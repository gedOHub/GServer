/* 
 * File:   GCommandExecution.cpp
 * Author: gedas
 * 
 * Created on Šeštadienis, 2016, balandis 23, 14.04
 */

#include "GCommandExecution.h"
#include "GTagGenerator.h"

GServer::GCommandExecution::GCommandExecution(GLogger* logger,
        GTagGenerator* tagGenerator, GClientContainer* clients,
        std::map<int, GServer::GSocket*>* clientSocketList, GConfig* conf,
        GTunnelContainer* tunnels) :
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
    // Nustatuat tuneliu objekta
    this->tunnels = tunnels;

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

    // Tikrinu ar nera uzdaryta jungtis
    if (sendDataSize < 1) {
        // Uzdaryta jungtis
        this->logger->logInfo(this->className, "Klientas " +
                std::to_string(socket->getSocket()) + +" uzdare sujungima");
        // Nutraukiu is klientu saraso
        this->clients->DeleteByID(socket->getSocket());
        std::map<int, GSocket*>::iterator it = this->clientSocketList->
                find(socket->getSocket());
        if (it != this->clientSocketList->end()) {
            // Salinu is klineto->Objekta sarso
            this->clientSocketList->erase(it);
        } else {
            this->logger->logError(this->className, "Neapvyko rasti kliento " +
                    std::to_string(socket->getSocket()));
        }
        // Naikinu pati si objketa
        delete socket;
        return false;
    }

    //string data(buffer.data(), sendDataSize);
    //this->logger->logDebug(this->className, "Gauta: " + data);

    try {
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
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "HELLO komanda");
                                this->commandHello(
                                        &buffer.data()[sizeof (header)],
                                        socket->getSocket());
                                returnValue = true;
                                break;
                            }
                            case Commands::LIST:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "LIST komanda");
                                int tempCount = -1;
                                // Pildau puslapi klientu inforamcija su atsaku
                                this->commandList(buffer, tempCount,
                                        socket->getSocket());
                                socket->sendData(buffer.data(), tempCount);
                                if (tempCount > 0) returnValue = true;
                                else returnValue = false;
                                break;
                            }
                            case Commands::JSON_LIST:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "JSON_LIST komanda");
                                int tempCount = -1;
                                // Pildau puslapi klientu inforamcija su atsaku
                                this->commandJsonList(buffer, tempCount,
                                        socket->getSocket());
                                socket->sendData(buffer.data(), tempCount);
                                if (tempCount > 0) returnValue = true;
                                else returnValue = false;
                                break;
                            }
                            case Commands::INIT_CONNECT:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "INIT_CONNECT komanda");
                                int reciverID = -1, duomCout = -1;
                                this->commandInitCommand(buffer, duomCout,
                                        socket->getSocket(), reciverID);
                                GSocket* client = NULL;
                                // Randu klientu su kuriuo norima uzmegzti rysi
                                this->clientSocketListIterator =
                                        this->clientSocketList->find(reciverID);
                                // Tirkinu ar pavyko uzmegzti
                                if (this->clientSocketListIterator !=
                                        this->clientSocketList->end()) {
                                    // Radau
                                    client = (GSocket*) &(*this->clientSocketListIterator->second);
                                    // Siunciu duomenis klientui
                                    client->sendData(buffer.data(), duomCout);
                                } else {
                                    // Neradau
                                    this->logger->logError(this->className,
                                            "[INIT_CONNECT]Neradau kliento su ID " +
                                            std::to_string(reciverID));
                                }
                                break;
                            }
                            case Commands::JSON_INIT_CONNECT:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "JSON_INIT_CONNECT komanda");
                                int reciverID = -1, duomCout = -1;
                                this->commandJsonInitCommand(buffer, duomCout,
                                        socket->getSocket(), reciverID);
                                GSocket* client = NULL;
                                // Randu klientu su kuriuo norima uzmegzti rysi
                                this->clientSocketListIterator =
                                        this->clientSocketList->find(reciverID);
                                // Tirkinu ar pavyko uzmegzti
                                if (this->clientSocketListIterator !=
                                        this->clientSocketList->end()) {
                                    // Radau
                                    client = (GSocket*) &(*this->clientSocketListIterator->second);
                                    // Siunciu duomenis klientui
                                    client->sendData(buffer.data(), duomCout);
                                } else {
                                    // Neradau
                                    this->logger->logError(this->className,
                                            "[JSON_INIT_CONNECT]Neradau kliento su ID " +
                                            std::to_string(reciverID));
                                }
                                break;
                            }
                            case Commands::CONNECT_ACK:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "CONNECT_ACK komanda");
                                int duomCount = -1, reciverSocket = -1;
                                this->commandConnecACK(buffer, duomCount,
                                        socket->getSocket(), reciverSocket);
                                GSocket* reciver = NULL;
                                // Randu klientu su kuriuo norima uzmegzti rysi
                                this->clientSocketListIterator =
                                        this->clientSocketList->find(reciverSocket);
                                // Tirkinu ar pavyko uzmegzti
                                if (this->clientSocketListIterator !=
                                        this->clientSocketList->end()) {
                                    // Radau
                                    reciver = (GSocket*) &(*this->clientSocketListIterator->second);
                                    // Siunciu duomenis klientui
                                    reciver->sendData(buffer.data(), duomCount);
                                } else {
                                    // Neradau
                                    this->logger->logError(this->className,
                                            "[CONNECT_ACK]Neradau kliento su ID " +
                                            std::to_string(reciverSocket));
                                }
                                break;
                            }
                            case Commands::JSON_CONNECT_ACK:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "JSON_CONNECT_ACK komanda");
                                int duomCount = -1, reciverSocket = -1;
                                this->commandJsonConnecACK(buffer, duomCount,
                                        socket->getSocket(), reciverSocket);
                                GSocket* reciver = NULL;
                                // Randu klientu su kuriuo norima uzmegzti rysi
                                this->clientSocketListIterator =
                                        this->clientSocketList->find(reciverSocket);
                                // Tirkinu ar pavyko uzmegzti
                                if (this->clientSocketListIterator !=
                                        this->clientSocketList->end()) {
                                    // Radau
                                    reciver = (GSocket*) &(*this->clientSocketListIterator->second);
                                    // Siunciu duomenis klientui
                                    reciver->sendData(buffer.data(), duomCount);
                                } else {
                                    // Neradau
                                    this->logger->logError(this->className,
                                            "[JSON_CONNECT_ACK]Neradau kliento su ID " +
                                            std::to_string(reciverSocket));
                                }
                                break;
                            }
                            case Commands::CLIENT_CONNECT:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "CLIENT_CONNECT komanda");
                                int duomCount = -1, reciverSocket = -1;
                                this->commandClientConnect(buffer, duomCount,
                                        socket->getSocket(), reciverSocket);
                                GSocket* reciver = (GSocket*) &(*clientSocketList->
                                        find(reciverSocket)->second);
                                reciver->sendData(buffer.data(), duomCount);
                                break;
                            }
                            case Commands::BEGIN_READ_ACK:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "BEGIN_READ_ACK komanda");
                                int duomCount = -1, reciverSocket = -1;
                                this->commandBeginReadAck(buffer, duomCount,
                                        socket->getSocket(), reciverSocket);
                                GSocket* reciver = (GSocket*) &(*clientSocketList->
                                        find(reciverSocket)->second);
                                reciver->sendData(buffer.data(), duomCount);
                                break;
                            }
                            case Commands::CLOSE_TUNNEL:
                            {
                                this->logger->logDebug(this->className, "Gauta "
                                        "CLOSE_TUNNEL komanda");
                                int duomCount = -1, reciverSocket = -1;
                                this->commandCloseTunnel(buffer, duomCount,
                                        socket->getSocket(), reciverSocket);
                                try {
                                    GSocket* reciver = (GSocket*) &(*clientSocketList->
                                            find(reciverSocket)->second);
                                    reciver->sendData(buffer.data(), duomCount);
                                } catch (int i) {
                                    this->logger->logError(this->className, "Klaida siuncian CLOSE_TUNNEL komanda. " + std::to_string(i));
                                }

                                break;
                            }
                            default:
                            {
                                this->logger->logError(this->className, "Gauta "
                                        "nezinoma komanda: " +
                                        std::to_string(tempCmd));
                                break;
                            }
                        } //END switch (tempCmd) {
                    }// END Analizuoju kokia komanda atejo
                    break;
                    // Bus persiunciami duomenys
                default:
                    try {
                        int rSend = 0, lenght = 0;
                        header* head;
                        this->logger->logDebug(this->className, "Viso gauta: " + std::to_string(sendDataSize));
                        while ((sendDataSize - rSend) != 0) {
                            // Nustatau headerio pozicija
                            head = (struct header*) &buffer.data()[rSend];
                            // Duomenu permetimas i kita socketa
                            int dep_socket = -1, dep_tag = -1;
                            lenght = ntohl(head->lenght) + sizeof (header);
                            this->logger->logDebug(this->className, "Reikia persiusti: " + std::to_string(lenght));

                            this->tunnels->FindByPear(socket->getSocket(),
                                    ntohs(head->tag), dep_socket, dep_tag);

                            GSocket* reciver = &(*this->clientSocketList->find(
                                    dep_socket)->second);

                            if (dep_socket != -1 && dep_tag != -1) {
                                // Permetineju paketa i reikiama socketa
                                head->tag = htons(dep_tag);
                                head->lenght = head->lenght;
                                rSend = rSend + reciver->sendData(buffer.data(), lenght);
                                this->logger->logDebug(this->className, "Isisusta: " + std::to_string(rSend));
                                break;
                            } else {
                                this->logger->logError(this->className, "Neradau sujungimo. Destinatio socket: " + std::to_string(dep_socket) + " destination tag: " + std::to_string(dep_tag));
                                break;
                            }
                        }
                    }catch(int e){
                        this->logger->logError(this->className, "Gautas klaidos kodas: " + std::to_string(errno));
                    }
                    break;
            } // switch (tag)
        }
    }//if (analizeHeader(buffer, tag, size))
    catch (int e) {
        this->logger->logError(this->className, "Vykdant komanda iskilo "
                "klaida: " + std::to_string(e));
        return -1;
    }

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
                "informacija: TAG: " + std::to_string(tag) +
                " SIZE: " + std::to_string(size));
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

