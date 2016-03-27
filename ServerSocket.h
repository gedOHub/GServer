/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 01.30
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

class ServerSocket {
public:
    // ----- Kintamieji -----
    // ----- END Kintamieji -----
//##############################################################################    
    // ----- Metodai -----
    ServerSocket();
    virtual ~ServerSocket();
    // ----- END Metodai -----
private:
    // ----- Kintamieji -----
    /* file_deskriptor
     * Kintamasis skirtas saugoti socket failo deskritproaius reiksme. 
     * Naudojamas tinklo operacijose (duomnu siuntimas, gavimas ir darbui su 
     * prisijungusiais klientais). Numatyta reiksme -1*/
    int file_deskriptor;
    
    /* buffer
     * Char masyvo kintamasis skirtas saugoti gaunama ir siunciama informacija 
     * i tinkla. Masyvas isvalomas destruktoriuje. Maksimalus dydis apibreziamas 
     * konfiguraciniame faile- MAX_SERVER_SCOKET_BUFFER_SIZE. Numatyta 
     * reiksme- NULL */
    char* buffer;
    
    /* IP
     * Kintamasis skirtas saugoti IP adresa, kuriuo bus klausomasi ateinanciu 
     * jungciu. Numatyta reiksme- 0.0.0.0 */
    // ----- END Kintamieji -----
//##############################################################################    
    // ----- Metodai -----
    
    // ----- END Metodai -----
};

#endif /* SERVERSOCKET_H */

