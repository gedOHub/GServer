/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GCommandExecution.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 23, 14.04
 */

#ifndef GCOMMANDEXECUTION_H
#define GCOMMANDEXECUTION_H

#include "GCommandExecution.h"
#include "GObject.h"
#include "GLogger.h"

#include "GClientContainer.h"
#include "GSocket.h"
#include "GTunnelContainer.h"

#include <map>

namespace GServer {

    class GSocket;
    class GTagGenerator;
    class UDPServerGSocket;
    class TCPServerGSocket;
    class TCPClientGSocket;
    class UDPClientGSocket;

    class GCommandExecution : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** GCommandExecution ***
         * Metodas skirtas sukurti GCommandExecution. Si klase analizuoja ir
         * vykdo gautas komandas. 
            logger- pranesimu isvedimo objektas 
            tagGenerato- objektas, generuojantis zymas
            clients- klientu sarao objektas
            clientSocketList- klientu ir socketu sarasas 
            conf- nuododa i objekta, kuris dirba su konfiguraciniu failu
            tunnels- nuoroda i tuneliu saugojimo objekta*/
        GCommandExecution(GLogger* logger, GTagGenerator* tagGenerator,
                GClientContainer* clients,
                std::map<int, GServer::GSocket*>* clientSocketList,
                GConfig* conf, GTunnelContainer* tunnels);
        virtual ~GCommandExecution();

        /*** executeCommand ***
         * Metodas ksirtas nuskaityti is buferio komanda ir grazinti atsakyma i 
         * ta pati buferi. Rezultatas- true, jei pavyko apdoroti komanda, false,
         *  jei ne 
            buffer- buferis, kuriame gauti ir apdorojimi duomenys
            size- apdoroto atsakymo dydis buferyje
            socket- kliento objektas, kuris gavo duomenis */
        bool executeCommand(vector<char>& buffer, int& size, GSocket* socket);

        /*** registerUDPAccept ***
         * Metodas sksirtas uzregistruoti UDP kliento jungti */
        void registerUDPAccept(GSocket* udp);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /*** clientSocketList ***
         * Kintamasis sksirtas saugoti nurooda i klientu ir ju objektu sarasa */
        std::map<int, GServer::GSocket*>* clientSocketList;

        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /*** logger ***
         * Kintamassis skirtas saugoti nuoroda i pranesimu isvedimo objekta */
        GLogger* logger;

        /*** tagGenerator ***
         * Kintamasis skirtas asugoti nuoroda i zymy generavimo objekta */
        GTagGenerator* tagGenerator;

        /*** clients ***
         * Kintamasis saugo nuoroda i klientu saraso objekta */
        GClientContainer* clients;

        /*** config ***
         * Kintamasis saugnatis nuoroda i objekta, kuris dirba su nustatymu 
         * failu */
        GServer::GConfig* config;

        /*** tunnels ***
         * Kintamasis skirtas saugoti nuoroda i tuneliu saro objekta */
        GServer::GTunnelContainer* tunnels;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** analizeHeader ***
         * Metodas skirtas nustatyti atejusiu duomenu headerio reiksmems. 
         * Rezultatas- true, pavykus nustatyti, false- nepavykus
            buffer- buferis, kuraime ieskoma
            tag- nustatyta tag reiksme
            size- nustatyta duomenu dydzio reiksme*/
        bool analizeHeader(char* buffer, int& tag, int& size);

        /*** analizeCommandHeader ***
         * Metodas skirtas nustatyti atejusios koamndos lauku reiksmes. 
         * Rezultatas- true, pavykus nustatyti, false- nepavykus
            buffer- buferis, kuraime ieskoma
            command- nustatyta komandos reiksme*/
        bool analizeCommandHeader(char* buffer, int& command);

        /*** commandHello ***
         * Metodas skirtas ivykdyti HELLO komandai. Rezultatas pridetas kliento
         *  objektas 
            buffer- buferis, kuriame saugomi duomenys
            socket- socketas, kuriame gauta si komanda*/
        Client commandHello(char* buffer, int socket);

        /*** commandList ***
         * Metodas skirtas ivygdyti LIST komanda, kuri grazina klientui 
         * prisjungusiu kientu sarasa. Rezultatas- suformuotas klientu sarasa 
         * tame paciame masyve, kuris paduotas komandai
            buffer- nuoroda i buferi
            duomCount- suformuoto atsakymo duomenu kiekis
            socket- kintamasis nusakantis kurios soketo nereikai grazinti*/
        void commandList(vector<char>& buffer, int& duomCount, int socket);

        /*** commandJsonList ***
         * Metodas skirtas ivygdyti JSON_LIST komanda, kuri grazina klientui 
         * prisjungusiu kientu sarasa. Rezultatas- suformuotas klientu sarasa 
         * tame paciame masyve, kuris paduotas komandai
            buffer- nuoroda i buferi
            duomCount- suformuoto atsakymo duomenu kiekis
            socket- kintamasis nusakantis kurios soketo nereikai grazinti*/
        void commandJsonList(vector<char>& buffer, int& duomCount, int socket);

        /*** commandInitCommand ***
         * Metodas skirtas inicijuosti sujungimui */
        void commandInitCommand(vector<char>& buffer, int& duomCount,
                int socket, int& reciverID);

        /*** commandInitCommand ***
         * Metodas skirtas inicijuosti sujungimui */
        void commandJsonInitCommand(vector<char>& buffer, int& duomCount,
                int socket, int& reciverID);

        /*** commandConnecACK ***
         * Metodas skirtas realizuoti CONNECT_AK komandai */
        void commandConnecACK(vector<char>& buffer, int& duomCount, int socket,
                int& reciverSocket);

        /*** commandJsonConnecACK ***
         * Metodas skirtas realizuoti CONNECT_AK komandai */
        void commandJsonConnecACK(vector<char>& buffer, int& duomCount, int socket,
                int& reciverSocket);

        /*** commandClientConnect ***
         * Metodas skirtasigyvnedinti CLIENT_CONNECT komandai */
        void commandClientConnect(vector<char>& buffer, int& duomCount,
                int socket, int& reciver);
        
        /*** commandBeginReadAck ***
         * Metodas skirtasigyvnedinti CLIENT_CONNECT komandai */
        void commandBeginReadAck(vector<char>& buffer, int& duomCount,
                int socket, int& reciver);
        
        /*** commandCloseTunnel ***
         * Metodas skirtasigyvnedinti CLIENT_CONNECT komandai */
        void commandCloseTunnel(vector<char>& buffer, int& duomCount,
                int socket, int& reciver);
        // ##### END Metodai #####
    };
}

#endif /* GCOMMANDEXECUTION_H */

