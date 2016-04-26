/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConsoleGLogger.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 9, 15.16
 */

#ifndef CONSOLEGLOGGER_H
#define CONSOLEGLOGGER_H

#include <string>
#include "LocalGLogger.h"

namespace GServer {

    class LocalGLogger;
    
    class ConsoleGLogger : public LocalGLogger {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** ConsoleGLogger **
         * * Metodas skirtas sukurti ConsoleGLogger objektui. Sis objektas 
         * isvesti informacija i konoles langa.
         *  debug- nurodo ar ijungti derinimo inforamcijos spausdinima ar ne. 
         * Placiau const bool DEBUG*/
        ConsoleGLogger(bool debug = true);

        virtual ~ConsoleGLogger();

        /* logInfo
         * Metodas skirtas pranesti informacini pranesima */
        virtual void logInfo(std::string className, std::string message);

        /* logError
         * Metodas skirtas pranesti klaidos pranesima */
        virtual void logError(std::string className, std::string message);

        /* logDebug
         * Metodas skirtas pranesti derinimo pranesima */
        virtual void logDebug(std::string className, std::string message);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}
#endif /* CONSOLEGLOGGER_H */

