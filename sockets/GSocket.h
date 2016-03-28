/* 
 * File:   GSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.51
 */

#ifndef GSOCKET_H
#define GSOCKET_H

#include <vector>

class GSocket {
public:
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    GSocket();
    GSocket(const GSocket& orig);
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
    
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    /** getSocket **
     * Metodas skirtas sukurti sistemos resursaui- socket. Si metoda realizuoja
     * kiekviena vaiko klase atskirai. */
    virtual int getSocket();
    
    // ##### END Metodai #####
};

#endif /* GSOCKET_H */

