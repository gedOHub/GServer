/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GObject.cpp
 * Author: gedas
 * 
 * Created on Pirmadienis, 2016, kovas 28, 16.22
 */

#include "GObject.h"

GObject::GObject() {
    // Nustatau objekto pavadinima
    this->className = "GObject";
    // Kuriu header'i
    std::stringstream s;
    s << "[" << this->className << "]";
    this->LOG_HEADER = s.str();
}

GObject::~GObject() {
}

std::string GObject::getClassName(){
    return this->className;
}

