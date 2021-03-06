/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GLoggerFactory.h
 * Author: gedas
 *
 * Created on Pirmadienis, 2016, kovas 28, 23.58
 */

#ifndef GLOGGERFACTORY_H
#define GLOGGERFACTORY_H

#include <libconfig.h>
#include "GLogger.h"
#include "FileGLogger.h"
#include "exitCodes.h"
#include "ConsoleGLogger.h"
#include <map>

namespace GServer {

    /* makeLogger
     * Statinis metodas, kuris sukuria objekta pagal parametrus, patalpintus 
     * konfiguracinaime faile ir grazina tolimesniam naudojimui.
     *  Config- libconfig kintamasis, kurio pagalba ieskoma reikalingu 
     * nustatymu konfiguraciniame faile */
    static GLogger *makeLogger(GServer::GConfig * conf) {
        using namespace std;

        /* configMap
         * Kintamsis skirtas isreksti konfiguratines reiksmes per integer 
         * kintamuosius. Naudojama switch strukturoje */
        map<string, int> configMap;
        // Nustatau galimas konfiguracijas
        configMap.insert(std::pair<std::string, int>("SQL", 1));
        configMap.insert(std::pair<std::string, int>("FILE", 2));
        configMap.insert(std::pair<std::string, int>("SYSLOG", 3));
        configMap.insert(std::pair<std::string, int>("CONSOLE", 4));

        try {
            // Gaunu pasirinkima pagal ID
            int temp = -1;
            std::string confName = "LOGGER";
            temp = configMap[conf->getStringSetting(confName)];

            // Tikrinu kas pasirinkta
            switch (temp) {
                    // Norima loginti viska i SQL baze
                case 1:
                    //TODO: Igyvendinti SQL loginima
                    cout << "Pranesimus rodysiu SQL serveryje" << endl;
                    cerr << "Neigyvendinta" << endl;
                    return NULL;
                    break;
                case 2:
                    cout << "Pranesimus rodysiu faile" << endl;
                    return new GServer::FileGLogger(
                            conf->getStringSetting("LOGGER_FILE_PATH"),
                            conf->getBoolSetting("DEBUG"));
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
                    return new GServer::ConsoleGLogger(
                            conf->getIntSetting("DEBUG"));
                    break;
                default:
                    cerr << "Gauta nezinoma LOGGER reiksme" << endl;
                    exit(GServer::EXIT_CODES::UNKNOWN_CONFIG_VALUE);
                    break;
            }
        } catch (int e) {
            // Pranesu apie gauta klaida
            cerr << "GLogger::makeLogger gauta klaida: " << e << endl;
        }
    }
}

#endif /* GLOGGERFACTORY_H */

