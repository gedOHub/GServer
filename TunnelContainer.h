/* 
 * File:   TunnelContainer.h
 * Author: developer
 *
 * Created on April 30, 2014, 1:28 PM
 */

#ifndef TUNNELCONTAINER_H
#define	TUNNELCONTAINER_H

#include <list>
#include <netinet/in.h>
#include "structures.h"
#include <stdio.h>
#include <string.h>

using namespace std;

class TunnelContainer {
public:
    TunnelContainer();
    TunnelContainer(const TunnelContainer& orig);
    
    // Veiksmai kai yra inicijuojamas tunelis is administratoiaus puses
    int InitConnect( int admSocket, connectInitCommand* connect, int clientTag ); 
    tunnel* ConnectAck(connectAckCommand* ack);
    void FindByPear(int arr_socket, int arr_tag, int &dep_socket, int&dep_tag);
    bool IsClient(int tag);
    
    virtual ~TunnelContainer();
private:
    int skaitliukas;
    list<tunnel> container;
    
    int GetID();
    tunnel* FindById(int id);
};

#endif	/* TUNNELCONTAINER_H */

