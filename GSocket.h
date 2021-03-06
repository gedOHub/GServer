/* 
 * File:   GSocket.h
 * Author: gedas
 *
 * Created on Sekmadienis, 2016, kovas 27, 04.51
 */

#ifndef GSOCKET_H
#define GSOCKET_H
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cerrno>

#include "GObject.h"
#include "GConfig.h"
#include "GCommandExecution.h"

namespace GServer {
    
    class GCommandExecution;
    
    class GSocket : public GObject {
    public:
        // ##### Kintamieji #####
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        GSocket(GConfig* conf, GLogger* logger,  GCommandExecution* command);
        virtual ~GSocket();

        /** close **
         * Metodas skirtas baigti darbui su socketu */
        virtual void close();

        /** sendData **
         * Meotdas skirtas issiuti duomenis i tinkla per si socketa. Sia 
         * funkcija turi igyvendinti kiekvienas protokolas savaip. Rezultatas-
         * issiustu duomenu kiekis. 
         *  socketFd- socketo i kuri siusi nuemris
            data- suformuoti duomenys, kurie bus issiunciami*/
        virtual int sendData(char * data, int size);

        /** recive **
         * Metodas skirtas gauti duomenis is tinklo. Sia funkcija turi 
         * igyvendinti kiekvienas protokolas savaitp. Rezultatas- gautu 
         * duomenu kiekis */
        virtual int reciveData();
        
        /** reciveData **
         * Metodas skirtas gauti duomenis is tinklo. Rezultatas- gautu duomenu
         * kiekis. 
            buffer- nuoroda i buferi kuri gauti
            size- nurodoma kiek duomenu gauti*/
        virtual int reciveData( char* buffer, int size );

        /** getSocket**
         * Metodas skirtas grazinti soketo numeriui */
        int getSocket();

        /** acceptConnection **
         * Metodas skirtas priimti kliento prisjugimui. Metodas grazina naujai
         *  sukurti kliento objekta
         *  conf- objektas dirbantis su nustatymu failu
         *  maxDescriptor- maksimalaus deskritporiaus reiksme */
        virtual GServer::GSocket* acceptConnection(GServer::GConfig* conf,
                int &maxDescriptor);

        // ##### END Metodai #####
    protected:
        // ##### Kintamieji #####
        /** buffer **
         * Kintamasis skirtas saugoti gaunama ir siunciama informacija i tinkla. 
         * Maksimalu buferio dydi nusako nustatymu faile saugoma reiksme 
         * MAX_SCOKET_BUFFER_SIZE */
        std::vector<char> buffer;

        /** socket_descriptor **
         * Kintamasis skirtas saugoti failo deskriptoriaus numeri, kuris 
         * naudojamas bendrvmui su tinklo klientu. Numatyta reiksme- -1.
         * Placiau- https://en.wikipedia.org/wiki/File_descriptor */
        int socket_descriptor;

        /** logger
         * Kintamasis saugantis nuoroda i pranesimu rasimo objekta */
        GLogger* logger;

        /** remoteAddress **
         * Struktura, skirta saugoti priimamo kliento duomenims, kaip IP ir
         *  PORT */
        sockaddr_storage remoteAddress;

        /** remoteAddressSize **
         * Kintamasis saugantis remoteAddress strukturos dydi */
        socklen_t remoteAddressSize;

        /** skaitomiSocket**
         * Kintamasis skirtas saugoti visu skaitomu socketu saraso nuoroda */
        fd_set* skaitomiSocket;

        /*** commands ***
         * Kintamasis skirtas saugoti nuoroda i komandu apdorojimo objekta */
        GCommandExecution* commands;
        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** createSocket **
         * Metodas skirtas sukurti sistemos resursaui- socket. Si metoda 
         * realizuoja kiekviena vaiko klase atskirai. 
            socketFamily- kokio tipo tinklu bus bendraujama
            socketType- kokiu principu bus bendraujama
            socketProtocol- kokiu protokolu bus bendraujama
            socketFlag- papildomi socket nustatymai
            result - kintamsis saugnatis gautus rezultatus is IP ir PORT 
         * kombinacijos
         Placiau: https://msdn.microsoft.com/en-us/library/windows/desktop/ms737530(v=vs.85).aspx*/
        virtual int createSocket(char* ip, char* port, int socketFamily,
                int socketType, int socketProtocol, int socketFlag, 
                addrinfo *& result);

        /** createServerScoket **
         * Metodas skirtas sukurti serverio socketa, kuris sukuria socketa, 
         * paruposia ji klausimuisi ir pradeda klausytis jungciu 
            socketFamily- kokio tipo tinklu bus bendraujama
            socketType- kokiu principu bus bendraujama
            socketProtocol- kokiu protokolu bus bendraujama
            socketFlag- papildomi socket nustatymai
         */
        virtual int createServerScoket(char* ip, char* port, int socketFamily,
                int socketType, int socketProtocol, int socketFlag);

        /** resizeBuffer **
         * Metodas skirtas pertvarkyti buferio dydi i nurodyta. Buferis negali 
         * buti didesnes reiksmes nei nurodyta konfiguracinaime faile. Metodo 
         * rezultatas- naujas pertvarkytas dydis.
            newSize- naujas pageidaujamas buferio dydis*/
        int resizeBuffer(int newSize);

        /** checkMaxDescriptor **
         * Metodas skirtas nustatyti ar esamas deskriuptorius yra didenis nei 
         * dabartinis didenis deskritprius */
        void checkMaxDescriptor(int& maxDescriptor);
        
        /** acceptConnectionDescriptor **
         * Metodas skirtas priimti naujo sujungimo deskriptoriui ir ji grazinti.
         *  Rezultatas- naujos jungties deskriptrius */
        virtual int acceptConnectionDescriptor();
        
        /** listen **
         * Metodas sksirtas pradeti klausimuisi klientu prisjungimu nurodytu 
         * prievadu. Placiau: http://linux.die.net/man/2/listen*/
        virtual void listenSocket();
        // ##### END Metodai #####
    private:
        // ##### Kintamieji #####
        /** MAX_BUFFER_SIZE **
         * Konstanta nurodanti koks maksimalus gali buti buferio dydis */
        const int MAX_BUFFER_SIZE;

        // ##### END Kintamieji #####
        // #####################################################################
        // ##### Metodai #####
        /** setSize **
         * Metodas skirtas nustatyti buferio dydziui. Grazinama reiksme- 
         * naujas buferio dydis.
            newSize- naujas pageidaujamas buferio dydis*/
        int setBufferSize(int newSize);

        /** bind ** 
         Metodas skirtas socketo paruosimui klausimuisi
            result- kintamsis saugnatis gautus rezultatus is IP ir PORT 
         * kombinacijos. Placiau: http://linux.die.net/man/2/bind*/
        void bindSocket(addrinfo * result);

        // ##### END Metodai #####
    };
}

#endif /* GSOCKET_H */