void GServer::GCommandExecution::registerUDPAccept(GSocket* udp) {
    clientSocketList->insert(std::pair<int, GSocket*>(udp->getSocket(), udp));
}

void GServer::GCommandExecution::commandList(vector<char>& buffer, int& duomCount, int socket) {
    // Headeris jau nuskaitytas
    /* Header,ACK,DATA...
     * HHHHHHHAAAADDDDDDDDDDDDDDDDDD....
     */
    listCommand* list = (struct listCommand*) &buffer.data()[sizeof (header)];
    // Nustatau i tinkama isdestyma puslapi
    list->page = ntohl(list->page);
    this->logger->logDebug(this->className, "Norima puslapio: " +
            std::to_string(list->page));
    // Formuoju prasyta puslapi
    this->clients->PrintPage(socket, list->page, &buffer.data()[
            sizeof (listAckCommand) + sizeof (header)], duomCount);
    // Pildau atsako antraste
    listAckCommand* listAck = (struct listAckCommand*)
            &buffer.data()[sizeof (header)];
    listAck->command = htons(LIST_ACK);
    // Tirkinu ar pavyko suformuoti duomenis
    if (duomCount > 0)
        listAck->success = true;
    else
        listAck->success = false;
    // Pildau headerio informacija
    header* head = (struct header*) &buffer[0];
    head->tag = htons(0);
    head->lenght = htonl(sizeof (listAckCommand) + duomCount);

    duomCount = duomCount + sizeof (listAckCommand) + sizeof (header);
}

