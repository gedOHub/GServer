/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConsoleGLogger.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 9, 15.16
 */

#include "ConsoleGLogger.h"

GServer::ConsoleGLogger::ConsoleGLogger(bool debug) :
LocalGLogger(debug) {
    // Nustatau pavadinima
    this->className = this->className + ":ConsoleGLogger";
    this->logDebug(this->className, "Objektas sukurtas");
}

GServer::ConsoleGLogger::~ConsoleGLogger() {
    this->logDebug(this->className, "Objektas sunaikinamas");
}

void GServer::ConsoleGLogger::logDebug(std::string className, std::string message) {
    using namespace std;
    if (this->DEBUG) {
        // Laikinas stringas
        string tempString;
        // Formuoju pranesimu eilute
        this->formMessage(className, message, DEBUG, tempString);
        // Skelbiu pranesimo eilute
        cout << tempString;
    }
}

void GServer::ConsoleGLogger::logError(std::string className, std::string message) {
    using namespace std;
    // Laikinas stringas
    string tempString;
    // Formuoju pranesimu eilute
    this->formMessage(className, message, ERROR, tempString);
    // Skelbiu pranesimo eilute
    cout << tempString;
}

void GServer::ConsoleGLogger::logInfo(std::string className, std::string message) {
    using namespace std;
    // Laikinas stringas
    string tempString;
    // Formuoju pranesimu eilute
    this->formMessage(className, message, INFO, tempString);
    // Skelbiu pranesimo eilute
    cout << tempString;
}