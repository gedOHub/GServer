/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GCommandExecution.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 23, 14.04
 */

#include "GCommandExecution.h"

GServer::GCommandExecution::GCommandExecution(GLogger* logger, 
        GTagGenerator* tagGenerator) :GObject() {
    // Nustatau objekto pavadinima
    this->className = this->className + ":GCommandExecution";
    // Priskiriu pranesimu isvedimu objekta
    this->logger = logger;
    // Priskiriu zymu generatoriu
    this->tagGenerator = tagGenerator;

    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::GCommandExecution::~GCommandExecution() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

