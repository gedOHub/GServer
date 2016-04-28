/* 
 * File:   GLogger.h
 * Author: gedas
 *
 * Created on Pirmadienis, 2016, kovas 28, 16.44
 */

#ifndef GLOGGER_H
#define GLOGGER_H

#include <libconfig.h>
#include <iostream>
#include <string.h>
#include <ctime>
#include <sstream>
#include "GObject.h"

using namespace std;

namespace GServer {

    // Del vienas kito prideji
    class GConfig;

    class GLogger : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /* GLogger
         * Metodas skirtas sukurti GLogger objektui. Sis objektas apraso sasaja 
         * skirta pranesimu rasimui i pranesimu faila. GLogger tipas nustatymas 
         * pagal LOGGER nustatyma konfiguraciniame faile.
         *  debug- nurodo ar ijungti derinimo inforamcijos spausdinima ar ne. 
         * Placiau const bool DEBUG*/
        GLogger(bool debug);

        /* ~GLogger
         * Metodas skirtas suanikinti GLogger objektui. */
        virtual ~GLogger();

        /* logInfo
         * Metodas skirtas pranesti apie informacija */
        virtual void logInfo(std::string className, std::string message) {
        };

        /* logError
         * Metodas skirtas pranesti apie klaida */
        virtual void logError(std::string className, std::string message) {
        };

        /* logDebug
         * Metodas skirtas pranesti derinimo informacijai */
        virtual void logDebug(std::string className, std::string message) {
        };
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /* debug
         * Kintamasis skirtas ijungti arba isjungti derinimo informacijos 
         * spausdinimui. Reiksme nustatoma konfiguraciniame faile, DEBUG lauke. 
         * Galimos reiksmes:
         *  DEBUG=1 - derinimo informacijos spausdinimas ijungtas
         *  DEBUG=0 - derinimo informacijos spausdinimas isjungtas
         * Numatyta reiksme- 1. */
        const bool DEBUG;


        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /* getTime
         * Metodas skirtas grazinti dabartini laika formatu: 
         * YYYY-MM-DD HH:mm:ss */
        std::string getTime();

        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };

}
#endif /* GLOGGER_H */

