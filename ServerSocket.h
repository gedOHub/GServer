/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 00.26
 */

#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <string>

class ServerSocket {
public:
    ServerSocket();
    ServerSocket(const ServerSocket& orig);
    virtual ~ServerSocket();
    
    // Grazinu ServerSocket pagal protokola
    static ServerSocket *make_ServerSocket ( std::string PROTOCOL, std::string IP, std::string PORT );
private:
    // ----- KINTAMIEJI -----
    /* Dinaminio buferio kintamasis skirtas saugoti gaunama ar issiunciama 
     * inforamcija. Is pradziu sukuriamas 5MB dydzio buferis. Esant reikalui
     * Darbo metu didinamas. Maksimali reiksme apibreziama konfiguracijos faile
     * BUFFER_MAX_SIZE kintamojo. */
    char * buffer;
    // ----- END KINTAMIEJI -----
};

#endif /* SERVERSOCKET_H */

