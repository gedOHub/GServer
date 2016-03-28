/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GObject.h
 * Author: gedas
 *
 * Created on Pirmadienis, 2016, kovas 28, 16.22
 */

#ifndef GOBJECT_H
#define GOBJECT_H

class GObject {
public:
    // ##### Kintamieji #####
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    GObject();
    virtual ~GObject();
    
    /* getClassName
     * Metodas skirtas grazinti klases padavinimui */
    std::string getClassName();
    // ##### END Metodai #####
private:
    // ##### Kintamieji #####
    /* className
     * Kintamasis skirtas saugoti klases pavadinimui */
    std::string className;
    
    /* LOG_HEADER
     * Kintamasis skirtas saugoti antraste prie objekto su jo pavadinimu */
    std::string LOG_HEADER;
    // ##### END Kintamieji #####
    // #########################################################################
    // ##### Metodai #####
    // ##### END Metodai #####
};

#endif /* GOBJECT_H */

