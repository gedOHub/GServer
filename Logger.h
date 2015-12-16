/* 
 * File:   Logger.h
 * Author: gedas
 *
 * Created on April 7, 2015, 9:50 PM
 */

#ifndef LOGGER_H
#define	LOGGER_H

#include <iostream>
#include <fstream>
#include "string.h"
#include <syslog.h>
#include "CONSTANTS.h"

#define SYSLOG 0
#define FILE 1

using namespace std;

class Logger {
public:
    
    /*
     * Loginama i SYSLOG
     */
    Logger(bool d = false);
    
    /*
     * Ijungia derinimo pranesimus
     */
    void EnableDebug();
    
    /*
     * Pranesimas, kuris priskiriamas prie informacijos
     * @param info - informacinis pranesiams
     */
    void WriteInfo(string info);
    
    /*
     * Pranesimas, kuris priskiramas prie kalidu
     * @param error - klaidos pranesimas
     */
    void WriteError(string error);
    
    /*
     * Pranesimas, kuris priskiriamas prie derinimo
     * @param debug - derinimo pranesiams
     */
    void WriteDebug(string debug);
    
    virtual ~Logger();
private:
    bool debug; // Nusako ar rodomi derinimo pranesimai
};

#endif	/* LOGGER_H */

