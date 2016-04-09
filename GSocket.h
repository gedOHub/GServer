/* 
 * File:   GSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.51
 */

#ifndef GSOCKET_H
#define GSOCKET_H

#include <vector>
#include "GLogger.h"
#include "GConfig.h"

namespace GServer {

    class GSocket : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        GSocket(GConfig* conf, GLogger* logger);
        virtual ~GSocket();

        /** send **
         * Meotdas skirtas issiuti duomenis i tinkla per si socketa. Sia 
         * funkcija turi igyvendinti kiekvienas protokolas savaip. Rezultatas-
         * issiustu duomenu kiekis. 
            data- suformuoti duomenys, kurie bus issiunciami*/
        virtual int send(vector<char>* data);

        /** recive **
         * Metodas skirtas gauti duomenis is tinklo. Sia funkcija turi 
         * igyvendinti kiekvienas protokolas savaitp. Rezultatas- gautu 
         * duomenu kiekis.
         *  data- buferis i kuri bus gaunami duomenys */
        virtual int recive(vector<char>* data);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /** buffer **
         * Kintamasis skirtas saugoti gaunama ir siunciama informacija i tinkla. 
         * Maksimalu buferio dydi nusako nustatymu faile saugoma reiksme 
         * MAX_SCOKET_BUFFER_SIZE */
        std::vector<char> buffer;

        /** socket_descriptor **
         * Kintamasis skirtas saugoti failo deskriptoriaus numeri, kuris 
         * naudojamas bendrvmui su tinklo klientu. Numatyta reiksme- -1.
         * Placiau- https://en.wikipedia.org/wiki/File_descriptor */
        int socket_descriptor;

        /** logger
         * Kintamasis saugantis nuoroda i pranesimu rasimo objekta */
        GLogger* logger;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** createSocket **
         * Metodas skirtas sukurti sistemos resursaui- socket. Si metoda 
         * realizuoja kiekviena vaiko klase atskirai. 
            config- objektas dirbantis su nustatymu failu*/
        virtual int createSocket(GConfig* conf);

        /** resizeBuffer **
         * Metodas skirtas pertvarkyti buferio dydi i nurodyta. Buferis negali 
         * buti didesnes reiksmes nei nurodyta konfiguracinaime faile. Metodo 
         * rezultatas- naujas pertvarkytas dydis.
            newSize- naujas pageidaujamas buferio dydis*/
        int resizeBuffer(int newSize);

        /** */
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /** MAX_BUFFER_SIZE **
         * Konstanta nurodanti koks maksimalus gali buti buferio dydis */
        const int MAX_BUFFER_SIZE;

        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** setSize **
         * Metodas skirtas nustatyti buferio dydziui. Grazinama reiksme- 
         * naujas buferio dydis.
            newSize- naujas pageidaujamas buferio dydis*/
        int setBufferSize(int newSize);
        // ##### END Metodai #####
    };
}

#endif /* GSOCKET_H */

