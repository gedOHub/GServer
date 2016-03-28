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
            NO_LOGGER = -1
        };
    };
}

#endif /* EXITCODES_H */

