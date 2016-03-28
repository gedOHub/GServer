/* 
 * File:   STCPServerSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.54
 */

#ifndef STCPSERVERSOCKET_H
#define STCPSERVERSOCKET_H

#include "ServerSocket.h"

namespace GServer{
    class STCPServerSocket : public ServerSocket {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        STCPServerSocket();
        STCPServerSocket(const STCPServerSocket& orig);
        virtual ~STCPServerSocket();
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #########################################################################
        // ##### Metodai #####
        // ##### END Metodai #####
    };
}

#endif /* STCPSERVERSOCKET_H */

