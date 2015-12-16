/* 
 * File:   TagGenerator.h
 * Author: developer
 *
 * Created on May 7, 2014, 11:07 PM
 */

#ifndef TAGGENERATOR_H
#define	TAGGENERATOR_H
#include "TunnelContainer.h"

class TagGenerator {
public:
    TagGenerator();
    TagGenerator(const TagGenerator& orig);
    virtual ~TagGenerator();
    int Generate( TunnelContainer* tunnels );
private:
    // Generuojama nuo 1000 iki 65535 zymes
    int tag;
    int MIN;
    int MAX;
    
    void Reset();
};

#endif	/* TAGGENERATOR_H */