void GServer::GCommandExecution::commandJsonList(vector<char>& buffer,
        int& duomCount, int socket) {
    jsonListCommand* list = (struct jsonListCommand*)
            &buffer.data()[sizeof (header)];
    // Nustatau puslapi i tinkma puse
    list->page = ntohl(list->page);
    // Nustatau sokceto ID i tinkama isdestyma
    int jsonSocket = ntohl(list->socketID);
    // Spausdinu kleintu sarasa
    this->clients->PrintPage(socket, list->page, &buffer.data()[
            sizeof (jsonListAckCommand) + sizeof (header)], duomCount);
    // Formuoju atsako paketa
    jsonListAckCommand* listAck =
            (struct jsonListAckCommand*) &buffer.data()[sizeof (header)];
    // Nurodau kokia komanda bus siunčiama
    listAck->command = htons(JSON_LIST_ACK);
    // Nurodau socketID
    listAck->socketID = htonl(jsonSocket);
    if (duomCount > 0)
        listAck->success = true;
    else
        listAck->success = false;
    // Pildau paketo antrste
    header* head = (struct header*) &buffer[0];
    head->tag = htons(0);
    head->lenght = htonl(sizeof ( jsonListAckCommand) + duomCount);

    duomCount = duomCount + sizeof (jsonListAckCommand) + sizeof (header);
}

