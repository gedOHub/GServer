/* 
 * File:   socket.h
 * Author: gedas
 *
 * Created on February 9, 2014, 3:01 PM
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef SOCKET_H
#define	SOCKET_H

class Socket {
public:
    Socket(const char* IP, const char* PORT);
    Socket(const char* IP, const char* PORT, bool debug);
    int accept(sockaddr_storage *);
    void close();
    void close(int);
    virtual ~Socket();
    int getFileDescriptor();
private:
    bool debug;
    const char* IP;
    const char* PORT;
    addrinfo * rezelt;
    
    int init();
    int bind();
    int listen();
    int getAddressInfo();
    void printResult();
    int socketDescriptor;
};

#endif	/* SOCKET_H */

