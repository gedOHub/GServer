/* 
 * File:   exitCodes.h
 * Author: gedas
 *
 * Created on Pirmadienis, 2016, kovas 28, 18.31
 */

#ifndef EXITCODES_H
#define EXITCODES_H

/* Sis failas reikalingas aprasyti visus programos iseigos kodus*/
namespace GServer{
    // Programos iseigos kodai
    struct EXIT_CODES{
        enum {
            // Programa baigia darba normaliui
            NORMAL = 0,
            // Programa baigia darba, nes nesukurtas loginimo objektas
            NO_LOGGER = -1,
            // Nepavyko sukurti buferio su atitinkamu dydzio
            SOCKET_BUFFER_TO_SMALL = -2,
            // Nepavyko atverti skaitymui konfigracinio failo
            ERROR_OPENNING_CONFIG_FILE = -3,
            // Rasta  klaida nustatymu faile
            ERROR_IN_CONFIG_FILE = -4,
            // Nepavyko rasti norimo nustatimo
            CONFIG_NOT_FOUND = -5,
            // Rasta nepalaikoma reiksme nustatymu faile
            UNKNOWN_CONFIG_VALUE = -6,
            // Nepavyko nuskiatyti konfiguraciniop rakto duomenu
            UNABLE_READ_CONFIG = -7
        };
    };
}

#endif /* EXITCODES_H */

