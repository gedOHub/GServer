/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ServerSocket.cpp
 * Author: gedas
 * 
 * Created on Sekmadienis, 2016, kovas 27, 01.30
 */

#include "ServerSocket.h"

ServerSocket::ServerSocket() {
    try{
        // Priskiriu numatyta reiksme file_deskriptor
        this->file_deskriptor = -1;
        // Priskiriu numatyta reiksme buffer
        this->buffer = NULL;
    } catch ( int e){
        //TODO: prijungti LOGGER
    }
}

ServerSocket::~ServerSocket() {
    try{
        // ##### Isvalau BUFFER #####
        // Tirkinu ar buffer priskirtas
        if(this->buffer != NULL){
            // Buffer kintamasis buvo naudotas, isvalau
            delete[] this->buffer;
        }
        // ##### END Isvalau BUFER #####
    } catch(int e){
        //TODO: prijungti LOGGER
    }
}

