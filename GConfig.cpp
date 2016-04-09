/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Config.cpp
 * Author: gedas
 * 
 * Created on Antradienis, 2016, balandis 5, 23.11
 */

#include "GConfig.h"
#include "exitCodes.h"

GServer::GConfig::GConfig(GServer::GLogger* log) : CONFIG_FILE_NAME("server.conf"), GObject() {
    // Nustatau pavadinima
    this->className = this->className + ":GConfig";
    // Nustatau nuoroda i pranesimu objekta
    this->logger = log;
    // Sukuriu nustatymu failo skaitymo objekta
    this->conf = new libconfig::Config();

    // Inicijuoju nustatymu failo skaityma
    this->openConfigFile();
}

GServer::GConfig::~GConfig() {
    this->logger->logDebug(this->className, "Baigiu darba su nustatymu failu");
    this->conf->~Config();
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

std::string GServer::GConfig::getStringSetting(std::string name) {
    std::string returnValue;
    this->openSetting(name, returnValue);
    // Grazinu reiksme
    return returnValue;
}

int GServer::GConfig::getIntSetting(std::string name) {
    int returnValue = 0;
    this->openSetting(name, returnValue);
    // Grazinu reiksme
    return returnValue;
}

bool GServer::GConfig::getBoolSetting(std::string name) {
    bool returnValue;
    this->openSetting(name, returnValue);
    // Grazinu reiksme
    return returnValue;
}

void GServer::GConfig::openConfigFile() {
    // Nuskaitau konfiguracini faila
    try {
        conf->readFile(this->CONFIG_FILE_NAME.c_str());
        this->logger->logDebug(this->className, "Atvertas nustatymu failas: "
                + this->CONFIG_FILE_NAME);
    } catch (const libconfig::FileIOException &fioex) {
        // Pranesu klaida
        this->logger->logError(this->className,
                "Nepavyko atverti konfiguracinio failo: " +
                this->CONFIG_FILE_NAME);
        // Baigiu programa su atitinkamu iseigos kodu
        exit(GServer::EXIT_CODES::ERROR_OPENNING_CONFIG_FILE);
    } catch (libconfig::ParseException &pex) {
        // Pranesu klaida
        this->logger->logError(this->className,
                "Skaitatn faila: " + this->CONFIG_FILE_NAME +
                " ivyko klaida: " + std::to_string(pex.getLine()) + " - " + pex.getError());
        // Baigiu programa su atitinkamu iseigos kodu
        exit(GServer::EXIT_CODES::ERROR_IN_CONFIG_FILE);
    }
}

template<typename TYPE>
void GServer::GConfig::openSetting(std::string name, TYPE &returnValue) {
    try {
        // Tikrinu ar yra norima reiksme
        if (!this->conf->lookupValue(name, returnValue)) {
            // Nerasta nustaytmu reiksme
            this->logger->logError(this->className,
                    "Nerastas konfiguracijos raktas: " + name);
            exit(GServer::EXIT_CODES::CONFIG_NOT_FOUND);
        }
        //Formuoju pranesima
        std::ostringstream ss;
        ss << "Nuskaityta nustatymo reiksme: " << name << ":" << returnValue;
        this->logger->logDebug(this->className, ss.str());
    } catch (int e) {
        this->logger->logError(this->className,
                "Klaida nuskaitant " + name + " nustatymo reiksme. Klaidos kodas: "
                + std::to_string(e));
        exit(GServer::EXIT_CODES::UNABLE_READ_CONFIG);
    }
}


