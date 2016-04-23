/* 
 * File:   ClientContainer.cpp
 * Author: developer
 * 
 * Created on April 24, 2014, 4:05 PM
 */

#include "ClientContainer.h"
#include "structures.h"
#include <iostream>

GServer::ClientContainer::ClientContainer() {
    this->printBuffer = new char[OneMBofChar];
}

GServer::ClientContainer::~ClientContainer() {
    this->Container.clear();
    delete this->printBuffer;
}

void GServer::ClientContainer::Add(Client client) {
    this->Container.push_back(client);
}

void GServer::ClientContainer::Add(int socket, char sritis[MAX_COMPUTERNAME_LENGTH + 1],
        char kompiuteris[MAX_COMPUTERNAME_LENGTH + 1],
        char naudotojas[MAX_COMPUTERNAME_LENGTH + 1]) {

    Client temp;
    temp.id = socket;
    // Kopijuojam reiksmes
    memcpy(temp.domainName, sritis, sizeof temp.domainName);
    memcpy(temp.pcName, kompiuteris, sizeof temp.pcName);
    memcpy(temp.userName, naudotojas, sizeof temp.userName);

    this->Add(temp);
}

void GServer::ClientContainer::DeleteByID(int id) {
    std::list<Client>::iterator i;

    for (i = this->Container.begin(); i != this->Container.end(); i++) {
        if (i->id == id) {
            this->Container.erase(i);
            break;
        }
    }
}

Client GServer::ClientContainer::DeleteByClient(char sritis[MAX_COMPUTERNAME_LENGTH + 1],
        char kompiuteris[MAX_COMPUTERNAME_LENGTH + 1], char naudotojas[MAX_COMPUTERNAME_LENGTH + 1]) {
    std::list<Client>::iterator i;

    for (i = this->Container.begin(); i != this->Container.end(); i++) {
        if (i->domainName == sritis && i->pcName == kompiuteris && i->userName == naudotojas) {
            this->Container.erase(i);
        }
    }
}

Client GServer::ClientContainer::FindByID(int id) {
    std::list<Client>::iterator i;
    for (i = this->Container.begin(); i != this->Container.end(); i++) {
        if (i->id == id) {
            return *i;
        }
    }
}

void GServer::ClientContainer::PrintPage(int id, int page, char* buffer, int &length) {
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

// Tirkinama ar egzistuoja nurodytas puslapis

bool GServer::ClientContainer::IsValidPage(int pageNr) {
    return ( (this->Container.size() - (pageNr * PAGE_SIZE)) > (-1 * PAGE_SIZE));
}