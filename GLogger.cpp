/*
 * T
#include <iostream>
#include <iostream>
#include <iostream>o change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLogger.cpp
 * Author: gedas
 * 
 * Created on Pirmadienis, 2016, kovas 28, 16.44
 */

#include "GLogger.h"

GServer::GLogger::GLogger( bool debug = 1 ) : DEBUG(debug) {
    // Nustatau pavadinima
    this->className = this->className + ":GLogger";
    this->logDebug(this->className, "Objektas sukurtas");
}

GServer::GLogger::~GLogger() {
    this->logDebug(this->className, "Objektas sunaikinamas");
}

std::string GServer::GLogger::getTime(){
    /* Laiko saugojimo kintamasis milisekundemis 
     * nuo 00:00 hours, Jan 1, 1970 UTC. 
     * Placiau: http://www.cplusplus.com/reference/ctime/time_t/?kw=time_t */
    time_t rawtime;
    
    /* Struktura, sauganti laika sudalinus i atitinkamas sekcijas. 
     * Placiau: http://www.cplusplus.com/reference/ctime/tm/?kw=tm */ 
    struct tm * timeinfo;
    
    /* Buferis, kuriame bus formuojamas laiko atvaizdavimas */
    char buffer[80];

    // Gaunu laika nuo 00:00 hours, Jan 1, 1970 UTC milisekundemis
    time (&rawtime);
    // Isskaidau laika pagal dabartine laiko zona
    timeinfo = localtime(&rawtime);
    // Atvaizduoju laika pagal norima formata
    strftime(buffer,80,"%Y-%m-%d %R:%M:%S",timeinfo);
    // Grazinu suformuota laika
    return std::string(buffer);
}

