/* 
 * File:   TCPGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#include "TCPGSocket.h"

GServer::TCPGSocket::TCPGSocket(GServer::GConfig* conf, GLogger* logger,
        GCommandExecution* command) : GSocket(conf, logger, command) {
    // Nustatau pavadinima
    this->className = this->className + ":TCPGSocket";
    // Priskiriu nuorda i pranesimu objekta
    this->logger = logger;
    // Priskiriu nuoroda i komandu vykdymo objekta
    this->commands = command;
    // Nustatua paketo dydi
    this->MAX_PACKET_SIZE = buffer.size();

    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::TCPGSocket::~TCPGSocket() {

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

int GServer::TCPGSocket::sendData(char* data, int size) {
    int returnValue = 0;
    this->logger->logDebug(this->className, "Reikia issiusti: " + std::to_string(size));

    returnValue = send(this->socket_descriptor, &data[0], size, MSG_CONFIRM);
    this->logger->logDebug(this->className, "[" +
            std::to_string(this->socket_descriptor) + "] Turiu issiusti: " +
            std::to_string(returnValue));
    return returnValue;
}

int GServer::TCPGSocket::reciveData(char* buffer, int size) {
    struct header* head;
    // Gaunu headeri
    int returnValue = recv(this->socket_descriptor, &buffer[0], sizeof (header), MSG_WAITALL);
    this->logger->logDebug(this->className, "Laukiu: " + std::to_string(ntohl(head->lenght)));
    if (returnValue > 0) {
        // Nustatua headeri
        head = (struct header*) & this->buffer[0];
        // Gaunu tiek duomenu kiek nurodyta headeryje
        returnValue = recv(this->socket_descriptor, &buffer[sizeof (header)], ntohl(head->lenght), MSG_WAITALL);
    }
    this->logger->logDebug(this->className, "Gauta: " + std::to_string(returnValue));
    return returnValue;
}
