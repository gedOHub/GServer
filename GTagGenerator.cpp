/* 
 * File:   TagGenerator.cpp
 * Author: developer
 * 
 * Created on May 7, 2014, 11:07 PM
 */

#include "GTagGenerator.h"
#include "GTunnelContainer.h"
#include "GLogger.h"

GServer::GTagGenerator::GTagGenerator( GServer::GLogger* logger ) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":TagGenerator";
    // Priskiriu pranesimu isvedimu objekta
    this->logger = logger;
    // Nustatau kritines reiksmes
    this->MIN = 1000;
    this->MAX = 65534;
    // Nustatau pradine reiksme
    this->Reset();
    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::GTagGenerator::~GTagGenerator() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

void GServer::GTagGenerator::Reset() {
    this->logger->logDebug(this->className, "Nustatau skaitliuka i pradine "
            "maziausia reiksme: " + std::to_string(this->MIN));
    this->tag = this->MIN;
}

int GServer::GTagGenerator::Generate(GTunnelContainer* tunnels) {
    if (this->tag >= MAX)
        this->Reset();

    // Padidinam paskutine zyme
    this->tag = this->tag + 1;

    // Tikrinam ar tokia jau yra naudojama
    while (tunnels->IsClient(this->tag)) {
        // Jei naudojama tada dar didinam
        this->tag = this->tag + 1;

        if (this->tag >= MAX)
            this->Reset();
    }

    this->logger->logDebug(this->className, "Sugeneruota reiksme: " + 
            std::to_string(this->tag));
    return this->tag;
}

