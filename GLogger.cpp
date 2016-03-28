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

GServer::GLogger::GLogger( libconfig::Config* conf ) {
    // Pataisau klases pavadinima
    this->className = "GLogger";
    // Bandau nuskaityti DEBUG reiksme is nustatymu failo
    try{
        this->debug = conf->lookup("DEBUG");
        this->logDebug(this->className, "Nuskaityta DEBUG reiksme:");
        this->logDebug(this->className, std::to_string(this->debug) );
    } catch( int e ){
        // Pranesimas apie nepavykusi nuskaityma DEBUG reiksmes
        this->logError(this->className, "Nepavyko nuskaityti DEBUG reiksmes");
    }
}

GServer::GLogger::~GLogger() {
}

GServer::GLogger *GServer::GLogger::makeLogger(libconfig::Config* conf){
    using namespace std;
    
    /* configMap
     * Kintamsis skirtas isreksti konfiguratines reiksmes per integer 
     * kintamuosius. Naudojama switch strukturoje */
    map<string, int> configMap;
    // Nustatau galimas konfiguracijas
    configMap.insert(std::pair<std::string,int>("SQL", 1));
    configMap.insert(std::pair<std::string,int>("FILE", 2));
    configMap.insert(std::pair<std::string,int>("SYSLOG", 3));
    configMap.insert(std::pair<std::string,int>("CONSOLE", 4));
    
    try{
        // Gaunu pasirinkima pagal ID
        int temp = -1;
        temp = configMap[conf->lookup("LOGGER").c_str()];
        
        // Tikrinu kas pasirinkta
        switch( temp ){
            // Norima loginti viska i SQL baze
            case 1:
                //TODO: Igyvendinti SQL loginima
                cout << "Pranesimus rodysiu SQL serveryje" << endl;
                cerr << "Neigyvendinta" << endl;
                return NULL;
                break;
            case 2:
                //TODO: Igyvendinti failo loginima
                cout << "Pranesimus rodysiu faile" << endl;
                cerr << "Neigyvendinta" << endl;
                return NULL;
                break;
            case 3:
                //TODO: Igyvendinti syslog loginima
                cout << "Pranesimus rodysiu syslog sistemoje" << endl;
                cerr << "Neigyvendinta" << endl;
                return NULL;
                break;
            case 4:
                cout << "Pranesimus rodysiu terminale" << endl;
                // Kuriu loginima i konsole, pagal factory paterna, placiau: 
                // https://sourcemaking.com/design_patterns/factory_method/cpp/1
                return new GLogger(conf);
                break;
            default:
                cerr << "Gauta nezinoma LOGGER reiksme" << endl;
                return NULL;
                break;
        }
    }catch( int e ){
        // Pranesu apie gauta klaida
        cerr << "GLogger::makeLogger gauta klaida: " << e << endl;
    }
}

void GServer::GLogger::logInfo(std::string className, std::string message){
    std::cout << "[" << this->getTime() << "] INFO [" << className 
            << "] " << message << std::endl;
}

void GServer::GLogger::logError(std::string className, std::string message){
    std::cerr << "[" << this->getTime() << "] ERROR [" << className 
            << "] " << message << std::endl;
}

void GServer::GLogger::logDebug(std::string className, std::string message){
    if(this->debug) {
        std::cerr << "[" << this->getTime() << "] DEBUG [" << className 
            << "] " << message << std::endl;
    }
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
