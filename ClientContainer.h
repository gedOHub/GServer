/* 
 * File:   ClientContainer.h
 * Author: developer
 *
 * Created on April 24, 2014, 4:05 PM
 */

#ifndef CLIENTCONTAINER_H
#define	CLIENTCONTAINER_H

#include <list>
#include <netinet/in.h>
#include "structures.h"
#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 20
#define OneMBofChar 1048576

using namespace std;

class ClientContainer {
public:
    ClientContainer();
    ClientContainer(const ClientContainer& orig);
    virtual ~ClientContainer();
    
    // Pridedu klientus
    void Add( int socket, char sritis[MAX_COMPUTERNAME_LENGTH+1], 
        char kompiuteris[MAX_COMPUTERNAME_LENGTH+1], 
        char naudotojas[MAX_COMPUTERNAME_LENGTH+1] );
    
    // Salinimas
    void DeleteByID( int id );
    Client DeleteByClient( char* sritis, char* kompiuteris, char* naudotojas );
    
    // Paieska
    Client FindByID( int id );
    Client FindByClient( char* sritis, char* kompiuteris, char* naudotojas );
    
    // Paruosimas issiuntimui
    void PrintPage( int id, int page, char* buffer, int &length );
    
private:
    std::list<Client> Container;        // Sarasas, kuriame saugomas
    char* printBuffer;  // Buferis klientu grazinimui
    
    // Pridedu klientus
    void Add( Client client );     // Generuoja ID numeri
};

#endif	/* CLIENTCONTAINER_H */
