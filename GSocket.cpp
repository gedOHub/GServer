/* 
 * File:   GSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, kovas 27, 04.51
 */

#include "GSocket.h"
#include "exitCodes.h"

// TODO: lookupus perdaryti per objekta

GServer::GSocket::GSocket(GServer::GConfig* conf, GLogger* logger) : MAX_BUFFER_SIZE(conf->getIntSetting("MAX_SOCKET_BUFFER_SIZE")) {
    // Nustatau objekto pavadinima
    this->className = this->className + ":GSocket";
    // Nustatau numatytaja socket_descritptor reiksme
    this->socket_descriptor = -1;
    // Nustatau logeri
    this->logger = logger;
    // Nustatu buferio dydi
    this->buffer.resize(conf->getIntSetting("SOCKET_BUFFER_SIZE"));
    // Spausdinu nustatytai buferio dydi
    this->logger->logDebug(this->className, "Sukurto buferio dydis: " +
            std::to_string(this->buffer.size()));
    // Tirkinu ar pavyko sukurti buferi
    if (this->buffer.size() < conf->getIntSetting("SOCKET_BUFFER_SIZE")) {
        // Buferio dydis per mazas
        this->logger->logError(this->className,
                "Nepavyko sukurti norimo dydzio buferio");
        // Nutraukiamas programos darbas
        exit(GServer::EXIT_CODES::SOCKET_BUFFER_TO_SMALL);
    }

    // Atspausdinu derinimo inforamcija
    this->logger->logDebug(this->className, "socket_descriptor reiksme: " +
            std::to_string(this->socket_descriptor));
    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::GSocket::~GSocket() {
    this->close();

    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

int GServer::GSocket::resizeBuffer(int newSize) {
    // Tikrinu ar nuajas dydis nera didesnis nei leistinas
    if (newSize > this->MAX_BUFFER_SIZE) {
        this->logger->logInfo(this->className, "Norimas dydis: " +
                std::to_string(newSize) +
                " per didelis. Nustatomas maksimalus dydis: " +
                std::to_string(this->MAX_BUFFER_SIZE));
        // Didenis, nustatau maksimalu dydi
        return this->setBufferSize(this->MAX_BUFFER_SIZE);
    }
    // Naujas dydis mazesnis nei nurimas
    this->logger->logInfo(this->className, "Nustatau tauja dydi: " + newSize);
    // Nustatau nauja dydi
    return this->setBufferSize(newSize);
}

int GServer::GSocket::setBufferSize(int newSize) {
    // Nustatau nauja buferio dydi
    this->buffer.resize(newSize);
    // Grazinu nauja dydi
    return this->buffer.size();
}

int GServer::GSocket::sendData(int socketFd, vector<char>* data) {
    this->logger->logError(this->className, "Neigyvendinta sendData funkcija");
    return -1;
}

int GServer::GSocket::reciveData(int socketFd, vector<char>* data) {
    this->logger->logError(this->className, "Neigyvendinta reciveData funkcija");
    return -1;
}

int GServer::GSocket::createSocket(char* ip, char* port, int socketFamily,
        int socketType, int socketProtocol, int socketFlag, addrinfo *result) {
    // Grazinamo socketo numeris
    int returnValue = -1;
    // Strukturos kuriso saugos visa inforamcija apie norima adresa ir prievada
    addrinfo hints;
    // Isvalo filtruojancia
    memset(&hints, sizeof (hints), sizeof (struct addrinfo));
    // Nustatom norimus parametrus
    hints.ai_family = socketFamily;
    hints.ai_socktype = socketType;
    hints.ai_protocol = socketProtocol;
    hints.ai_flags = socketFlag;
    // Bandau gauti galimus rezultatus
    int searchResult = getaddrinfo(ip, port, &hints, &result);
    // TIkrinu ar neivyko klaida
    if (searchResult != 0) {
        // Ivyko klaida
        // Pranesu kas ivyko
        this->logger->logError(this->className, gai_strerror(searchResult));
        exit(GServer::EXIT_CODES::UNABLE_TO_GET_ADDRESS_INFO);
    }
    // Begu per visus galimus variantus
    for (addrinfo* i = result; i != NULL; i->ai_next) {
        returnValue = socket(i->ai_family, i->ai_socktype, i->ai_protocol);
        // Tikrinu ar pavyko sukurti socketa
        if (returnValue == -1) {
            // Nepavyko, einu per galimus varaintus toliau
            this->logger->logDebug(this->className, "Nepavyko sukurti socketo");
            continue;
        } else
            // Pavyko, baigiu eijima per variantus
            break;
    }
    // Tirkinu ar pavyko kazka gauti
    if (returnValue == -1) {
        this->logger->logDebug(this->className, "Nepavyko sukurti socketo");
        exit(GServer::EXIT_CODES::UNABLE_TO_CREATE_SOCKET);
    }
    // Grazinu socketo numeri
    this->logger->logDebug(this->className, "Grazinamo socketo numeris- " +
            std::to_string(returnValue));
    return returnValue;
}

void GServer::GSocket::close() {
    this->logger->logDebug(this->className, "Uzveriamas socket. ID: " +
            std::to_string(this->socket_descriptor));
    shutdown(this->socket_descriptor, SHUT_RDWR);
}

int GServer::GSocket::createServerScoket(char* ip, char* port,
        int socketFamily, int socketType, int socketProtocol, int socketFlag) {
    // Kintamasis, kuris saugo gautus duomenis is adreso ir porto kombinacijos
    addrinfo result;
    // Kuriu socketa
    this->socket_descriptor = createSocket(ip, port, socketFamily, socketType,
            socketProtocol, socketFlag, &result);
    // Ruosiu klausimuisi
    bindSocket(&result);
    // Pradedu klausimasi
    listenSocket();
}

void GServer::GSocket::bindSocket(addrinfo* result) {    
    // Tirkinu ar pavyko prauosti sokceta klausimuisi
    if (bind(this->socket_descriptor, result->ai_addr, result->ai_addrlen) 
            != 0) {
        // Nepavyko paruosti
        this->logger->logError(this->className, strerror(errno));
        exit(GServer::EXIT_CODES::UNABLE_TO_BIND_SOCKET);
    }
    
    this->logger->logDebug(this->className, "SOCKET " + 
            std::to_string(this->socket_descriptor) + " paruostas klausimuisi");
}

void GServer::GSocket::listenSocket(){
    // Tikrinu ar pavyko klausytis
    if( listen(this->socket_descriptor, SOMAXCONN) != 0 ){
        // Nepavyko klausytis
        this->logger->logError(this->className, strerror(errno));
        exit(GServer::EXIT_CODES::UNABLE_TO_LISTEN_ON_SOCKET);
    }
    this->logger->logDebug(this->className, "SOCKET " + 
            std::to_string(this->socket_descriptor) + " pradejo klausimasi");
}

