/* 
 * File:   GSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.51
 */

#ifndef GSOCKET_H
#define GSOCKET_H

#include <vector>
#include <libconfig.h>
#include "GLogger.h"

namespace GServer {
    class GSocket: public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        GSocket( libconfig::Config* conf, GLogger* logger );
        virtual ~GSocket();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /** buffer **
         * Kintamasis skirtas saugoti gaunama ir siunciama informacija i tinkla. 
         * Maksimalu buferio dydi nusako nustatymu faile saugoma reiksme 
         * MAX_SCOKET_BUFFER_SIZE */
        std::vector<char> buffer;

        /** socket_descriptor **
         * Kintamasis skirtas saugoti failo deskriptoriaus numeri, kuris naudojamas 
         * bendrvmui su tinklo klientu. Numatyta reiksme- -1.
         * Placiau- https://en.wikipedia.org/wiki/File_descriptor */
        int socket_descriptor;

        /* logger
         * Kintamasis saugantis nuoroda i pranesimu rasimo objekta */
        GLogger* logger;
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        /** createSocket **
         * Metodas skirtas sukurti sistemos resursaui- socket. Si metoda realizuoja
         * kiekviena vaiko klase atskirai. */
        virtual int createSocket(){};

        // ##### END Metodai #####
    };
}

#endif /* GSOCKET_H */

