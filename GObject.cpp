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

GServer::GObject::GObject() {
    // Nustatau objekto pavadinima
    this->className = "GObject";
}

GServer::GObject::~GObject() {
}

std::string GServer::GObject::getClassName() {
    return this->className;
}

