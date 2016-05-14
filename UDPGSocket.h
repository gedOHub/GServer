/* 
 * File:   UDPGSocket.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 23, 00.31
 */

#ifndef UDPGSOCKET_H
#define UDPGSOCKET_H

#include "GSocket.h"
#include "structures.h"
#include "GConfig.h"
#include "GCommandExecution.h"

namespace GServer {

    class GCommandExecution;

    class UDPGSocket : public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        UDPGSocket(GServer::GConfig* conf, GLogger* logger,
                GCommandExecution* command);
        virtual ~UDPGSocket();

        /** reciveData **
         * Metodas skirtas gauti duomenis is tinklo. Rezultatas- gautu duomenu
         * kiekis. 
            buffer- nuoroda i buferi kuri gauti
            size- nurodoma kiek duomenu gauti*/     
        virtual int reciveData(char* buffer, int size);

        /** sendData **
         * Meotdas skirtas issiuti duomenis i tinkla per si socketa. Sia 
         * funkcija turi igyvendinti kiekvienas protokolas savaip. Rezultatas-
         * issiustu duomenu kiekis. 
         *  socketFd- socketo i kuri siusi nuemris
            data- suformuoti duomenys, kurie bus issiunciami*/
        virtual int sendData(char * data, int size);

        /*** returnClientAddressInfo ***
         * Metodas sksirtras grazinti kliento adreso informacijos strukturai */
        sockaddr_storage returnClientAddressInfo();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /*** commands ***
         * Kintamasis skirtas saugoti nuoroda i komandu apdorojimo objekta */
        GCommandExecution* commands;

        /*** serverStorage ***
         * Kintamasis skirtas saugoti adreso inforamcija */
        struct sockaddr_storage serverStorage;

        /*** addr_size ***
         * Kintamasis skirtas saugoti adreso inforamcijos dydi */
        socklen_t addr_size = sizeof serverStorage;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** listen **
         * Metodas sksirtas pradeti klausimuisi klientu prisjungimu nurodytu 
         * prievadu. Placiau: http://linux.die.net/man/2/listen
         * UDP nepaliko listen saukinio */
        virtual void listenSocket();
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####

    };
}
#endif /* UDPGSOCKET_H */

