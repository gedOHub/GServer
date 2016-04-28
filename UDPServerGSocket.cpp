/* 
 * File:   UDPServerGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 23, 00.48
 */

#include "UDPServerGSocket.h"

GServer::UDPServerGSocket::UDPServerGSocket(GServer::GConfig* conf,
        GLogger* logger, fd_set& visiSocket, int& maxDeskriptor,
        GCommandExecution* command) : UDPGSocket(conf, logger, command) {

    // Nustatau pavadinima
    this->className = this->className + ":UDPServerGSocket";
    // Objektui reikalingi veiksmai

    // Sukuriu socketa klausimuisi
    this->createServerScoket(
            const_cast<char*> (conf->getStringSetting("IP").c_str()),
            const_cast<char*> (conf->getStringSetting("PORT").c_str()),
            conf->getIntSetting("NETWORK_TYPE"), SOCK_DGRAM, IPPROTO_UDP,
            AI_PASSIVE);
    // Nustatau skaitomu socketu sarasa
    this->skaitomiSocket = &visiSocket;
    // Pridedu socketa i socketu sarasa
    FD_SET(this->socket_descriptor, this->skaitomiSocket);
    // Tikrinu ar nera didenis deskritprious nei dabartinis
    this->checkMaxDescriptor(maxDeskriptor);

    // Objektas sukurtas pilnai
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::UDPServerGSocket::~UDPServerGSocket() {
    // Naikinimas
    this->logger->logDebug(this->className, "Baigiu darba su " +
            std::to_string(this->socket_descriptor) + " socketu");
    this->close();
    this->logger->logDebug(this->className, "Pasalinu is skaitomu saraso");
    FD_CLR(this->socket_descriptor, this->skaitomiSocket);

    // Objektas sunaikintas
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

GServer::GSocket* GServer::UDPServerGSocket::acceptConnection(
        GServer::GConfig* conf, int& maxDescriptor) {
    int returnValue = -1;

    // Priimu gaunamus duomenis
    returnValue = this->reciveData(this->buffer.data(), this->buffer.size());
    UDPClientGSocket* client;
    //Tirkinu ar pavyko kazka gauti
    if (returnValue != -1) {
        // Pavyko
        // Ieskau ar esamas klientas ar naujas
        // Gaminu IP ir PORT kombinacija
        sockaddr_in* addr = (struct sockaddr_in*) & this->serverStorage;
        string address(inet_ntoa(addr->sin_addr));
        address.append(":" + std::to_string(ntohs(addr->sin_port)));

        this->UDPClientListIterator = this->UDPClientList.find(address);
        // Tikrinu esamas ar ne
        if (UDPClientListIterator == UDPClientList.end()) {
            // Naujas
            // Reikia sukurti objekta prie soketu
            //TODO: Generuoti netikra ID
            client = new UDPClientGSocket(conf, logger, commands, 65535,
                    this->getSocket(), this->serverStorage);
            GSocket* g = (GSocket*) & client;
            // Pridedu prie klientu saraso
            commands->registerUDPAccept(g);
            // Pridedu prie UDP kleintu saraso
            this->UDPClientList.insert(std::pair<string, UDPClientGSocket*>(
                    address, client));
            
        } else {
            // Esamas
            client = (UDPClientGSocket*) UDPClientList[address];
        }
        // Bandau vygdyti gauta komanda
        this->commands->executeCommand(this->buffer, returnValue,
                (GSocket*) client);
    }

    return NULL;
}
