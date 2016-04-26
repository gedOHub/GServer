/* 
 * File:   UDPServerGSocket.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 23, 00.47
 */

#ifndef UDPSERVERGSOCKET_H
#define UDPSERVERGSOCKET_H

#include "UDPGSocket.h"
#include "GCommandExecution.h"
#include "UDPClientGSocket.h"
#include "GConfig.h"

#include <arpa/inet.h>


namespace GServer {

    class UDPServerGSocket : public UDPGSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** UDPServerGSocket **
         * Metodas skirtas sukurti UDPServerGSocket objekta, kuris organizuoja 
         * darba su nauju klientu prijsungimu per UDP protokola
         *  conf- objektas, kuris dirba su nustatymu failu
         *  logger- objektas, kuris dirba su pranesimu isvedimu
         *  visiSocket- kintamaisi, kuris saugo visu socketu sarasa
         *  maxDeskriptor- nuoroda i kintamji, kuris saugo didziuasio 
         * desktoriaus reikse 
            command- nuoroda i objekta, kuris atsakingas uz komandu vykdyma*/
        UDPServerGSocket(GServer::GConfig* conf, GLogger* logger,
                fd_set& visiSocket, int& maxDeskriptor,
                GCommandExecution* command);
        virtual ~UDPServerGSocket();

        //TODO: fix it
        /** acceptConnection **
         * Metodas skirtas priimti kliento prisjugimui. Metodas grazina naujai
         *  sukurti kliento objekta */
        //virtual GServer::GSocket* acceptConnection( GServer::GConfig* conf, 
        //int &maxDescriptor );

        /** acceptConnection **
         * Metodas skirtas priimti kliento duomenims, nes sio protokolo socketai
         *  neuzmeezga sesijos. Si funkcija tokia pati kaip recive. Sio 
         * protokolo socketams niekada nebus saukiamas recive, nes visada 
         * bus accept dalis.
         *  conf- objektas dirbantis su nustatymu failu
         *  maxDescriptor- maksimalaus deskritporiaus reiksme */
        virtual GServer::GSocket* acceptConnection(GServer::GConfig* conf,
                int &maxDescriptor);

        /** recive **
         * Metodas skirtas gauti duomenis is tinklo. Sia funkcija turi 
         * igyvendinti kiekvienas protokolas savaitp. Rezultatas- gautu 
         * duomenu kiekis */
        //virtual int reciveData();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /*** UDPClientList ***
         * Kintamasis skirtas saugoti klientu sarasa surysta su ju objektais */
        std::map< std::string, UDPClientGSocket* > UDPClientList;

        /*** UDPClientListIterator ***
         * KKintamasis skirtas vaikscioti per UDPClientList kintamojo duomenis*/
        std::map< std::string, UDPClientGSocket* >::iterator
        UDPClientListIterator;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* UDPSERVERGSOCKET_H */

