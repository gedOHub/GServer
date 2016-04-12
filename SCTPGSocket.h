/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SCTPGSocket.h
 * Author: gedas
 *
 * Created on Antradienis, 2016, balandis 12, 04.41
 */

#ifndef SCTPGSOCKET_H
#define SCTPGSOCKET_H

#include "GSocket.h"


namespace GServer {

    class SCTPGSocket :public GSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        SCTPGSocket(GConfig* conf, GLogger* logger);
        virtual ~SCTPGSocket();
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
    };
}

#endif /* SCTPGSOCKET_H */

