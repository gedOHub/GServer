/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GCommandExecution.h
 * Author: gedas
 *
 * Created on Šeštadienis, 2016, balandis 23, 14.04
 */

#ifndef GCOMMANDEXECUTION_H
#define GCOMMANDEXECUTION_H

#include "GObject.h"
#include "GLogger.h"
#include "GTagGenerator.h"
#include "GClientContainer.h"
#include "GSocket.h"

namespace GServer {

    class GCommandExecution : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** GCommandExecution ***
         * Metodas skirtas sukurti GCommandExecution. Si klase analizuoja ir
         * vykdo gautas komandas. 
            logger- pranesimu isvedimo objektas 
            tagGenerato- objektas, generuojantis zymas
            clients- klientu sarao objektas*/
        GCommandExecution( GLogger* logger, GTagGenerator* tagGenerator, 
                GClientContainer* clients );
        virtual ~GCommandExecution();
        
        /*** executeCommand ***
         * Metodas ksirtas nuskaityti is buferio komanda ir grazinti atsakyma i 
         * ta pati buferi. Rezultatas- true, jei pavyko apdoroti komanda, false,
         *  jei ne 
            buffer- buferis, kuriame gauti ir apdorojimi duomenys
            size- apdoroto atsakymo dydis buferyje
            socket- kliento objektas, kuris gavo duomenis */
        bool executeCommand(vector<char>& buffer, int& size, GSocket* socket);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /*** logger ***
         * Kintamassis skirtas saugoti nuoroda i pranesimu isvedimo objekta */
        GLogger* logger;
        
        /*** tagGenerator ***
         * Kintamasis skirtas asugoti nuoroda i zymy generavimo objekta */
        GTagGenerator* tagGenerator;
        
        /*** clients ***
         * Kintamasis saugo nuoroda i klientu saraso objekta */
        GClientContainer* clients;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** analizeHeader ***
         * Metodas skirtas nustatyti atejusiu duomenu headerio reiksmems. 
         * Rezultatas- true, pavykus nustatyti, false- nepavykus
            buffer- buferis, kuraime ieskoma
            tag- nustatyta tag reiksme
            size- nustatyta duomenu dydzio reiksme*/
        bool analizeHeader(char* buffer, int& tag, int& size);
        
        /*** analizeCommandHeader ***
         * Metodas skirtas nustatyti atejusios koamndos lauku reiksmes. 
         * Rezultatas- true, pavykus nustatyti, false- nepavykus
            buffer- buferis, kuraime ieskoma
            command- nustatyta komandos reiksme*/
        bool analizeCommandHeader(char* buffer, int& command);
        
        /*** commandHello ***
         * Metodas skirtas ivykdyti HELLO komandai. Rezultatas pridetas kliento
         *  objektas 
            buffer- buferis, kuriame saugomi duomenys
            socket- socketas, kuriame gauta si komanda*/
        Client commandHello(char* buffer, int socket);
        // ##### END Metodai #####
    };
}

#endif /* GCOMMANDEXECUTION_H */

