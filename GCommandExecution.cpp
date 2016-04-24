/* 
 * File:   GCommandExecution.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 23, 14.04
 */

#include "GCommandExecution.h"
#include "UDPServerGSocket.h"
#include "TCPServerGSocket.h"
#include "TCPClientGSocket.h"
#include "UDPClientGSocket.h"

GServer::GCommandExecution::GCommandExecution(GLogger* logger,
        GTagGenerator* tagGenerator, GClientContainer* clients,
        std::map<int, GServer::GSocket*>* clientSocketList, GConfig* conf) :
GObject() {
    // Nustatau objekto pavadinima
    this->className = this->className + ":GCommandExecution";
    // Priskiriu pranesimu isvedimu objekta
    this->logger = logger;
    // Priskiriu zymu generatoriu
    this->tagGenerator = tagGenerator;
    // Priskiriu klientu sarao objekta
    this->clients = clients;
    // Nuoroda i nustatymu faila
    this->config = conf;

    this->clientSocketList = clientSocketList;

    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::GCommandExecution::~GCommandExecution() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

bool GServer::GCommandExecution::executeCommand(vector<char>& buffer,
        int& sendDataSize, GSocket* socket) {
    bool returnValue = false;
    int tempCmd = -1;
    int tag, size;

    // Analizuoju headeri
    if (analizeHeader(buffer.data(), tag, size)) {
        // Pavykus nustaty headerio duomenis
        switch (tag) {
                // Atejo komanda
            case 0:
                // Analizuoju kokia komanda atejo
                if (this->analizeCommandHeader(
                        &buffer.data()[sizeof (header)], tempCmd)) {
                    // Pavyko nustatyti kokia komanda atejo
                    // TOliau atlieku veiksmus su atitinkama komanda
                    switch (tempCmd) {
                        case Commands::HELLO:
                            this->logger->logDebug(this->className, "Gauta "
                                    "HELLO komanda");
                            // Tirkinu kuris protokolas
                            // Tirkinu ar ne TCP
                            if (socket->getClassName().find("TCP") !=
                                    std::string::npos) {
                                // TCP protokolas
                                this->commandHello(
                                        &buffer.data()[sizeof (header)],
                                        socket->getSocket());
                            }
                            if (socket->getClassName().find("UDP") !=
                                    std::string::npos) {
                                // UDP protokolas
                                UDPServerGSocket* udp =
                                        (UDPServerGSocket*) socket;

                                this->commandHelloUDP(
                                        &buffer.data()[sizeof (header)],
                                                // Generuojamas fake ID
                                                65535,
                                        udp->getSocket(),
                                        udp->returnClientAddressInfo() );
                            }

                            break;
                        default:
                            this->logger->logError(this->className, "Gauta "
                                    "nezinoma komanda: " +
                                    std::to_string(tempCmd));
                            break;
                    }
                }// END Analizuoju kokia komanda atejo
                break;
                // Bus persiunciami duomenys
            default:
                break;
        } // switch (tag)
    } //if (analizeHeader(buffer, tag, size))

    return returnValue;
}

bool GServer::GCommandExecution::analizeHeader(char* buffer, int& tag,
        int& size) {
    try {
        header* head = (struct header*) &buffer[0];
        // Suvartau gautus duomenis i suprantama puse
        tag = ntohs(head->tag);
        size = ntohl(head->lenght);
        this->logger->logDebug(this->className, "Gautu duomenu headerio "
                "informacija\nTAG: " + std::to_string(tag) +
                "\nSIZE: " + std::to_string(size));
        return true;
    } catch (int e) {
        this->logger->logError(this->className, "Nepavyko nustatyti duomenu "
                "header. Klaida: " + std::to_string(e));
        return false;
    }
    return false;
}

bool GServer::GCommandExecution::analizeCommandHeader(char* buffer,
        int& command) {
    try {
        Command* cmd = (struct Command*) &buffer[0];
        // Suvartau gautus duomenis i suprantama puse
        command = ntohs(cmd->command);
        this->logger->logDebug(this->className, "Gauta komanda:  " +
                std::to_string(command));
        return true;
    } catch (int e) {
        this->logger->logError(this->className, "Nepavyko nustatyti komandos "
                "duomenu. Klaida: " + std::to_string(e));
        return false;
    }
    return false;
}

Client GServer::GCommandExecution::commandHello(char* buffer, int socket) {
    helloCommand* hello = (struct helloCommand*) &buffer[0];
    // Suvartau likusius komandos laukus
    // Vartyti nereikia, gautas tekstats
    return this->clients->Add(socket, hello->domainName, hello->pcName,
            hello->userName);
}

Client GServer::GCommandExecution::commandHelloUDP(char* buffer, int socket,
        int serverSocket, sockaddr_storage klientoDuomenys) {
    // Nustatau struktura buferyje
    helloCommand* hello = (struct helloCommand*) &buffer[0];
    // Suvartau likusius komandos laukus

    // Kuriu UDPCLientGSocket objekta
    GSocket* udpClient = new GServer::UDPClientGSocket(
            this->config, this->logger, (GCommandExecution *)this, socket, 
            serverSocket, klientoDuomenys);
    // Pridedu prie klientu saraso
    clientSocketList->insert( std::pair<int, GSocket*>(
            udpClient->getSocket(), udpClient) );

    return this->clients->Add(socket, hello->domainName, hello->pcName,
            hello->userName);
}
