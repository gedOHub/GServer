/* 
 * File:   structures.h
 * Author: developer
 *
 * Created on April 24, 2014, 10:15 AM
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H
#define MAX_COMPUTERNAME_LENGTH 15

// Komandu strukturos
// Komandu numeriai
enum Commands{
	HELLO = 99,                     // Kompiuterio duomenu perdavimas serveriui
	LIST = 1,                       // Prasimas grazinti klientu sarasa
	LIST_ACK = 11,                  // Atsakas i prasima grazinti klientu sarasa
        INIT_CONNECT = 100,             // Prasimas inicijuoti tuneli
        INIT_CONNECT_ACK = 200,         // Atsakas i tunelio inicaivima
        CONNECT = 300,                  // Komanda jungtis i tam tikra prievada
        CONNECT_ACK = 400,              // Atsakas i connect koamdna
        CLIENT_CONNECT = 555,           // Komanda, rodanti, kad kliento prohrama prpsijnge
	CLIENT_CONNECT_ACK = 666,	// ATSAKAS i CLIENT_CONNECT_ACK
        BEGIN_READ = 777,               // Leidimas pradeti skaitytma
        BEGIN_READ_ACK = 888,           // Atsakas i BEGIN_READ
        CLOSE = 5,                      // Prasimas baigti rysi
};

// Tunelio statuso reiksmes;
enum CONNECTION_STATUS{
    INIT = 1,   // Sukurtas tunelis
    SOCKET_CREATED = 2, // Pavyko prisjungti rpei prievado
    FAULT = 3, // Nepavyko prisijungti prie prievado
};

#pragma pack(push, 1)	// Nustatom strukturas i tikra isdestyma

struct tunnel{
    int id;     // Tunelio id
    int adm_socket;   // Administratoriaus socketas
    int adm_port;       // Administratoriaus puseje atidarytas prievadas
    int adm_tag;        // Administratoriaus puseje nuedoajma zyme
    int cln_socket;     // Kliento socketas
    int cln_port;       // Prievadas i kuri administratorius nori jungtis
    int cln_tag;        // Kliento puseje naudojama zyme
    int status;         // Sujungimo statuso indikatorius
};

// gNet paketo antrastes struktura
struct header{
	uint16_t tag;	// dydis: 2
	uint32_t lenght;// dydis: 4
};

struct ClientInfo{
    char domainName[MAX_COMPUTERNAME_LENGTH + 1];	// KOmpiuterio srities vardas
    char pcName[MAX_COMPUTERNAME_LENGTH + 1];	// Kompiuterio vardas
    char userName[MAX_COMPUTERNAME_LENGTH + 1];	// Naudotojo vardas
};

// Kliento informacijos struktura
struct Client: ClientInfo{
    uint32_t id;     // KLiento ID sistemoje
};

/* --- KOMANDOMS --- */

struct Command{
	uint16_t command; // dydis 2
};

// HELLO
struct helloCommand : Command, ClientInfo{
};
// LIST
struct listCommand : Command{
        uint32_t page;		// dydis 4
};
// LIST_ACK
struct listAckCommand : Command{
    char success;       // True - pavyko suformuoti klientu sarasa
                        // False - nepavyko suformuoti klientu saraso
};
// CONNECT_INIT
struct connectInitCommand: Command{
    uint16_t destination_port;
    uint16_t source_port;
    uint16_t tag;
    uint32_t client_id;
};
// CONNECT
struct connectCommand:Command{
    uint16_t destinatio_port;   // Prievadas i kuri jungtis
    uint16_t tag;       // Zyme kuria naudoti klientui
    uint32_t tunnelID;  // Tunelio ID. I si tuneli gris rezultatai
};
// CONNECT_ACK
struct connectAckCommand: Command{
    uint32_t tunnelID;  // Tunelio id
    uint16_t status;    // Sujungimo statusas
};
// CONNECT_INIT_ACK
struct connectInitAckCommand: Command {
    uint16_t status;    // Sujungimo statusas
    uint32_t client_id; // Kliento id prie kurio jungtasi
    uint16_t adm_port;  // prievadas administartoriaus kompiuteryje
    uint16_t cln_port;  // Prievadas kliento kompiuteryje
};
// CLIENT_CONNECT
struct clientConnectCommand : Command{
    uint16_t tag;	// Srauto zyme
};
// CLIENT_CONNECT_ACK
struct clientConnectAckCommand : Command{
    uint16_t tag;
};
// BEGIN_READ
struct beginReadCommand : Command {
    uint16_t tag;	// Srauto zyme
};
// BEGIN_READ_ACK
struct beginReadAckCommand : Command {
    uint16_t tag;	// Srauto zyme
};

#pragma pack(pop) // nustatom i normalu isdestyma

#endif	/* STRUCTURES_H */