void GServer::GCommandExecution::commandInitCommand(vector<char>& buffer,
        int& duomCount, int socket, int& reciverID) {
    connectInitCommand* connect = (struct connectInitCommand*)
            &buffer.data()[ sizeof ( header) ];
    // Suvartau paketo laukus i tinkama puse
    connect->client_id = ntohl(connect->client_id);
    connect->destination_port = ntohs(connect->destination_port);
    connect->source_port = ntohs(connect->source_port);
    connect->tag = ntohs(connect->tag);
    // Generuojama zyme clientui
    int clientTag = this->tagGenerator->Generate(this->tunnels);
    // Kuriu nauja tuneli
    int tunnel_id = this->tunnels->InitConnect(socket, connect, clientTag);
    // Ieskau reikiamo kliento
    Client clientInfo = this->clients->FindByID(connect->client_id);
    reciverID = connect->client_id;
    // Kuriu CONNECT paketa
    connectCommand * cCMD = (struct connectCommand*)
            &buffer.data()[ sizeof ( header) ];
    cCMD->command = htons(CONNECT);
    // Pildau connect komanda
    cCMD->tag = htons(clientTag);
    cCMD->source_port = htons(connect->source_port);
    cCMD->destinatio_port = htons(connect->destination_port);
    cCMD->client_id = htonl(socket);
    cCMD->tunnelID = htonl(tunnel_id);
    // Kuriu gNet paketo antraste
    header* head = (struct header*) &buffer.data()[0];
    head->tag = htons(0);
    head->lenght = htonl(sizeof (connectCommand));

    duomCount = sizeof (header) + sizeof (connectCommand);
}

void GServer::GCommandExecution::commandJsonInitCommand(vector<char>& buffer,
        int& duomCount, int socket, int& reciverID) {
    jsonConnectInitCommand* connect = (struct jsonConnectInitCommand*)
            &buffer.data()[ sizeof ( header) ];
    // Suvartau paketo laukus i tinkama puse
    connect->client_id = ntohl(connect->client_id);
    connect->destination_port = ntohs(connect->destination_port);
    connect->source_port = ntohs(connect->source_port);
    connect->tag = ntohs(connect->tag);
    connect->socketID = ntohl(connect->socketID);
    // Generuojama zyme clientui
    int clientTag = this->tagGenerator->Generate(this->tunnels);
    // Kuriu nauja tuneli
    int tunnel_id = this->tunnels->InitConnect(socket, connect, clientTag);
    // Ieskau reikiamo kliento
    Client clientInfo = this->clients->FindByID(connect->client_id);
    reciverID = connect->client_id;
    // Kuriu CONNECT paketa
    jsonConnectCommand * cCMD = (struct jsonConnectCommand*)
            &buffer.data()[ sizeof ( header) ];
    cCMD->command = htons(JSON_CONNECT);
    // Pildau connect komanda
    cCMD->tag = htons(clientTag);
    cCMD->source_port = htons(connect->source_port);
    cCMD->destinatio_port = htons(connect->destination_port);
    cCMD->client_id = htonl(socket);
    cCMD->tunnelID = htonl(tunnel_id);
    cCMD->socketID = htonl(connect->socketID);
    // Kuriu gNet paketo antraste
    header* head = (struct header*) &buffer.data()[0];
    head->tag = htons(0);
    head->lenght = htonl(sizeof (jsonConnectCommand));

    duomCount = sizeof (header) + sizeof (jsonConnectCommand);
}

