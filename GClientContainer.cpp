/* 
 * File:   ClientContainer.cpp
 * Author: developer
 * 
 * Created on April 24, 2014, 4:05 PM
 */

#include "GClientContainer.h"
#include "structures.h"
#include <iostream>

GServer::GClientContainer::GClientContainer(GLogger* logger) {
    // Nustatau pavadinima
    this->className = this->className + ":GClientContainer";
    // Nustatau nuoroda i pranesimu objekta
    this->logger = logger;
    // Sukriu spausdinimo masyva
    this->printBuffer = new char[OneMBofChar];
    
    this->logger->logDebug(this->className, "Objektas sekmingai sukurtas");
}

GServer::GClientContainer::~GClientContainer() {
    this->logger->logDebug(this->className, "Isvalau klientu konteineri");
    this->Container.clear();
    
    this->logger->logDebug(this->className, "Naikinu spausdinimo buferi");
    delete this->printBuffer;
    
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

Client GServer::GClientContainer::Add(Client client) {
    this->logger->logDebug(this->className, "Pridedu klienta:\n" +
            this->printClientInfo(client));
    this->Container.push_back(client);
    return client;
}

Client GServer::GClientContainer::Add(int socket, char sritis[MAX_COMPUTERNAME_LENGTH + 1],
        char kompiuteris[MAX_COMPUTERNAME_LENGTH + 1],
        char naudotojas[MAX_COMPUTERNAME_LENGTH + 1]) {

    Client temp;
    temp.id = socket;
    // Kopijuojam reiksmes
    memcpy(temp.domainName, sritis, sizeof temp.domainName);
    memcpy(temp.pcName, kompiuteris, sizeof temp.pcName);
    memcpy(temp.userName, naudotojas, sizeof temp.userName);

    return this->Add(temp);
}

void GServer::GClientContainer::DeleteByID(int id) {
    std::list<Client>::iterator i;

    for (i = this->Container.begin(); i != this->Container.end(); i++) {
        if (i->id == id) {
            this->logger->logDebug(this->className, "Salinu klienta:\n" +
            this->printClientInfo((Client &)i));
            this->Container.erase(i);
            break;
        }
    }
}

Client GServer::GClientContainer::DeleteByClient(char sritis[MAX_COMPUTERNAME_LENGTH + 1],
        char kompiuteris[MAX_COMPUTERNAME_LENGTH + 1], char naudotojas[MAX_COMPUTERNAME_LENGTH + 1]) {
    std::list<Client>::iterator i;

    for (i = this->Container.begin(); i != this->Container.end(); i++) {
        if (i->domainName == sritis && i->pcName == kompiuteris &&
                i->userName == naudotojas) {
            this->logger->logDebug(this->className, "Salinu klienta:\n" +
            this->printClientInfo((Client &)i));
            this->Container.erase(i);
        }
    }
}

Client GServer::GClientContainer::FindByID(int id) {
    std::list<Client>::iterator i;
    for (i = this->Container.begin(); i != this->Container.end(); i++) {
        if (i->id == id) {
            return *i;
        }
    }
}

void GServer::GClientContainer::PrintPage(int id, int page, char* buffer, int &length) {
    // Tikrinu ar yra toks puslapis
    if (!this->IsValidPage(page)) {
        // Nera topio puslapio
        buffer = NULL;
        length = 0;
        return;
    }

    std::list<Client>::iterator it = this->Container.begin();
    // Einam iki nurodito puslapio
    for (int i = 1; i < page; i++) {
        for (int j = 0; j < PAGE_SIZE; j++)
            it++;
    }
    
    // Pildom duomenis grazinimui
    Client* client;
    int place = 0;
    int count;
    for (count = -1; it != this->Container.end() && count < PAGE_SIZE; count++) {
        if (it->id != id) {
            client = (struct Client*) &buffer[place];
            Client &temp = *it;
            memcpy(client, &temp, sizeof (Client));
            client->id = htonl(temp.id);
            place = place + sizeof (Client);
        }
        it++;
    }

    // Grazinu duomenu kieki
    length = count * sizeof ( Client);
}

bool GServer::GClientContainer::IsValidPage(int pageNr) {
    return ( (this->Container.size() - (pageNr * PAGE_SIZE)) > (-1 * PAGE_SIZE));
}

std::string GServer::GClientContainer::printClientInfo(Client client){
    std::stringstream ss;
    ss << "Kliento informacija: ";
    ss << "ID: " << std::to_string(client.id) << " ";
    ss << "Sritis: " << string(client.domainName) << " ";
    ss << "Kompiuterio pavadinimas: " << string(client.pcName) << " ";
    ss << "Naudotojo vardas: " << string(client.userName);
    return ss.str();
}