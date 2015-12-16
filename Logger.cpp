/* 
 * File:   Logger.cpp
 * Author: gedas
 * 
 * Created on April 7, 2015, 9:50 PM
 */

#include "Logger.h"

/*
 * Loginama i SYSLOG
 */
Logger::Logger(bool d){
    debug = d;
    openlog(APP_NAME, LOG_PID, LOG_USER);
}

/*
 * Ijungia derinimo pranesimus
 */
void Logger::EnableDebug(){
    this->debug = true;
}

/*
 * Pranesimas, kuris priskiriamas prie informacijos
 * @param info - informacinis pranesiams
 */
void Logger::WriteInfo(string info){
    syslog(LOG_INFO, "%s", info.c_str());
}

/*
 * Pranesimas, kuris priskiramas prie kalidu
 * @param error - klaidos pranesimas
 */
void Logger::WriteError(string error){
    syslog(LOG_ERR, "%s", error.c_str());
}

/*
 * Pranesimas, kuris priskiriamas prie derinimo
 * @param debug - derinimo pranesiams
 */
void Logger::WriteDebug(string debugMsg){
    if(debug)
        syslog(LOG_DEBUG, "%s", debugMsg.c_str());
}

Logger::~Logger(){
    closelog();
}

