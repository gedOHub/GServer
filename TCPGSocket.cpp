/* 
 * File:   TCPGSocket.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 9, 20.00
 */

#include "TCPGSocket.h"

GServer::TCPGSocket::TCPGSocket(GServer::GConfig* conf, GLogger* logger) :
GSocket(conf, logger) {
    // Nustatau pavadinima
    this->className = this->className + ":TCPGSocket";

    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::TCPGSocket::~TCPGSocket() {

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

int GServer::TCPGSocket::sendData(int socketFd, vector<char>* data){
    int returnValue = -1;
    // Siusti duomenis
    returnValue = send(socketFd, &data[0], data->size(), 0 );
    // Pranesimas apie sekme
    this->logger->logDebug(this->className, 
            std::to_string(this->socket_descriptor) + ":" + 
            std::to_string(data->size()) + " --->" + 
            std::to_string(socketFd) + ":" +  std::to_string(returnValue));
    return returnValue;
}

int GServer::TCPGSocket::reciveData(){
    int returnValue = -1;
    // Siusti duomenis
    returnValue = recv(this->socket_descriptor, &this->buffer[0], this->buffer.size(), 0 );
    // Pranesimas apie sekme
    this->logger->logDebug(this->className, 
            std::to_string(this->socket_descriptor) + ":" + 
            std::to_string(this->buffer.size()) + " <---" + 
            std::to_string(returnValue));
    return returnValue;
}
