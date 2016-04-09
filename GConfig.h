/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Config.h
 * Author: gedas
 *
 * Created on Antradienis, 2016, balandis 5, 23.10
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "GObject.h"
#include "GLogger.h"
#include <libconfig.h>
#include <string>

namespace GServer {
    
    class GLogger;
    
    class GConfig : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        GConfig( GServer::GLogger* logger );
        virtual ~GConfig();
        /** getSetting **
         * Metodas skirtas grazinti prasomo nustatymo reiksme, stringo pavidale
         *  name- nurimo nustatymo pavadinimas */
        std::string getStringSetting(std::string name);
        int getIntSetting(std::string name);
        bool getBoolSetting(std::string name);
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /** CONFIG_FILE_NAME **
         * Kintamasis skirtas saugoti konfiguracinio failo pavadinima */
        const std::string CONFIG_FILE_NAME;
        
        /** logger **
         * Kintamasis skirtas saugoti nuoroda i pranesimu rasymo objekta */
        GServer::GLogger* logger;
        
        /** conf **
         * Kintamasis skirtas saugoti nuoroda i konfiguracinio failo nuskaitymo 
         * objekta */
        libconfig::Config* conf;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** openConfigFile **
         * Metodas skritas atverti ir pradeti nustatymu nuskaityma is nustatymu 
         * failo. */
        void openConfigFile();
        
        /** openSetting **
         * Metodas skirtas nuskaityti norimą nustatyma.
         *  name- ieskomo nustatymu pavadinimas
         *  returnValue - kintasis, i kuri bus grazinama nuskaityta reiksme */
        template<typename TYPE>
        void openSetting(std::string name, TYPE &returnValue);
        // ##### END Metodai #####
    };
}

#endif /* CONFIG_H */

