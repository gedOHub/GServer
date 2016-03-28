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
#include <map>
#include <ctime>
#include "../GObject.h"

using namespace std;
    namespace GServer {
    class GLogger : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        /* GLogger
         * Metodas skirtas sukurti GLogger objektui. Sis objektas atlieka pranesimu 
         * prasima i konsole. GLogger tipas nustatymas pagal LOGGER nustatyma 
         * konfiguraciniame faile.
         *  Config- libconfig kintamasis, kuris dirba su konfiguraciniu failu */
        GLogger( libconfig::Config* confuration );

        /* ~GLogger
         * Metodas skirtas suanikinti GLogger objektui. */
        virtual ~GLogger();

        /* makeLogger
         * Statinis metodas, kuris sukuria objekta pagal parametrus, patalpintus 
         * konfiguracinaime faile ir grazina tolimesniam naudojimui.
         *  Config- libconfig kintamasis, kurio pagalba ieskoma reikalingu nustatymu
         *  konfiguraciniame faile */
        static GLogger *makeLogger(libconfig::Config*);

        /* logInfo
         * Metodas skirtas pranesti apie informacija */
        virtual void logInfo(std::string message);

        /* logError
         * Metodas skirtas pranesti apie klaida */
        virtual void logError(std::string message);

        /* logDebug
         * Metodas skirtas pranesti derinimo informacijai */
        virtual void logDebug(std::string message);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /* debug
         * Kintamasis skirtas ijungti arba isjungti derinimo informacijos 
         * spausdinimui. Reiksme nustatoma konfiguraciniame faile, DEBUG lauke. 
         * Galimos reiksmes:
         *  DEBUG=1 - derinimo informacijos spausdinimas ijungtas
         *  DEBUG=0 - derinimo informacijos spausdinimas isjungtas
         * Numatyta reiksme- 0. */
        bool debug;
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        /* getTime
         * Metodas skirtas grazinti dabartini laika formatu: 
         * YYYY-MM-DD HH:mm:ss */
        std::string getTime();
        // ##### END Metodai #####

    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };

}
#endif /* GLOGGER_H */

