/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LocalGLogger.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 9, 15.45
 */

#ifndef LOCALGLOGGER_H
#define LOCALGLOGGER_H

#include <iostream>
#include <sstream>

#include "GLogger.h"


namespace GServer {

    class LocalGLogger : public GLogger {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** ConsoleGLogger **
         * * Metodas skirtas sukurti LocalGLogger objektui. Sis objektas 
         * Apraso reikalingas funkcijas vietiniam loginimui.
         *  debug- nurodo ar ijungti derinimo inforamcijos spausdinima ar ne. 
         * Placiau const bool DEBUG*/
        LocalGLogger(bool debug);
        
        virtual ~LocalGLogger();
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /* Pranesimu tipu isvardijimas ir priskirimas tam tirkai reiksmei*/
        enum LOGLEVEL {
            INFO = 0,   // Informacinis pranesimas
            ERROR = 1,  // Klaidos pranesimas
            DEBUG = 9   // Derinimo informacijos pranesimas
        };
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /* formMessage
         * Meotdas skirtas formuoti gauta pranesima rasymui i pranesimu faila.
         *  className - klases vardas, kuri kviecia sia funckija
         *  message- zinute kuri bus pranesama
         *  type- zinutes tipas, ziureti enumeratoriu
         *  resultString- objektas, i kuri bus irasoma zinute */
        void formMessage(std::string className, std::string message, int type, 
        std::string & resultString);
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        std::stringstream messageBuilder;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* LOCALGLOGGER_H */