void GServer::GCommandExecution::commandConnecACK(vector<char>& buffer,
        int& duomCount, int socket, int& reciverSocket) {
    // Atejo atsakas is sujungimo
    connectAckCommand* connectAck =
            (struct connectAckCommand*) &buffer.data()[sizeof (header)];
    // Suvartau atejusiuos duoemnis teisinga tvarka
    connectAck->status = ntohs(connectAck->status);
    connectAck->tunnelID = htonl(connectAck->tunnelID);
    // Baigiu pildyti tunelio duomenis
    tunnel* tunelis = this->tunnels->ConnectAck(connectAck);

    // Formuoju CONNECT_INT_ACK paketa
    connectInitAckCommand* ack =
            (struct connectInitAckCommand*) &buffer.data()[sizeof (header)];

    ack->command = htons(INIT_CONNECT_ACK);
    // Nustatau iniciatoriaus puses TAG zyme
    ack->adm_tag = htons(tunelis->adm_tag);
    if (tunelis == NULL) {
        // Nepavykus rasti tunelio
        ack->status = htons(FAULT);
        ack->client_id = htonl(socket);
        ack->adm_port = htons(-1);
        ack->client_id = htons(-1);
    } else {
        ack->status = htons(tunelis->status);
        ack->client_id = htonl(tunelis->cln_socket);
        ack->adm_port = htons(tunelis->adm_port);
        ack->cln_port = htons(tunelis->cln_port);
    }
    // Pildau header struktura
    header* head = (struct header*) &buffer.data()[0];
    head->tag = htons(0);
    head->lenght = htonl(sizeof (connectInitAckCommand));

    duomCount = sizeof (header) + sizeof (connectInitAckCommand);
    reciverSocket = tunelis->adm_socket;
}

void GServer::GCommandExecution::commandJsonConnecACK(vector<char>& buffer,
        int& duomCount, int socket, int& reciverSocket) {
    // Atejo atsakas is sujungimo
    jsonConnectAckCommand* connectAck =
            (struct jsonConnectAckCommand*) &buffer.data()[sizeof (header)];
    // Suvartau atejusiuos duoemnis teisinga tvarka
    connectAck->status = ntohs(connectAck->status);
    connectAck->tunnelID = htonl(connectAck->tunnelID);
    // Baigiu pildyti tunelio duomenis
    tunnel* tunelis = this->tunnels->ConnectAck(connectAck);
    int jsonSocket = connectAck->socketID;
    // Formuoju CONNECT_INT_ACK paketa
    jsonConnectInitAckCommand* ack =
            (struct jsonConnectInitAckCommand*) &buffer.data()[sizeof (header)];

    ack->command = htons(JSON_INIT_CONNECT_ACK);
    // Nustatau iniciatoriaus puses TAG zyme
    ack->adm_tag = htons(tunelis->adm_tag);
    ack->socketID = jsonSocket;
    if (tunelis == NULL) {
        // Nepavykus rasti tunelio
        ack->status = htons(FAULT);
        ack->client_id = htonl(socket);
        ack->adm_port = htons(-1);
        ack->client_id = htons(-1);
    } else {
        ack->status = htons(tunelis->status);
        ack->client_id = htonl(tunelis->cln_socket);
        ack->adm_port = htons(tunelis->adm_port);
        ack->cln_port = htons(tunelis->cln_port);
    }
    // Pildau header struktura
    header* head = (struct header*) &buffer.data()[0];
    head->tag = htons(0);
    head->lenght = htonl(sizeof (jsonConnectInitAckCommand));

    duomCount = sizeof (header) + sizeof (jsonConnectInitAckCommand);
    reciverSocket = tunelis->adm_socket;
}

