/* 
 * File:   ClientContainer.h
 * Author: developer
 *
 * Created on April 24, 2014, 4:05 PM
 */

#ifndef CLIENTCONTAINER_H
#define CLIENTCONTAINER_H

#include <list>
#include <netinet/in.h>
#include "structures.h"
#include <stdio.h>
#include <string.h>

#define PAGE_SIZE 20
#define OneMBofChar 1048576

using namespace std;

namespace GServer {

    class ClientContainer {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** ClientContainer ***
         * Metodas skirtas sukurti ClientContainer tipo objektui. */
        ClientContainer();
        virtual ~ClientContainer();

        /*** Add ***
         * Metodas skirtas prideti kliento duomenis i klientu sarasa
            socket- kliento ndescriptrius 
            sritis- angl. domain, kompiuterio srieties pavadinimas
            kompiuteris- kompiuterio pavadinimas
            naudtojas- naudotojo pavadinimas*/
        void Add(int socket, char sritis[MAX_COMPUTERNAME_LENGTH + 1],
                char kompiuteris[MAX_COMPUTERNAME_LENGTH + 1],
                char naudotojas[MAX_COMPUTERNAME_LENGTH + 1]);

        /*** DeleteByID ***
         * Metodas skirtas pasalinti klienta is saraso pagal ID numeri 
            id- IDI numeris, dar zinomas kaip socket numeris*/
        void DeleteByID(int id);
        /*** DeleteByClient ***
         * Metodas skirtas pasalinti is klientu saraso pagal srities pavadinima,
         *  kompiuterio varda ir naudotojo varda. Rezultatas- pasalintas 
         * objektas
            sritis- angl. domain, kompiuterio srieties pavadinimas
            kompiuteris- kompiuterio pavadinimas
            naudtojas- naudotojo pavadinimas*/
        Client DeleteByClient(char* sritis, char* kompiuteris, char* naudotojas);

        /*** FindByID ***
         * Metodas skirtas rasti naudotjo objekta pagal ID. Rezultatas- radus 
         * grazinamas kliento objektas, jei ne tada NULL
            id- naudotojo ID- socket numeris*/
        Client FindByID(int id);
        
        /*** FindByClient ***
         * Metodas skirtas rasti naudotjo objekta pagal ID. Rezultatas- radus 
         * grazinamas kliento objektas, jei ne tada NULL
            sritis- angl. domain, kompiuterio srieties pavadinimas
            kompiuteris- kompiuterio pavadinimas
            naudtojas- naudotojo pavadinimas*/
        Client FindByClient(char* sritis, char* kompiuteris, char* naudotojas);

        /*** PrintPage ***
         * Metodas skirtas suformuoti klientu saraso dali i nurodyta buferi. 
            id- kliento ID, kurio nereikia atvaizduoti
            page- kelinto puslapio norima. I viena puslapi talpinama 20 klientu
            buffer- nuroda i buferi, kuriame formuojamas sarasas
            length- duomenu kiekio ilgis*/
        void PrintPage(int id, int page, char* buffer, int &length);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
        std::list<Client> Container; // Sarasas, kuriame saugomas
        char* printBuffer; // Buferis klientu grazinimui

        // Pridedu klientus
        void Add(Client client); // Generuoja ID numeri
        // Tirkinama ar egzistuoja nurodytas puslapis
        bool IsValidPage(int pageNr);
    };
}
#endif /* CLIENTCONTAINER_H */
