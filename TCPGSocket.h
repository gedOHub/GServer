/* 
 * File:   TCPGSocket.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#ifndef TCPGSOCKET_H
#define TCPGSOCKET_H

#include "GSocket.h"


namespace GServer {

    class TCPGSocket : public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        TCPGSocket(GServer::GConfig* conf, GLogger* logger);
        virtual ~TCPGSocket();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** send **
         * Meotdas skirtas issiuti duomenis i tinkla per si socketa. Sia 
         * funkcija turi igyvendinti kiekvienas protokolas savaip. Rezultatas-
         * issiustu duomenu kiekis. 
         *  socketFd- socketo i kuri siusi nuemris
            data- suformuoti duomenys, kurie bus issiunciami*/
        virtual int sendData(int socketFd, vector<char>* data);
        
        /** recive **
         * Metodas skirtas gauti duomenis is tinklo. Sia funkcija turi 
         * igyvendinti kiekvienas protokolas savaitp. Rezultatas- gautu 
         * duomenu kiekis.
         *  socketFd- socketo is kurio skaitoma nuemris
         *  data- buferis i kuri bus gaunami duomenys */
        virtual int reciveData();
        
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* TCPGSOCKET_H */

