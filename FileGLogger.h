/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileGLogger.h
 * Author: gedas
 *
 * Created on Pirmadienis, 2016, kovas 28, 22.32
 */

#ifndef FILEGLOGGER_H
#define FILEGLOGGER_H

#include <fstream>
#include <string>
#include "LocalGLogger.h"

namespace GServer {

    class FileGLogger : public LocalGLogger {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        /** FileGLOgger **
         * metodas skitas sukurti objekta, kuris pranesimus raso i nurodyta 
         * faila. 
         *  filePath- kelias iki failo, i kuri norima rasyti pranesimus
         *  debug- jungtis kuri ijungia arba isungia derinimo inforamcijos 
         * rasyma i pranesimu faila */
        FileGLogger(std::string filePath, bool debug = true);

        virtual ~FileGLogger();

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
    private:
        // ##### Kintamieji #####
        /* file_descriptor
         * Objektas skirtas rasyti duomensi i faila nurodyta konfiguracinaime 
         * faile LOGGER_FILE_PATH nustatyme. 
         * Placiau: http://www.cplusplus.com/reference/fstream/ofstream/*/
        std::ofstream* logFile;

        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        /* createFileDescriptor
         * Metodas skirtas nuskaityti nuskaitymus is konfiguracinio failo ir 
         * atverti faila pranesimu rasimui nurodytu keliu. Skaityti apie 
         * file_descriptor 
            fielPath- kelias ini pranesimu rasymo failo*/
        void openLogFile(std::string fielPath);

        // ##### END Metodai #####
    };
}

#endif /* FILEGLOGGER_H */

