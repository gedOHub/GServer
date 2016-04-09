/* 
 * File:   TunnelContainer.cpp
 * Author: developer
 * 
 * Created on April 30, 2014, 1:28 PM
 */

#include "TunnelContainer.h"

TunnelContainer::TunnelContainer() {
    this->skaitliukas = 0;
}

TunnelContainer::TunnelContainer(const TunnelContainer& orig) {
}

TunnelContainer::~TunnelContainer() {
}

int TunnelContainer::InitConnect(int admSocket, connectInitCommand* connect, int clientTag) {
    // Kuriu tunelio objekta
    tunnel tunelis;
    tunelis.id = this->GetID();
    // Pildau tunelio administratoriaus sturktura
    tunelis.adm_port = connect->source_port;
    tunelis.adm_tag = connect->tag;
    tunelis.adm_socket = admSocket;
    // Pildau tunelio kliento dali
    tunelis.cln_port = connect->destination_port;
    tunelis.cln_tag = clientTag;
    tunelis.cln_socket = connect->client_id;
    // Nustatau tunelio statusa
    tunelis.status = INIT;
    // Pridedu prie tuneliu saugyklos
    this->container.push_front(tunelis);
    // Grazinu tunelio id
    return tunelis.id;
}

int TunnelContainer::InitConnect(int admSocket, jsonConnectInitCommand* connect, int clientTag) {
    // Kuriu tunelio objekta
    tunnel tunelis;
    tunelis.id = this->GetID();
    // Pildau tunelio administratoriaus sturktura
    tunelis.adm_port = connect->source_port;
    tunelis.adm_tag = connect->tag;
    tunelis.adm_socket = admSocket;
    // Pildau tunelio kliento dali
    tunelis.cln_port = connect->destination_port;
    tunelis.cln_tag = clientTag;
    tunelis.cln_socket = connect->client_id;
    // Nustatau tunelio statusa
    tunelis.status = INIT;
    // Pridedu prie tuneliu saugyklos
    this->container.push_front(tunelis);
    // Grazinu tunelio id
    return tunelis.id;
}

//TODO: Patikra del statuso

tunnel* TunnelContainer::ConnectAck(connectAckCommand* ack) {
    try {
        tunnel* tunelis = this->FindById(ack->tunnelID);
        tunelis->status = ack->status;
        return tunelis;
    } catch (exception e) {
        printf("ConnectAck\n");
    }
    return NULL;
}

//TODO: Patikra del statuso

tunnel* TunnelContainer::ConnectAck(jsonConnectAckCommand* ack) {
    try {
        tunnel* tunelis = this->FindById(ack->tunnelID);
        tunelis->status = ack->status;
        return tunelis;
    } catch (exception e) {
        printf("ConnectAck\n");
    }
    return NULL;
}

int TunnelContainer::GetID() {
    this->skaitliukas = this->skaitliukas + 1;
    return this->skaitliukas;
}

void TunnelContainer::FindByPear(int arr_socket, int arr_tag, int& dep_socket, int& dep_tag) {
    list<tunnel>::iterator it;
    for (it = this->container.begin(); it != this->container.end(); it++) {
        // Ieskau pagal admino duomenis
        if (it->adm_socket == arr_socket && it->adm_tag == arr_tag) {
            dep_socket = it->cln_socket;
            dep_tag = it->cln_tag;
            break;
        }
        // Ieskau pagal kliento duomenis
        if (it->cln_socket == arr_socket && it->cln_tag == arr_tag) {
            dep_socket = it->adm_socket;
            dep_tag = it->adm_tag;
            break;
        }
    }
}

tunnel* TunnelContainer::FindById(int id) {
    list<tunnel>::iterator it;
    for (it = this->container.begin(); it != this->container.end(); it++) {
        if (it->id == id) {
            return &(*it);
        }
    }
    return NULL;
}

bool TunnelContainer::IsClient(int tag) {
    list<tunnel>::iterator it;
    for (it = this->container.begin(); it != this->container.end(); it++) {
        // Ieskau pagal kliento duomenis
        if (it->cln_tag == tag)
            return true;
    }
    return false;
}

tunnel TunnelContainer::RemoveBySocketTag(int socket, int tag) {
    tunnel tunelis;
    // Begu per sarasa ir ieskau nuroditos kombinacijos
    list<tunnel>::iterator it;
    for (it = this->container.begin(); it != this->container.end(); it++) {
        // Tikrinu ar yra reikalinga kombinacija
        // Tikrinu iniciatoriaus puse po to kliento puse
        if ((it->adm_socket == socket && it->adm_tag == tag) ||
                (it->cln_socket == socket && it->cln_tag == tag)) {
            // Darau elemento kopija
            memcpy(&tunelis, &(*it), sizeof (tunnel));
            // Salinu is saraso
            container.erase(it);
            return tunelis;
        }
    }
    return tunelis;
}