void GServer::GCommandExecution::commandClientConnect(vector<char>& buffer,
        int& duomCount, int socket, int& reciver) {
    clientConnectCommand* cmd =
            (struct clientConnectCommand*) &buffer.data()[sizeof (header)];
    // Nustatau zyme
    cmd->tag = ntohs(cmd->tag);
    // Ieskau is turimu jungciu saraso kam persiusti
    int cli_socket = -1, cli_tag = -1;
    this->tunnels->FindByPear(socket, cmd->tag, cli_socket, cli_tag);

    if (cli_socket != -1 && cli_tag != -1) {
        // PAvyko rasti kam persiusti
        // formuoju BEGIN_READ paketa
        beginReadCommand* read = (struct beginReadCommand*) &buffer.data()[sizeof (header)];
        read->command = htons(BEGIN_READ);
        read->tag = htons(cli_tag);
        // Formuoju antraste
        header* head = (struct header*) &buffer.data()[0];
        head->tag = htons(0);
        head->lenght = htonl(sizeof (beginReadCommand));

        duomCount = sizeof (header) + sizeof (beginReadCommand);
        reciver = cli_socket;
    } else {
        // Nepavyko rasti kam persiusti
        this->logger->logError(this->className, "Nepavyko rasti kam siusti"
                " BEGIN_READ paketo");
    }
}

void GServer::GCommandExecution::commandBeginReadAck(vector<char>& buffer,
        int& duomCount, int socket, int& reciver) {
    beginReadAckCommand* cmd =
            (struct beginReadAckCommand*) &buffer.data()[sizeof (header)];
    // Nustatau zyme i gera isdestyma
    cmd->tag = ntohs(cmd->tag);

    // Ieskau jungties pagal zyme
    int adm_socket = -1, adm_tag = -1;
    this->tunnels->FindByPear(socket, cmd->tag, adm_socket, adm_tag);

    if (adm_socket != -1 && adm_tag != -1) {
        // Suradau jungti
        // Persiunciu administratoriui atsaka
        clientConnectAckCommand* ack = (struct clientConnectAckCommand*)
                &buffer.data()[sizeof (header)];
        // Pildau struktura
        ack->command = htons(CLIENT_CONNECT_ACK);
        ack->tag = htons(adm_tag);
        // PIldau antraste
        header* head = (struct header*) &buffer.data()[0];
        head->tag = htons(0);
        head->lenght = htonl(sizeof (clientConnectAckCommand));

        duomCount = sizeof (header) + sizeof (clientConnectAckCommand);
        reciver = adm_socket;
    } else {
        // Neradau jungties
        this->logger->logError(this->className, "Nepavyko rasti kam siusti "
                "CLIENT_CONNECT_ACK paketo");
    }
}

void GServer::GCommandExecution::commandCloseTunnel(vector<char>& buffer,
        int& duomCount, int socket, int& reciver) {
    // Susivartau gauta informacija
    closeTunnelCommand* close =
            (struct closeTunnelCommand*) &buffer.data()[sizeof ( header)];
    close->tag = ntohs(close->tag);

    // Salinu tuneli is tuneliu saraso
    tunnel tunelis = this->tunnels->RemoveBySocketTag(socket, close->tag);
    // Kintamaisis saugantis SOCKET id , kuriuo bus siunciamas atsakas

    // Tirkinu is kurios puses atejo CLOSE_TUNNEL
    // Ar is iniciatoriaus
    if (tunelis.adm_socket == socket) {
        // Nustatau i kliento
        reciver = tunelis.cln_socket;
        close->tag = htons(tunelis.cln_tag);
    } else {
        // Nustatau i iniciatoriaus
        reciver = tunelis.adm_socket;
        close->tag = htons(tunelis.adm_tag);
    }

    // Persiunciu CLOSE_TUNNEL komanda
    // Suvartau TAG

    close->command = htons(CLOSE_TUNNEL);

    // Pildau antraste
    header* head = (struct header*) &buffer.data()[0];
    head->tag = htons(0);
    head->lenght = htonl(sizeof (closeTunnelCommand));

    duomCount = sizeof (header) + sizeof (closeTunnelCommand);
}

void GServer::GCommandExecution::printClientList() {
    for (this->clientSocketListIterator = this->clientSocketList->begin(); this->clientSocketListIterator != this->clientSocketList->end(); ++this->clientSocketListIterator) {
        this->logger->logDebug(this->className, "[" + std::to_string(this->clientSocketListIterator->first) + "]" + std::to_string((*this->clientSocketListIterator->second).getSocket()));
    }
}