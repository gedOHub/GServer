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
#include <sstream>
#include "GObject.h"

using namespace std;

    namespace GServer {
    class GLogger : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /* GLogger
         * Metodas skirtas sukurti GLogger objektui. Sis objektas atlieka 
         * pranesimu prasima i konsole. GLogger tipas nustatymas pagal LOGGER 
         * nustatyma konfiguraciniame faile.
         *  Config- libconfig kintamasis, kuris dirba su konfiguraciniu failu */
        GLogger( libconfig::Config* confuration );

        /* ~GLogger
         * Metodas skirtas suanikinti GLogger objektui. */
        virtual ~GLogger();

        /* logInfo
         * Metodas skirtas pranesti apie informacija */
        virtual void logInfo(std::string className, std::string message);

        /* logError
         * Metodas skirtas pranesti apie klaida */
        virtual void logError(std::string className, std::string message);

        /* logDebug
         * Metodas skirtas pranesti derinimo informacijai */
        virtual void logDebug(std::string className, std::string message);
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
        
        /* messageBuilder
         * Objektas, stringstream tipo, kurio pagalba formuojamos zinutes i 
         * pranesimu faila. 
         * Placiau: http://www.cplusplus.com/reference/sstream/stringstream/*/
        std::stringstream  messageBuilder;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /* getTime
         * Metodas skirtas grazinti dabartini laika formatu: 
         * YYYY-MM-DD HH:mm:ss */
        std::string getTime();
        
        /* formMessage
         * Meotdas skirtas formuoti gauta pranesima rasymui i pranesimu faila.
         *  className - klases vardas, kuri kviecia sia funckija
         *  message- zinute kuri bus pranesama
         *  type- zinutes tipas, ziureti enumeratoriu
         *  resultString- objektas, i kuri bus irasoma zinute */
        void formMessage(std::string className, std::string message, int type, 
        std::string & resultString);
        // ##### END Metodai #####
        /* Pranesimu tipuisvardijimas ir priskirimas tam tirkai reiksmei*/
        enum {
            INFO = 0,   // Informacinis pranesimas
            ERROR = 1,  // Klaidos pranesimas
            DEBUG = 9   // Derinimo informacijos pranesimas
        };
        
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };

}
#endif /* GLOGGER_H */

