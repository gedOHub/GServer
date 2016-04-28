/* 
 * File:   TunnelContainer.h
 * Author: developer
 *
 * Created on April 30, 2014, 1:28 PM
 */

#ifndef TUNNELCONTAINER_H
#define TUNNELCONTAINER_H

#include <list>
#include <netinet/in.h>
#include "structures.h"
#include "GObject.h"
#include <stdio.h>
#include <string.h>

using namespace std;
namespace GServer {

    class GLogger;
    
    class GTunnelContainer : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** TunnelContainer ***
         * Metodas skirtas sukurti TunnelContainer tipo objektui 
            logger- nuoroda i obejtka,  kuris atlieka inforacijos ivedimus*/
        GTunnelContainer(GLogger* logger);
        virtual ~GTunnelContainer();
        
        //TODO: papildyti aprasyma
        /*** InitConnect ***
         * Metodas skirtas inicijuoti tunelio sujungimui is administratoriaus 
         * puses. Rezultatas- sujungimo tunelio ID 
            admSocket- administratoriaus ID
            connect- connectInitCommand struktura su klieno duomenimis
            clientTag- kliento */
        int InitConnect(int admSocket, connectInitCommand* connect, int clientTag);
        // ##### END Metodai #####
        

        
        // Veiksmai kai yra inicijuojamas tunelis is administratoiaus puses
        int InitConnect(int admSocket, jsonConnectInitCommand* connect, int clientTag);
        tunnel* ConnectAck(connectAckCommand* ack);
        tunnel* ConnectAck(jsonConnectAckCommand* ack);
        void FindByPear(int arr_socket, int arr_tag, int &dep_socket, int&dep_tag);
        bool IsClient(int tag);
        // Metodas skirtas pasalinti is saraso tuneli pagal naudotojo ID ir zyme (TAG)
        tunnel RemoveBySocketTag(int socket, int tag);

        
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        int skaitliukas;
        list<tunnel> container;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        int GetID();
        tunnel* FindById(int id);
        // ##### END Metodai #####
        

        
    };
}
#endif /* TUNNELCONTAINER_H */

