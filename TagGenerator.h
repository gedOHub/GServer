/* 
 * File:   TagGenerator.h
 * Author: developer
 *
 * Created on May 7, 2014, 11:07 PM
 */

#ifndef TAGGENERATOR_H
#define TAGGENERATOR_H
#include "TunnelContainer.h"
#include "GObject.h"
#include "GLogger.h"

namespace GServer {

    class TagGenerator : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** TagGenerator ***
         * Metodas skirtas sukurti TagGenerator tipo objektui. Sis objektas 
         * atsakingas uz unikaliu zymiu kurima ir grazinima tolimesniam 
         * naudojimui 
            logger- pranesimu isvedimo objektas*/
        TagGenerator( GServer::GLogger* logger );
        
        virtual ~TagGenerator();
        
        /*** Generate ***
         * Metodas skirtas grazinti sekancia laisva skaitliuko reiksme. 
         * Rezultatas- nauja, nenaudojama zyme */
        int Generate(TunnelContainer* tunnels);
        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /*** tag ***
         * Kintamasis skirtas saugoti dabartinei skaitliuko reiksmei */
        int tag;
        
        /*** MIN ***
         * Kintamasis skirtas suagoti maziausiai galimai reiksmei */
        int MIN;
        
        /*** MAX ***
         * Kintamasis skirtas saugoti didziausaii glaimai reiksmei */
        int MAX;
        
        /*** logger ***
         * Kintasis skirtas saugoti nuorodao i pranesimu isvedimu objeta */
        GServer::GLogger* logger;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /*** reset ***
         * Metodas skirtas nustatyti skaitliuka i maziausia glaima reiksme */
        void Reset();
        // ##### END Metodai #####
        // Generuojama nuo 1000 iki 65535 zymes

    };
}

#endif /* TAGGENERATOR_H */

