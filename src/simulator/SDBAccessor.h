
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SDBACCESSOR_H
#define SDBACCESSOR_H
#include "../input/IDBAccessor.h"
#include "SDB.h"

class SDBAccessor{
public:
    SDBAccessor(); 

    void addSpaceParticle( spaceParticle_t key, SpaceParticle * particle );
    int getSpaceParticlesNum();
    void getSpaceParticle(  spaceParticle_t key );
    
private:
    SDB* SDB_;
};
#endif //SDBACCESSOR_H

