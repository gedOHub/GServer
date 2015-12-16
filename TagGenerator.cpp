/* 
 * File:   TagGenerator.cpp
 * Author: developer
 * 
 * Created on May 7, 2014, 11:07 PM
 */

#include "TagGenerator.h"
#include "TunnelContainer.h"

TagGenerator::TagGenerator() {
    
    this->MIN = 1000;
    this->MAX = 65534;
            
    this->tag = MIN;
}

TagGenerator::TagGenerator(const TagGenerator& orig) {
}

TagGenerator::~TagGenerator() {
}

void TagGenerator::Reset(){
    this->tag = this->MIN;
}

int TagGenerator::Generate( TunnelContainer* tunnels ) {
    if(this->tag >= MAX)
        this->Reset();
    
    // Padidinam paskutine zyme
    this->tag = this->tag + 1;
    
    // Tikrinam ar tokia jau yra naudojama
    while(tunnels->IsClient(this->tag)){
        // Jei naudojama tada dar didinam
        this->tag = this->tag + 1;
        
        if(this->tag >= MAX)
            this->Reset();
    }
    
    return this->tag;
}

