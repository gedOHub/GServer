/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPGSocket.h
 * Author: gedas
 *
 * Created on Antradienis, 2016, balandis 12, 04.41
 */

#ifndef SCTPGSOCKET_H
#define SCTPGSOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#include "GSocket.h"
#include "exitCodes.h"


/* Pagal: http://www.ibm.com/developerworks/library/l-sctp/ */

namespace GServer {

    class SCTPGSocket :public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        SCTPGSocket(GConfig* conf, GLogger* logger, GCommandExecution* command);
        virtual ~SCTPGSocket();
        
        /** reciveData **
         * Metodas skirtas gauti duomenis is tinklo. Rezultatas- gautu duomenu
         * kiekis. 
            buffer- nuoroda i buferi kuri gauti
            size- nurodoma kiek duomenu gauti*/
        virtual int reciveData( char* buffer, int size );
        
        /** sendData **
         * Meotdas skirtas issiuti duomenis i tinkla per si socketa. Sia 
         * funkcija turi igyvendinti kiekvienas protokolas savaip. Rezultatas-
         * issiustu duomenu kiekis. 
         *  socketFd- socketo i kuri siusi nuemris
            data- suformuoti duomenys, kurie bus issiunciami*/
        virtual int sendData(char * data, int size);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /*** serverStorage ***
         * Kintamasis skirtas saugoti adreso inforamcija */
        struct sockaddr_storage serverStorage;
        
         /*** addr_size ***
         * Kintamasis skirtas saugoti adreso inforamcijos dydi */
        socklen_t addr_size = sizeof serverStorage;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** recive **
         * Metodas skirtas gauti duomenis is tinklo. Sia funkcija turi 
         * igyvendinti kiekvienas protokolas savaitp. Rezultatas- gautu 
         * duomenu kiekis. */
        //virtual int reciveData();
        
        /** createSocket **
         * Metodas skirtas sukurti sistemos resursaui- socket. Si metoda 
         * realizuoja kiekviena vaiko klase atskirai. 
            socketFamily- kokio tipo tinklu bus bendraujama
            socketType- kokiu principu bus bendraujama
            socketProtocol- kokiu protokolu bus bendraujama
            socketFlag- papildomi socket nustatymai
            result - kintamsis saugnatis gautus rezultatus is IP ir PORT 
         * kombinacijos
         Placiau: https://msdn.microsoft.com/en-us/library/windows/desktop/ms737530(v=vs.85).aspx*/
        /*virtual int createSocket(char* ip, char* port, int socketFamily,
                int socketType, int socketProtocol, int socketFlag, 
                addrinfo *& result);
         * */
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* SCTPGSOCKET_H */

