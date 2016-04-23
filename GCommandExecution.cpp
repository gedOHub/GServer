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
        GTagGenerator* tagGenerator, GClientContainer* clients) : GObject() {
    // Nustatau objekto pavadinima
    this->className = this->className + ":GCommandExecution";
    // Priskiriu pranesimu isvedimu objekta
    this->logger = logger;
    // Priskiriu zymu generatoriu
    this->tagGenerator = tagGenerator;
    // Priskiriu klientu sarao objekta
    this->clients = clients;

    // Pranesu apie objekto sukurima
    this->logger->logDebug(this->className, "Objektas sukurtas");
}

GServer::GCommandExecution::~GCommandExecution() {
    this->logger->logDebug(this->className, "Objektas sunaikintas");
}

bool GServer::GCommandExecution::executeCommand(vector<char>& buffer, 
        int& sendDataSize, GSocket* socket) {
    bool returnValue = false;
    int temp;
    int tag, size;

    // Analizuoju headeri
    if (analizeHeader(buffer.data(), tag, size)) {
        // Pavykus nustaty headerio duomenis
        switch (tag) {
                // Atejo komanda
            case 0:
                // Gaunu likusius duomenis
                temp = socket->reciveData(&buffer.data()[sizeof (header)], 
                        size);
                // Tirkinu ar gauta tiek kiek reikia
                if (temp == size) {
                    // Gautas tinkamas kiekis duomenu
                    // Analizuoju kokia komanda atejo
                    int command = -1;
                    if (this->analizeCommandHeader(
                            &buffer.data()[sizeof (header)], command)) {
                        // Pavyko nustatyti kokia komanda atejo
                        // TOliau atlieku veiksmus su atitinkama komanda
                        switch (command){
                            case Commands::HELLO:
                                this->logger->logDebug(this->className, "Gauta "
                                        "HELLO komanda");
                                this->commandHello(
                                        &buffer.data()[sizeof (header)], 
                                                socket->getSocket());
                                break;
                            default:
                                this->logger->logError(this->className, "Gauta "
                                        "nezinoma komanda: " + 
                                        std::to_string(command));
                                break;
                        }
                    }// END Analizuoju kokia komanda atejo
                } // END Tirkinu ar gauta tiek kiek reikia
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
        int& command){
    try {
        Command* cmd = (struct Command*) &buffer[0];
        // Suvartau gautus duomenis i suprantama puse
        command = ntohs(cmd->command);
        this->logger->logDebug(this->className, "Gauta komanda:  " + 
                std::to_string(command));
        return true;
    } catch (int e) {
        this->logger->logError(this->className, "Nepavyko nustatyti koamndos "
                "duomenu. Klaida: " + std::to_string(e));
        return false;
    }
    return false;
}

Client GServer::GCommandExecution::commandHello(char* buffer, int socket){
    helloCommand* hello = (struct helloCommand*) &buffer[0];
    // Suvartau likusius komandos laukus
    // Vartyti nereikia, gautas tekstats
    return this->clients->Add(socket, hello->domainName, hello->pcName, 
            hello->userName);
}
