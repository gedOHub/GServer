/* 
 * File:   TCPGSocket.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#ifndef TCPGSOCKET_H
#define TCPGSOCKET_H

#include "GSocket.h"
#include "GCommandExecution.h"


namespace GServer {

    class TCPGSocket : public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** TCPSocket ***
         * Metodas skirtas sukurti TCPSocket tipo objektui. 
            conf- nuoroda i objekta, kuris dirba su konfiguraciniu failu
            logger- nuorda i objekta, kuris rupinasi pranesimu isvedimu
            command- nuoroda i objekta, kuris rupinasi komandu aprodojimu*/
        TCPGSocket(GServer::GConfig* conf, GLogger* logger, 
                GCommandExecution* command);
        virtual ~TCPGSocket();
        
        /** reciveData **
         * Metodas skirtas gauti duomenis is tinklo. Rezultatas- gautu duomenu
         * kiekis. 
            buffer- nuoroda i buferi kuri gauti
            size- nurodoma kiek duomenu gauti*/
        virtual int reciveData( char* buffer, int size );
        // ##### END Metodai #####
    protected:
        
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** send **
         * Meotdas skirtas issiuti duomenis i tinkla per si socketa. Sia 
         * funkcija turi igyvendinti kiekvienas protokolas savaip. Rezultatas-
         * issiustu duomenu kiekis. 
            data- suformuoti duomenys, kurie bus issiunciami
            size- duomenu kiekis, kiek reikia issiusti is nurodyto buferio */
        virtual int sendData(char * data, int size);
        
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

