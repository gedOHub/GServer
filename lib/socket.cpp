/* 
 * File:   socket.cpp
 * Author: gedas
 * 
 * Created on February 9, 2014, 3:01 PM
 */

#include "socket.h"

Socket::Socket(const char* IP, const char* PORT) {
    this->IP = IP;
    this->PORT = PORT;
    this->debug = false;
    this->init();
}

Socket::Socket(const char* IP, const char* PORT, bool debug) {
    this->IP = IP;
    this->PORT = PORT;
    this->debug = debug;
    this->init();
}

/**
 * Inicijuoja socketa serveriui
 * @return 0 - jei viskas pavyko gerai
 * @return 1 - jei nepavyko gauti adreso duomenu
 */
int Socket::init() {
    if (this->getAddressInfo() == 0) {
        // Pavyko gauti adreso duomenis
        if (debug) {
            std::cout << "Pavyko gauti adreso duomenis\n";
            this->printResult();
        }
        this->socketDescriptor = ::socket(this->rezelt->ai_family,
                this->rezelt->ai_socktype, this->rezelt->ai_protocol);
        if (this->socketDescriptor == -1) {
            std::cout << "Nepavyko gauti socket deskriptoriaus\n";
        } else {
            //printf("Socketo deskriptorius: %d", this->socketDescriptor);
            std::cout << "Socketo deskriptorius: " << this->socketDescriptor << std::endl;
            if (this->bind() != -1) {
                std::cout << "Bindinimas pavyko\n";
                if (this->listen() != -1) {
                    std::cout << "Pavyko klausytis" << std::endl;
                } else {
                    std::cout << "Nepavyko klausytis" << std::endl;
                    printf("Klaida: %s\n", strerror(errno));
                }
            } else {
                std::cout << "Bindinimas nepavyko!\n";
                printf("Bind: %s\n", strerror(errno));
            }
        }
        return 0;
    } else {
        // Nepavyko gauti adreso duomenu
        std::cout << "Nepavyko gauti adreso duomenu\n";
        return -1;
    }
}

int Socket::getAddressInfo() {
    // Paieskos nustatymai //
    addrinfo hint; // Paieskos kriterijai
    memset(&hint, 0, sizeof hint);
    hint.ai_family = AF_UNSPEC; // IPv4 ar IPv6
    hint.ai_flags = AI_PASSIVE; // Sakom, kad bus serverinis socketas
    hint.ai_socktype = SOCK_STREAM; // Socketo tipas (TCP)

    if (this->debug) {
        // Ijungtas debuginimas
        int status = getaddrinfo(this->IP, this->PORT, &hint, &this->rezelt);
        if (status == 0) {
            std::cout << "Adreso duomenys gauti sekmingai\n";
            return status;
        } else {
            fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
            return status;
        }
    } else {
        // Neijungtas debuginimas
        return getaddrinfo(this->IP, this->PORT, &hint, &this->rezelt);
    }
}

int Socket::bind() {
    return ::bind(this->socketDescriptor, this->rezelt->ai_addr, this->rezelt->ai_addrlen);
}

int Socket::listen() {
    return ::listen(this->socketDescriptor, 10);
}

int Socket::accept(sockaddr_storage * clientAddress) {
    socklen_t size = sizeof (struct sockaddr_in6);
    std::cout << "Dydis: " << size << std::endl;
    std::cout << "Socket nr: " << this->socketDescriptor << std::endl;
    int status = ::accept(this->socketDescriptor, (struct sockaddr *) clientAddress, &size);
    if (status == -1) {
        // Klausantis ivyko klaida
        printf("Klaida: %s\n", strerror(errno));
    }
    return status;
}

void Socket::printResult() {
    if (this->debug && this->rezelt == NULL) {
        std::cout << "Rezultatau sarasas tuscias/n";
    }

    if (this->rezelt != NULL) {
        // Pavyko surasti duomenis
        // Einam per visus gautus rezultatus
        addrinfo * temp;
        char ipstr[INET6_ADDRSTRLEN];
        for (temp = this->rezelt; temp != NULL; temp = temp->ai_next) {
            void *addr;
            char *ipver;

            // get the pointer to the address itself,
            // different fields in IPv4 and IPv6:
            if (temp->ai_family == AF_INET) { // IPv4
                struct sockaddr_in *ipv4 = (struct sockaddr_in *) temp->ai_addr;
                addr = &(ipv4->sin_addr);
                ipver = "IPv4";
            } else { // IPv6
                struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) temp->ai_addr;
                addr = &(ipv6->sin6_addr);
                ipver = "IPv6";
            }
            // convert the IP to a string and print it:
            inet_ntop(temp->ai_family, addr, ipstr, sizeof ipstr);
            printf("  %s: %s\n", ipver, ipstr);
        }
    }
}

void Socket::close() {
    // Uzdaro socketa
    ::shutdown(this->socketDescriptor, 2);
}

void Socket::close(int how) {
    // Socketo uzdarymas pagal norima kriteriju
    // Galimi variantai
    //  0 - Tolimesni gavimai uzdrausti
    //  1 - Tolimesni siuntimai uzzdrausti
    //  2 - Pilnai uzdaroma (tas pats kaip close)
    ::shutdown(this->socketDescriptor, how);
}

int Socket::getFileDescriptor() {
    return this->socketDescriptor;
}

Socket::~Socket() {
    freeaddrinfo(this->rezelt);
    this->close();
    std::cout << "Socket objektas sunaikintas" << std::endl;
}

