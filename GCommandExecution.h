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
        // ##### END Metodai #####
    };
}

#endif /* GCOMMANDEXECUTION_H */

