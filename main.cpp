/* 
 * File:   main.cpp
 * Author: gedas
 *
 */
#include <signal.h>

/*
#include "lib/socket.h"
#include "structures.h"
#include "ClientContainer.h"
#include "TunnelContainer.h"
#include "TagGenerator.h"    // Klientu saugykla
 */

#include "GConfig.h"
#include "GLoggerFactory.h"
#include "GLogger.h"
#include "ConsoleGLogger.h"
#include "exitCodes.h"
#include "GSocket.h"
#include "TCPGSocket.h"
#include "TCPServerGSocket.h"
#include "SCTPServerGSocket.h"
#include "UDPServerGSocket.h"
#include "GTagGenerator.h"
#include "GCommandExecution.h"
#include "GClientContainer.h"

void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*) sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*) sa)->sin6_addr);
}

// Kintamasis kuris nuskao kada baigti darba programai
volatile sig_atomic_t done = 0;
// Funkcija keicianti done reiksme

void term(int signum) {
    done = 1;
}

int main(int argc, char** argv) {

    /* Veiksmai reikalingi sustabdyti programos veikima pagal SIGTERM signala */
    struct sigaction action;
    // Isvalo struktura
    memset(&action, 0, sizeof (struct sigaction));
    // Nustatom kuri funkcija bus kvieciama
    action.sa_handler = term;
    // Uzregistruojam valdyma
    sigaction(SIGTERM, &action, NULL);

    /** logger **
     * Kintamsis saugantis nuoroda i obnejtak, kuris atsakingas uz pranesimu 
     * pateikima. Is pradziu pateikiama konsoleje, o po to pagal konfiguracinio 
     * failo nustatymus */
    GServer::GLogger* logger = new GServer::ConsoleGLogger();

    /** config **
     * Nuoroda i objekta, kuris dirba su nustatymu nuskaitymu */
    GServer::GConfig* config = new GServer::GConfig(logger);
    // Nuskaiciau nustatymu faila

    /* Sarasas saugantis sokcetu, kurie klausosi prisjungimu sarasa */
    std::map<int, GServer::GSocket*> serverSocketList;
    /* Kintamasis skirtas dirbti su serveriu socketu sarasu dirbti */
    std::map<int, GServer::GSocket*>::iterator serverSocketListIterator;
    /* Sarasas saugantis sokcetus, kurie klausosi prisjungimu sarasa */
    std::map<int, GServer::GSocket*> clientSocketList;
    /* Kintamasis skirtas dirbti su serveriu socketu sarasu dirbti */
    std::map<int, GServer::GSocket*>::iterator clientSocketListIterator;

    // Kuriu zymiu generatoriu
    GServer::GTagGenerator tGenerator(logger);
    // Kuriu klientu saraso objekta
    GServer::GClientContainer clients(logger);
    // Kuriu tuneliu saraso objekta
    GServer::GTunnelContainer tunnel(logger);
    // Kuriu komandu apdorojimo objekta
    GServer::GCommandExecution cmdExec(logger, &tGenerator, &clients,
            &clientSocketList, config, &tunnel);

    //GServer::GLogger* oldLogger = logger;
    // Kuriu nauja logeri, pagal konfiguracini faila
    //logger = (GServer::GLogger*)(GServer::makeLogger(config));
    // Salinu senaji logeri
    //delete oldLogger;

    // Tikrinu ar pavyko sukurti logeri
    if (logger == NULL) {
        // Nepavyko, pranesu apie klaida ir grazinu klaidos koda
        std::cerr << "Nepavyko sukurti porgramos pranesimu objekto (Logger)" << std::endl;
        exit(GServer::EXIT_CODES::NO_LOGGER);
    }

    /* Kintamasis skirtas laikyti visus socketus, naudojaa tikrinti ar yra ka 
     * nuskaityti */
    fd_set visiSkaitomiSocket;
    // Inisicjuoju struktura
    FD_ZERO(&visiSkaitomiSocket);
    /* Kintamasis skirtas laikyti socketus, kuriuos tikrinsiu einamu metu del
     * gautos irnofmacijos */
    fd_set skaitomiSocket;
    /* Kintamasis skirtas saugoti maksimalaus socket deskriptoriaus reiksme */
    int maxDescriptor = 0;
    /* Kintamasis saugo laiko struktura,kurioje nurodoma kas kiek laiko atlikti 
     * tikrinima del nuskaitomu duomenu is socketu */
    struct timeval time;
    time.tv_sec = 0; // 0 sekundziu
    time.tv_usec = 2000; // 2000 mikro sekundes
    /* Kintamasis naudojamas begant per visus deskriptorius */
    int currentD = -1;

    //TODO: prideti kitus protokolus
    // Serveroi jungciu kintamieji
    GServer::TCPServerGSocket* TCPServer = NULL;

    // Tikrinu bus dirbama su TCP jungtimis
    if (config->getBoolSetting("TCP_ENABLE")) {
        // TCP jungtis ijungta
        logger->logDebug("main", "Kuriu TCP jungti");
        TCPServer = new GServer::TCPServerGSocket(config, logger,
                visiSkaitomiSocket, maxDescriptor, &cmdExec);
        if (TCPServer == NULL) {
            logger->logError("main", "Nepavyko sukurti TCP jungties");
            exit(GServer::EXIT_CODES::UNABLE_CREATE_TCP_SERVER_SOCKET);
        }
        // Pridedu TCP socket jungti i serveriu sarasa
        serverSocketList[TCPServer->getSocket()] = TCPServer;
    }

    GServer::SCTPServerGSocket* SCTPServer = NULL;
    // Tikrinu ar bus dirbama su SCTP jungtimis
    if (config->getBoolSetting("SCTP_ENABLE")) {
        //SCTP jungtis ijungta
        logger->logDebug("main", "Kuriu SCTP jungti");
        SCTPServer = new GServer::SCTPServerGSocket(config, logger,
                visiSkaitomiSocket, maxDescriptor, &cmdExec);
        if (SCTPServer == NULL) {
            logger->logError("main", "Nepavyko sukurti SCTP jungties");
            exit(GServer::EXIT_CODES::UNABLE_CREATE_SCTP_SERVER_SOCKET);
        }
        // Pridedu TCP socket jungti i serveriu sarasa
        serverSocketList[SCTPServer->getSocket()] = SCTPServer;
    }

    GServer::UDPServerGSocket* UDPServer = NULL;
    // Tikrinu ar bus dirbama su UDP jungtimis
    if (config->getBoolSetting("UDP_ENABLE")) {
        //UDP jungtis ijungta
        logger->logDebug("main", "Kuriu UDP jungti");
        UDPServer = new GServer::UDPServerGSocket(config, logger,
                visiSkaitomiSocket, maxDescriptor, &cmdExec);
        if (UDPServer == NULL) {
            logger->logError("main", "Nepavyko sukurti UDP jungties");
            exit(GServer::EXIT_CODES::UNABLE_CREATE_UDP_SERVER_SOCKET);
        }
        // Pridedu TCP socket jungti i serveriu sarasa
        serverSocketList[UDPServer->getSocket()] = UDPServer;
    }

    logger->logInfo("main", "Programa pradeda darba");

    // Dirbama kol programa negavo isjungimo signalo
    while (!done) {
        // Cia vyksta visas klausimosi procesas
        // Uzfiksuoju dabartinius visus socketus
        skaitomiSocket = visiSkaitomiSocket;

        // Gaunu visus socketus, kurie turi ka nors nuskaityti
        if (select(maxDescriptor + 1, &skaitomiSocket, NULL, NULL, &time)
                == -1) {
            // Ivyko klaida gaunant nuskaitomu socketu sarasa
            logger->logError("main", strerror(errno));
            // Iseinu is programos
            exit(GServer::EXIT_CODES::ERROR_IN_SELECT);
        }

        // Begu per visus deskriptorius
        for (currentD = 0; currentD <= maxDescriptor; currentD++) {
            // Tikrinu ar deskriptius yra reikaling nuskaityti sarase
            if (FD_ISSET(currentD, &skaitomiSocket)) {
                // Deskriptiurs is kurio reikai nusakityti duomenis

                // Tikrinam ar tai besiklausantis klientu prisjungimu socketas
                serverSocketListIterator = serverSocketList.find(currentD);
                if (serverSocketListIterator != serverSocketList.end()) {
                    // Reikia nuskaityti is serveriu socketu saraso
                    // Ivyks naujos sujungimo priemimas
                    GServer::GSocket* newConenction = NULL;
                    newConenction = serverSocketList.find(
                            currentD)->second->acceptConnection(
                            config, maxDescriptor);
                    // Tirkinu ar pavyko priimti jungti
                    if (newConenction != NULL) {
                        // Pridedu prie klientu saraso
                        clientSocketList[newConenction->getSocket()] =
                                newConenction;
                    }
                }// Atejo duomenys is kliento
                else {
                    // Surandu klienta ir duodu jam skaityti gautus duomenis
                    if (clientSocketList[currentD]->reciveData() <= 0) {
                        // Sujungimas baigtas arba klaida
                        logger->logInfo("main", "Sujungimas " +
                                std::to_string(currentD) + " atsijunge");
                        // Salinu objekta
                        delete clientSocketList[currentD];
                        // Salinu jo vieta sarase
                        clientSocketList.erase(currentD);
                    }
                }
            }
        }
    }

    logger->logInfo("main", "Programa baigia darba");

    // Begu per serveriu saras ir naikinu serveriu socketus
    for (serverSocketListIterator = serverSocketList.begin();
            serverSocketListIterator != serverSocketList.end();
            ++serverSocketListIterator) {
        // Salinu serveriu socketus
        delete serverSocketListIterator->second;

    }
    // Begu per klientu saras ir naikinu serveriu socketus
    for (clientSocketListIterator = clientSocketList.begin();
            clientSocketListIterator != clientSocketList.end();
            ++clientSocketListIterator) {
        // Salinu kliento socketus socketus
        delete clientSocketListIterator->second;
    }

    // Naikinu komandu vykdymo objekta
    //delete &cmdExec;
    // Naikinu zymu generavimo objekta
    delete &tGenerator;
    // Naikinu configuracini objekta
    delete config;
    // Naikinu pranesimu rasimo objekta
    delete logger;




















    /*
   
    string ip;
    string port;
    
    try {
        ip = config.lookup("IP").c_str();
        port = config.lookup("PORT").c_str();
    } catch (SettingNotFoundException &nfex) {
        cerr << "Nepavyko nuskaityti nustatymu" << endl;
        return (EXIT_FAILURE);
    }
    
    // Atidaromas socketas klausimuisi
    Socket S(ip.c_str(), port.c_str(), true);

    int fd_max; // Maksimalus failo dekriptorius
    fd_set master; // master file descriptor list
    fd_set skaitomas_deskriptorius; // temp file descriptor list for select()
    int newfd = -1; // newly accept()ed socket descriptor
    struct sockaddr_storage remoteaddr; // client address
    int yes = 1; // for setsockopt() SO_REUSEADDR, below
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
    
    // Klientu saugykla
    ClientContainer clients;
    // Tuneliu saugykla
    TunnelContainer tunnels;
    // Zymiu generatorius
    TagGenerator tagGenerator;

    FD_SET(S.getFileDescriptor(), &master);
    FD_SET(STDIN_FILENO, &master);
    fd_max = S.getFileDescriptor();

    // Klausimosi ciklas
    while (true) {
        skaitomas_deskriptorius = master;
        if (select(fd_max + 1, &skaitomas_deskriptorius, NULL, NULL, &time) == -1) {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data to read
        for (i = 0; i <= fd_max; i++) {
            if (FD_ISSET(i, &skaitomas_deskriptorius)) { // we got one!! 
                if (i == S.getFileDescriptor()) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(S.getFileDescriptor(),
                            (struct sockaddr *) &remoteaddr,
                            &addrlen);

                    if (newfd == -1) {
                        perror("accept");
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fd_max) { // keep track of the max
                            fd_max = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                                "socket %d\n",
                                inet_ntop(remoteaddr.ss_family,
                                get_in_addr((struct sockaddr*) &remoteaddr),
                                remoteIP, INET6_ADDRSTRLEN),
                                newfd);
                    }
                } else {
                    // handle data from a client
                    // Nusiskaitom antraste
                    if ((nbytes = recv(i, &buf[0], sizeof (header), 0)) <= 0) {
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
                        while (nbytes != (head->lenght + sizeof (header))) {
                            nbytes = nbytes + recv(i, &buf[nbytes], (head->lenght + sizeof (header)) - nbytes, 0);
                            //cout << "[COM]Siuo metu turiu " << nbytes << endl;
                        }
                        //cout << "[COM]Isviso gavau " << nbytes << endl;

                        switch (head->tag) {
                            case 0:
                            {
                                // Atejo komanda kuria reikai ivygdyti
                                Command* cmd = (struct Command*) &buf[ sizeof ( header) ];
                                cmd->command = ntohs(cmd->command);
                                
                                // Analizuojam kokia komanda atejo
                                switch (cmd->command) {
                                    case HELLO: {
                                        // Labas komanda
                                        helloCommand* hello = (struct helloCommand*) &buf[sizeof ( header)];
                                        cout << "Prisijunge: " << hello->domainName << "\\" << hello->pcName << "\\" << hello->userName << endl;
                                        clients.Add(i, hello->domainName, hello->pcName, hello->userName);
                                        break;
                                    }
                                    case LIST: {
                                        // Praso isvardinti klientus, formuosiu LIST ACK komanda
                                        listCommand* list = (struct listCommand*) &buf[sizeof ( header)];
                                        // Nustatau i tinkama isdestyma puslapi
                                        list->page = ntohl(list->page);
                                        //cout << "[LIST]Gautas puslapis " << list->page << endl;

                                        // Kuriu LIST_ACK komanda
                                        // Spausdinu
                                        int duomCount = -1;
                                        clients.PrintPage(i, list->page, &commandbuf[ sizeof (header) + sizeof (listAckCommand) ], duomCount);

                                        // Pildau komandos antraste
                                        listAckCommand* listAck = (struct listAckCommand*) &commandbuf[ sizeof (header) ];
                                        listAck->command = htons(LIST_ACK);

                                        if (duomCount > 0)
                                            listAck->success = true;
                                        else
                                            listAck->success = false;

                                        // Pildau paketo antrste
                                        header* head = (struct header*) &commandbuf[0];
                                        head->tag = htons(0);
                                        head->lenght = htonl(sizeof ( listAckCommand) + duomCount);
                                        //cout << "[LIST]Paketo ilgis: " << ntohl(head->lenght) << endl;
                                        int rSend = send(i, &commandbuf[0], duomCount + sizeof (header) + sizeof (listAckCommand), 0);
                                        //cout << "[LIST]Issiunciau " << rSend << endl;
                                        break;
                                    }
                                    case JSON_LIST: {
                                        // Praso isvardinti klientus, formuosiu LIST ACK komanda
                                        jsonListCommand* list = (struct jsonListCommand*) &buf[sizeof ( header)];
                                        // Nustatau i tinkama isdestyma puslapi
                                        list->page = ntohl(list->page);
                                        // Nustatau sokceto ID i tinkama isdestyma
                                        list->socketID = ntohl(list->socketID);
                                        // Kuriu LIST_ACK komanda
                                        // Spausdinu
                                        int duomCount = -1;
                                        clients.PrintPage(i, list->page, &commandbuf[ sizeof (header) + sizeof (jsonListAckCommand) ], duomCount);
                                        // Pildau komandos antraste
                                        jsonListAckCommand* listAck = (struct jsonListAckCommand*) &commandbuf[ sizeof (header) ];
                                        // Nurodau kokia komanda bus siunčiama
                                        listAck->command = htons(JSON_LIST_ACK);
                                        // Nurodau socketID
                                        listAck->socketID = htonl(list->socketID);
                                        if (duomCount > 0)
                                            listAck->success = true;
                                        else
                                            listAck->success = false;
                                        // Pildau paketo antrste
                                        header* head = (struct header*) &commandbuf[0];
                                        head->tag = htons(0);
                                        head->lenght = htonl(sizeof ( jsonListAckCommand) + duomCount);
                                        int rSend = send(i, &commandbuf[0], duomCount + sizeof (header) + sizeof (jsonListAckCommand), 0);
                                        break;
                                    }
                                    case INIT_CONNECT: {
                                        connectInitCommand* connect = (struct connectInitCommand*) &buf[ sizeof ( header) ];
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
                                        connectCommand* cCMD = (struct connectCommand*) &commandbuf[sizeof (header)];
                                        cCMD->command = htons(CONNECT);
                                        // Pildau connect komanda
                                        cCMD->tag = htons(clientTag);
                                        cCMD->source_port = htons(connect->source_port);
                                        cCMD->destinatio_port = htons(connect->destination_port);
                                        cCMD->client_id = htonl(i);
                                        cCMD->tunnelID = htonl(tunnel_id);
                                        // Kuriu gNet paketo antraste
                                        header* head = (struct header*) &commandbuf[0];
                                        head->tag = htons(0);
                                        head->lenght = htonl(sizeof (connectCommand));
                                        // Siunciu reikiamui klientui
                                        //cout << "[CONNECT_INIT]Paketo ilgis " << ntohl(head->lenght) << endl;
                                        int rSend = send(clientInfo.id, &commandbuf[0], sizeof (header) + sizeof (connectCommand), 0);
                                        //cout << "[CONNECT_INIT]Issiusta " << rSend << endl;
                                        break;
                                    }
                                    case JSON_INIT_CONNECT: {
                                        //cout << "[JSON] JSON_INIT_CONNECT" << endl;                                        jsonConnectInitCommand* connect = (struct jsonConnectInitCommand*) &buf[ sizeof ( header) ];
                                        jsonConnectInitCommand* connect = (struct jsonConnectInitCommand*) &buf[ sizeof ( header) ];
                                        // Suvartau paketo laukus i tinkama puse
                                        // Kliento ID
                                        connect->client_id = ntohl(connect->client_id);
                                        // Nutoles portas
                                        connect->destination_port = ntohs(connect->destination_port);
                                        // Atvertas portas pas inicijatoriu
                                        connect->source_port = ntohs(connect->source_port);
                                        // Srauto zyme
                                        connect->tag = ntohs(connect->tag);
                                        // Socketas pas inicijatoriu kuriam reikai grazinti duomenis
                                        connect->socketID = ntohl(connect->socketID);
                                        // Generuojama zyme clientui
                                        int clientTag = tagGenerator.Generate(&tunnels);
                                        // Kuriu nauja tuneli
                                        int tunnel_id = tunnels.InitConnect(i, connect, clientTag);
                                        // Ieskau reikiamo kliento
                                        Client clientInfo = clients.FindByID(connect->client_id);
                                        
                                        
                                        // Kuriu CONNECT paketa
                                        jsonConnectCommand* cCMD = (struct jsonConnectCommand*) &commandbuf[sizeof (header)];
                                        // Siunciama komanda
                                        cCMD->command = htons(JSON_CONNECT);
                                        // Tunelio identifiaktorius
                                        cCMD->tag = htons(clientTag);
                                        // Preivadas, atvertas pas iniciatoriu
                                        cCMD->source_port = htons(connect->source_port);
                                        // Nutoles portas prie kurio bus jungiamasi
                                        cCMD->destinatio_port = htons(connect->destination_port);
                                        // Inicijuojancio kliento ID
                                        cCMD->client_id = htonl(i);
                                        // Tunelio ID
                                        cCMD->tunnelID = htonl(tunnel_id);
                                        // Iniciatoriaus proketo numeris kuriam bus grazinta inforamcija
                                        cCMD->socketID = htonl(connect->socketID);
                                        // Kuriu gNet paketo antraste
                                        header* head = (struct header*) &commandbuf[0];
                                        head->tag = htons(0);
                                        head->lenght = htonl(sizeof (jsonConnectCommand));
                                        // Siunciu reikiamui klientui
                                        int rSend = send(clientInfo.id, &commandbuf[0], sizeof (header) + sizeof (jsonConnectCommand), 0);
                                        
                                        break;
                                    }
                                    case CONNECT_ACK: {
                                        // Atejo atsakas is sujungimo
                                        connectAckCommand* connectAck = (struct connectAckCommand*) &buf[sizeof (header)];
                                        // Suvartau atejusiuos duoemnis teisinga tvarka
                                        connectAck->status = ntohs(connectAck->status);
                                        connectAck->tunnelID = htonl(connectAck->tunnelID);
                                        // Baigiu pildyti tunelio duomenis
                                        tunnel* tunelis = tunnels.ConnectAck(connectAck);

                                        // Formuoju CONNECT_INT_ACK paketa
                                        connectInitAckCommand* ack = (struct connectInitAckCommand*) &commandbuf[sizeof (header)];
                                        try {
                                            ack->command = htons(INIT_CONNECT_ACK);
                                            // Nustatau iniciatoriaus puses TAG zyme
                                            ack->adm_tag = htons(tunelis->adm_tag);
                                            if (tunelis == NULL) {
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
                                            head->lenght = htonl(sizeof (connectInitAckCommand));

                                            // Siunciu adminui duomenis
                                            //cout << "[CONNECT_INIT_ACK]Paketo ilgis " << ntohl(head->lenght) << endl;
                                            int rSend = send(tunelis->adm_socket, &commandbuf[0], sizeof (header) + sizeof (connectInitAckCommand), 0);
                                            //cout << "[CONNECT_INIT_ACK]Issiunciau " << rSend << endl;
                                        } catch (exception e) {
                                            printf("Nepavyko issiusti CONNECT_INI_ACK paketo\n");
                                        }
                                        break;
                                    } // case JSON_CONNECT_ACK: {
                                    case JSON_CONNECT_ACK: {
                                        //cout << "[JSON] JSON_CONNECT_ACK" << endl;
                                        // Atejo atsakas is sujungimo
                                        jsonConnectAckCommand* connectAck = (struct jsonConnectAckCommand*) &buf[sizeof (header)];
                                        // Suvartau atejusiuos duoemnis teisinga tvarka
                                        connectAck->status = ntohs(connectAck->status);
                                        connectAck->tunnelID = htonl(connectAck->tunnelID);
                                        // Baigiu pildyti tunelio duomenis
                                        tunnel* tunelis = tunnels.ConnectAck(connectAck);

                                        // Formuoju JSON_CONNECT_INT_ACK paketa
                                        jsonConnectInitAckCommand* ack = (struct jsonConnectInitAckCommand*) &commandbuf[sizeof (header)];
                                        try {
                                            ack->command = htons(JSON_INIT_CONNECT_ACK);
                                            // Persiunciu nevaryta socketID
                                            ack->socketID = connectAck->socketID;
                                            if (tunelis == NULL) {
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
                                            head->lenght = htonl(sizeof (jsonConnectInitAckCommand));

                                            // Siunciu adminui duomenis
                                            //cout << "[CONNECT_INIT_ACK]Paketo ilgis " << ntohl(head->lenght) << endl;
                                            int rSend = send(tunelis->adm_socket, &commandbuf[0], sizeof (header) + sizeof (jsonConnectInitAckCommand), 0);
                                            //cout << "[CONNECT_INIT_ACK]Issiunciau " << rSend << endl;
                                        } catch (exception e) {
                                            printf("Nepavyko issiusti CONNECT_INI_ACK paketo\n");
                                        }
                                        break;
                                    } // case CONNECT_ACK: {
                                    case CLIENT_CONNECT: {
                                        //cout << "Gavau CLIENT_CONNECT komanda" << endl;
                                        clientConnectCommand* cmd = (struct clientConnectCommand*) &buf[sizeof (header)];
                                        // Nustatau zyme
                                        cmd->tag = ntohs(cmd->tag);
                                        // Ieskau is turimu jungciu saraso kam persiusti
                                        int cli_socket = -1, cli_tag = -1;
                                        tunnels.FindByPear(i, cmd->tag, cli_socket, cli_tag);

                                        if (cli_socket != -1 && cli_tag != -1) {
                                            // PAvyko rasti kam persiusti
                                            // formuoju BEGIN_READ paketa
                                            beginReadCommand* read = (struct beginReadCommand*) &buf[sizeof (header)];
                                            read->command = htons(BEGIN_READ);
                                            read->tag = htons(cli_tag);
                                            // Formuoju antraste
                                            header* head = (struct header*) &buf[0];
                                            head->tag = htons(0);
                                            head->lenght = htonl(sizeof (beginReadCommand));

                                            // Siunciu duomenis
                                            //cout << "Siunciu BEGIN_READ" << endl;
                                            //cout << "[BEGIN_READ]Paketo ilgis " << ntohl(head->lenght) << endl;
                                            int rSend = send(cli_socket, &buf[0], sizeof (header) + sizeof (beginReadCommand), 0);
                                            //cout << "[BEGIN_READ]Issiunciau " << rSend << endl;
                                        } else {
                                            // Nepavyko rasti kam persiusti
                                            printf("Nepavyko rasti kam siusti BEGIN_READ paketo\n");
                                        }
                                        break;
                                    } // case CLIENT_CONNECT:{
                                    case BEGIN_READ_ACK: {
                                        cout << "Gavau BEGIN_READ_ACK" << endl;
                                        beginReadAckCommand* cmd = (struct beginReadAckCommand*) &buf[sizeof (header)];
                                        // Nustatau zyme i gera isdestyma
                                        cmd->tag = ntohs(cmd->tag);

                                        // Ieskau jungties pagal zyme
                                        int adm_socket = -1, adm_tag = -1;
                                        tunnels.FindByPear(i, cmd->tag, adm_socket, adm_tag);

                                        if (adm_socket != -1 && adm_tag != -1) {
                                            // Suradau jungti
                                            // Persiunciu administratoriui atsaka
                                            clientConnectAckCommand* ack = (struct clientConnectAckCommand*) &buf[sizeof (header)];
                                            // Pildau struktura
                                            ack->command = htons(CLIENT_CONNECT_ACK);
                                            ack->tag = htons(adm_tag);
                                            // PIldau antraste
                                            header* head = (struct header*) &buf[0];
                                            head->tag = htons(0);
                                            head->lenght = htonl(sizeof (clientConnectAckCommand));

                                            //cout << "Siunciu CLIENT_CONNECT_ACK" << endl;
                                            //cout << "[CLIENT_CONNECT_ACK]Paketo ilgis " << ntohl(head->lenght) << endl;
                                            int rSend = send(adm_socket, &buf[0], sizeof (header) + sizeof (clientConnectAckCommand), 0);
                                            //cout << "[CLIENT_CONNECT_ACK]Issiunciau " << rSend << endl;
                                        } else {
                                            // Neradau jungties
                                            printf("Nepavyko rasti kam siusti CLIENT_CONNECT_ACK paketo\n");
                                        }
                                        break;
                                    } // case BEGIN_READ_ACK:{
                                    case CLOSE_TUNNEL: {
                                        // Susivartau gauta informacija
                                        closeTunnelCommand* close = (struct closeTunnelCommand*) &buf[sizeof ( header)];
                                        close->tag = ntohs(close->tag);
                                        
                                        // Salinu tuneli is tuneliu saraso
                                        tunnel tunelis = tunnels.RemoveBySocketTag(i, close->tag);
                                        // Kintamaisis saugantis SOCKET id , kuriuo bus siunciamas atsakas
                                        int returnSocket = -1;
                                        
                                        // Tirkinu is kurios puses atejo CLOSE_TUNNEL
                                        // Ar is iniciatoriaus
                                        if(tunelis.adm_socket == i){
                                            // Nustatau i kliento
                                            returnSocket = tunelis.cln_socket;
                                            close->tag = htons(tunelis.cln_tag);
                                        }
                                        else
                                        {
                                            // Nustatau i iniciatoriaus
                                            returnSocket = tunelis.adm_socket;
                                            close->tag = htons(tunelis.adm_tag);
                                        }
                                        
                                        // Persiunciu CLOSE_TUNNEL komanda
                                        // Suvartau TAG
                                        
                                        close->command = htons(CLOSE_TUNNEL);
                                        
                                        // Pildau antraste
                                        header* head = (struct header*) &buf[0];
                                        head->tag = htons(0);
                                        head->lenght = htonl(sizeof(closeTunnelCommand));
                                        
                                        //cout << "[CLOSE_TUNNEL]Paketo ilgis: " << ntohl(head->lenght) << endl;
                                        int rSend = send(returnSocket, &buf[0], sizeof (header) + sizeof (closeTunnelCommand), 0);
                                        //cout << "[CLOSE_TUNNEL]Issiunciau " << rSend << endl;
                                        break;
                                    }
                                }
                                break;
                            }
                            default: {
                                // Duomenu permetimas i kita socketa
                                int dep_socket = -1, dep_tag = -1, lenght = head->lenght;
                                tunnels.FindByPear(i, head->tag, dep_socket, dep_tag);
                                // Tikrinu ar rastas sujungimas
                                if (dep_socket != -1 && dep_tag != -1) {
                                    // Permetineju paketa i reikiama socketa

                                    head->tag = htons(dep_tag);
                                    head->lenght = htonl(head->lenght);
                                    //cout << "[COM]Reikia issiuti " << ntohl(head->lenght) << endl;
                                    int rSend = 0;
                                    while (rSend != nbytes) {
                                        rSend = rSend + send(dep_socket, &buf[rSend], nbytes - rSend, 0);
                                        //cout << "[COM]Siuo metu issiunciau " << rSend << endl;
                                    }
                                    //cout << "[COM]persiunciau: " << rSend << endl;
                                }
                                break;
                            }
                        } // END switch
                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END Klausimosi ciklas
    return 0;
     *      * */
    // Iseigos kodas jei programa baigiais normaliai
    exit(GServer::EXIT_CODES::NORMAL);
} // END main

