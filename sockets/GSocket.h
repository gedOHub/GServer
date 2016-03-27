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
private:
    // ##### Kintamieji #####
    /* buffer
     * Kintamasis skirtas saugoti gaunama ir siunciama informacija i tinkla. 
     * Maksimalu buferio dydi nusako nustatymu faile saugoma reiksme 
     * MAX_SCOKET_BUFFER_SIZE */
    std::vector buffer;
    
    
    
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    // ##### END Metodai #####
};

#endif /* GSOCKET_H */

