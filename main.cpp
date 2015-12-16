/* 
 * File:   main.cpp
 * Author: gedas
 *
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include <list>
#include <stdlib.h>
#include <fstream>
#include <libconfig.h++>

#include "lib/socket.h"
#include "structures.h"
#include "ClientContainer.h"
#include "TunnelContainer.h"
#include "TagGenerator.h"    // Klientu saugykla

using namespace std;
using namespace libconfig;


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char** argv) {
    
    // Nuskaitau nustatymus
    Config config;
    try {
        config.readFile("server.cfg");
    } catch(const FileIOException &fioex) {
        std::cerr << "Nepavyko atverti konfiguracinio failo server.cfg" << std::endl;
        return(EXIT_FAILURE);
    }
    catch(ParseException &pex) {
        std::cerr << "Skaitymi klaida server.cfg" << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        return(EXIT_FAILURE);
    }
    
    string ip;
    string port;
    try {
        string tmp_ip = config.lookup("IP");
        string tmp_port = config.lookup("PORT");
        ip = tmp_ip;
        port = tmp_port;
    } catch(SettingNotFoundException &nfex) {
        cerr << "Nepavyko nuskaityti nustatymu" << endl;
        return(EXIT_FAILURE);
    }
    // Atidaromas socketas klausimuisi
    Socket S(ip.c_str(),port.c_str(),true);
    
    int fd_max; // Maksimalus failo dekriptorius
    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int newfd = -1;        // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    int yes=1;        // for setsockopt() SO_REUSEADDR, below
    int i, j, rv;
    socklen_t addrlen;
    char remoteIP[INET6_ADDRSTRLEN];
    const int FiveMBtoCHAR = 5242880;
    char buf[FiveMBtoCHAR];
    char commandbuf[1048576];
    //head* header = (struct head* ) &buf[0];
    int nbytes;
    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 2000;
//    
    // Klientu saugykla
    ClientContainer clients;
    // Tuneliu saugykla
    TunnelContainer tunnels;
    // Zymiu generatorius
    TagGenerator tagGenerator;
    
    FD_SET(S.getFileDescriptor(), &master);
    FD_SET(STDIN_FILENO, &master);
    fd_max = S.getFileDescriptor();
    
    while(true) {
        read_fds = master;
        if(select(fd_max+1, &read_fds, NULL,NULL,&time) == -1){
            perror("select");
            exit(4);
        }
        
        // run through the existing connections looking for data to read
        for(i = 0; i <= fd_max; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
                /*
                if (i == STDIN_FILENO){
                    // Konsoles ivestis
                    /*
                    int rRecv = read(STDIN_FILENO, &buf[sizeof(header)], FiveMBtoCHAR-sizeof(header));
                    log << "Gavau " << rRecv << " is " << i << "socket" << endl;
                    std::string komanda(&buf[16], rRecv+1);
                    //newfd = 100 ;
                    if (newfd > 0 ) {
                        // Pridedam komandini tag
                        char tagBuffer[8];
                        //memset(tagBuffer, ' ', sizeof(tagBuffer));
                        snprintf(tagBuffer, sizeof(tagBuffer), "%d", 0);
                        memcpy(&buf[0], tagBuffer, 8);
                        // Pridedu duomenu ilgi
                        char lenghtBuffer[8];
                        //memset(lenghtBuffer, ' ', sizeof(lenghtBuffer));list 1232132
                        snprintf(lenghtBuffer, sizeof(lenghtBuffer), "%d", rRecv);
                        memcpy(&buf[8], lenghtBuffer, 8);
                        
                        int rSend = send(newfd, buf, rRecv+16, 0);
                    }
                    break;
                    
                } else*/ 
                    if (i == S.getFileDescriptor()) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(S.getFileDescriptor(),
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fd_max) {    // keep track of the max
                            fd_max = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                            "socket %d\n",
                            inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr*)&remoteaddr),
                                remoteIP, INET6_ADDRSTRLEN),
                            newfd);
                    }
                } else {
                    // handle data from a client
                    // Nusiskaitom antraste
                    if ((nbytes = recv(i, &buf[0], sizeof(header), 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                            clients.DeleteByID(i);
                        } else {
                            perror("recv");
                            clients.DeleteByID(i);
                        }
                        close(i); // bye!
                         FD_CLR(i, &master); // remove from master set
                    } else {
                        // we got some data from a client
                        // Issinagrinejam antraste
                        header* head = (struct header*) &buf[0];
                        head->tag = ntohs(head->tag);
                        head->lenght = ntohl(head->lenght);
                        
                        //cout << "[COM]Reikia gauti " << head->lenght << endl;
                        // Gaunam pilna paketa
                        while( nbytes != (head->lenght + sizeof(header)) ){
                            nbytes = nbytes + recv(i, &buf[nbytes], (head->lenght + sizeof(header))-nbytes, 0);
                            //cout << "[COM]Siuo metu turiu " << nbytes << endl;
                        }
                        //cout << "[COM]Isviso gavau " << nbytes << endl;
                        
                        switch ( head->tag ){
                            case 0:{
                                // Atejo komanda kuria reikai ivygdyti
                                Command* cmd = (struct Command*) &buf[ sizeof ( header ) ];
                                cmd->command = ntohs( cmd->command );
                                // Analizuojam kokia komanda atejo
                                switch(cmd->command){
                                    case HELLO:{
                                        // Labas komanda
                                        helloCommand* hello = (struct helloCommand*) &buf[sizeof ( header )];
                                        cout << "Prisijunge: " << hello->domainName << "\\" << hello->pcName << "\\" << hello->userName << endl; 
                                        clients.Add(i, hello->domainName, hello->pcName, hello->userName);
                                        break;
                                    }
                                    case LIST:{
                                        // Praso isvardinti klientus, formuosiu LIST ACK komanda
                                        listCommand* list = (struct listCommand*) &buf[sizeof ( header )] ; 
                                        // Nustatau i tinkama isdestyma puslapi
                                        list->page = ntohl(list->page);
                                        //cout << "[LIST]Gautas puslapis " << list->page << endl;
                                        
                                        // Kuriu LIST_ACK komanda
                                        // Spausdinu
                                        int duomCount = -1;
                                        clients.PrintPage(i, list->page, &commandbuf[ sizeof(header) + sizeof(listAckCommand) ], duomCount);
                                        
                                        // Pildau komandos antraste
                                        listAckCommand* listAck = (struct listAckCommand*) &commandbuf[ sizeof(header) ];
                                        listAck->command = htons( LIST_ACK);
                                        
                                        if(duomCount > 0) 
                                            listAck->success = true;
                                        else 
                                            listAck->success = false;
                                        
                                        // Pildau paketo antrste
                                        header* head = (struct header*) &commandbuf[0];
                                        head->tag = htons(0);
                                        head->lenght = htonl( sizeof( listAckCommand ) + duomCount );
                                        //cout << "[LIST]Paketo ilgis: " << ntohl(head->lenght) << endl;
                                        int rSend = send( i, &commandbuf[0], duomCount+sizeof(header)+sizeof(listAckCommand), 0 );
                                        //cout << "[LIST]Issiunciau " << rSend << endl;
                                        break;
                                    }
                                    case INIT_CONNECT:{
                                        connectInitCommand* connect = (struct connectInitCommand*) &buf[ sizeof ( header ) ];
                                        // Suvartau paketo laukus i tinkama puse
                                        connect->client_id = ntohl(connect->client_id);
                                        connect->destination_port = ntohs(connect->destination_port);
                                        connect->source_port = ntohs(connect->source_port);
                                        connect->tag = ntohs(connect->tag);
                                        // Generuojama zyme clientui
                                        int clientTag = tagGenerator.Generate(&tunnels);
                                        
                                        // Kuriu nauja tuneli
                                        int tunnel_id = tunnels.InitConnect(i, connect, clientTag);
                                        // Ieskau reikiamo kliento
                                        Client clientInfo = clients.FindByID(connect->client_id);
                                        
                                        // Kuriu CONNECT paketa
                                        connectCommand* cCMD = (struct connectCommand*) &commandbuf[sizeof(header)];
                                        cCMD->command = htons(CONNECT);
                                        cCMD->tag = htons(clientTag);
                                        cCMD->destinatio_port = htons( connect->destination_port );
                                        cCMD->tunnelID = htonl(tunnel_id);
                                        // Kuriu gNet paketo antraste
                                        header* head = (struct header*) &commandbuf[0];
                                        head->tag = htons(0);
                                        head->lenght = htonl( sizeof(connectCommand) );
                                        // Siunciu reikiamui klientui
                                        //cout << "[CONNECT_INIT]Paketo ilgis " << ntohl(head->lenght) << endl;
                                        int rSend = send( clientInfo.id, &commandbuf[0], sizeof(header)+sizeof(connectCommand), 0 );
                                        //cout << "[CONNECT_INIT]Issiusta " << rSend << endl;
                                        break;
                                    }
                                    case CONNECT_ACK:{
                                        // Atejo atsakas is sujungimo
                                        connectAckCommand* connectAck = (struct connectAckCommand*) &buf[sizeof(header)];
                                        // Suvartau atejusiuos duoemnis teisinga tvarka
                                        connectAck->status = ntohs(connectAck->status);
                                        connectAck->tunnelID = htonl(connectAck->tunnelID);
                                        // Baigiu pildyti tunelio duomenis
                                        tunnel* tunelis = tunnels.ConnectAck(connectAck);
                                        
                                        // Formuoju CONNECT_INT_ACK paketa
                                        connectInitAckCommand* ack = (struct connectInitAckCommand*) &commandbuf[sizeof(header)];
                                        try{
                                            ack->command = htons(INIT_CONNECT_ACK);
                                            if(tunelis == NULL){
                                                // Nepavykus rasti tunelio
                                                ack->status = htons(FAULT);
                                                ack->client_id = htonl(i);
                                                ack->adm_port = htons(-1);
                                                ack->client_id = htons(-1);
                                            } else {
                                                ack->status = htons(tunelis->status);
                                                ack->client_id = htonl(tunelis->cln_socket);
                                                ack->adm_port = htons(tunelis->adm_port);
                                                ack->cln_port = htons(tunelis->cln_port);
                                            }
                                            // Pildau header struktura
                                            header* head = (struct header*) &commandbuf[0];
                                            head->tag = htons(0);
                                            head->lenght = htonl(sizeof(connectInitAckCommand));

                                            // Siunciu adminui duomenis
                                            //cout << "[CONNECT_INIT_ACK]Paketo ilgis " << ntohl(head->lenght) << endl;
                                            int rSend = send( tunelis->adm_socket, &commandbuf[0], sizeof(header)+sizeof(connectInitAckCommand), 0 );
                                            //cout << "[CONNECT_INIT_ACK]Issiunciau " << rSend << endl;
                                        }catch(exception e){
                                            printf("Nepavyko issiusti CONNECT_INI_ACK paketo\n");
                                        }
                                        break;
                                    } // case CONNECT_ACK: {
                                    case CLIENT_CONNECT:{
                                        clientConnectCommand* cmd = (struct clientConnectCommand*) &buf[sizeof(header)];
                                        // Nustatau zyme
                                        cmd->tag = ntohs(cmd->tag);
                                        // Ieskau is turimu jungciu saraso kam persiusti
                                        int cli_socket = -1, cli_tag = -1;
                                        tunnels.FindByPear(i, cmd->tag, cli_socket, cli_tag);
                                       
                                        if( cli_socket != -1 && cli_tag != -1 ){
                                            // PAvyko rasti kam persiusti
                                            // formuoju BEGIN_READ paketa
                                            beginReadCommand* read = (struct beginReadCommand*) &buf[sizeof(header)];
                                            read->command = htons(BEGIN_READ);
                                            read->tag = htons(cli_tag);
                                            // Formuoju antraste
                                            header* head = (struct header*)&buf[0];
                                            head->tag = htons(0);
                                            head->lenght = htonl(sizeof(beginReadCommand));
                                            
                                            // Siunciu duomenis
                                            //cout << "[BEGIN_READ]Paketo ilgis " << ntohl(head->lenght) << endl;
                                            int rSend = send(cli_socket, &buf[0], sizeof(header)+sizeof(beginReadCommand),0);
                                            //cout << "[BEGIN_READ]Issiunciau " << rSend << endl;
                                        } else {
                                            // Nepavyko rasti kam persiusti
                                            printf("Nepavyko rasti kam siusti BEGIN_READ paketo\n");
                                        }
                                        break;
                                    } // case CLIENT_CONNECT:{
                                    case BEGIN_READ_ACK:{
                                        beginReadAckCommand* cmd = (struct beginReadAckCommand*) &buf[sizeof(header)];
                                        // Nustatau zyme i gera isdestyma
                                        cmd->tag = ntohs(cmd->tag);
                                        
                                        // Ieskau jungties pagal zyme
                                        int adm_socket = -1, adm_tag = -1;
                                        tunnels.FindByPear(i, cmd->tag, adm_socket, adm_tag);
                                        
                                        if(adm_socket != -1 && adm_tag != -1){
                                            // Suradau jungti
                                            // Persiunciu administratoriui atsaka
                                            clientConnectAckCommand* ack = (struct clientConnectAckCommand*) &buf[sizeof (header)];
                                            // Pildau struktura
                                            ack->command = htons(CLIENT_CONNECT_ACK);
                                            ack->tag = htons(adm_tag);
                                            // PIldau antraste
                                            header* head = (struct header*) &buf[0];
                                            head->tag = htons(0);
                                            head->lenght = htonl(sizeof(clientConnectAckCommand));
                                            
                                            //cout << "[CLIENT_CONNECT_ACK]Paketo ilgis " << ntohl(head->lenght) << endl;
                                            int rSend = send(adm_socket, &buf[0], sizeof(header)+sizeof(clientConnectAckCommand), 0);
                                            //cout << "[CLIENT_CONNECT_ACK]Issiunciau " << rSend << endl;
                                        } else {
                                            // Neradau jungties
                                            printf("Nepavyko rasti kam siusti CLIENT_CONNECT_ACK paketo\n");
                                        }
                                        break;
                                    } // case BEGIN_READ_ACK:{
                                }
                                break;
                            }
                            default:{
                                // Duomenu permetimas i kita socketa
                                int dep_socket =-1, dep_tag = -1, lenght = head->lenght;
                                tunnels.FindByPear(i, head->tag, dep_socket, dep_tag);
                                // Tikrinu ar rastas sujungimas
                                if(dep_socket != -1 && dep_tag != -1){
                                    // Permetineju paketa i reikiama socketa
         
                                    head->tag = htons(dep_tag);
                                    head->lenght = htonl(head->lenght);
                                    //cout << "[COM]Reikia issiuti " << ntohl(head->lenght) << endl;
                                    int rSend = 0;
                                    while(rSend != nbytes){
                                        rSend = rSend + send(dep_socket, &buf[rSend], nbytes - rSend, 0);
                                        //cout << "[COM]Siuo metu issiunciau " << rSend << endl;
                                    }                         
                                    //cout << "[COM]persiunciau: " << rSend << endl;
                                }
                                break;
                            }
                        }
                     }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    }
    return 0;
}
