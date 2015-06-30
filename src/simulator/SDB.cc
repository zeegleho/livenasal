
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "SDB.h"

SDB::SDB(){
}

void SDB::addSpaceParticle( int key,  SpaceParticle* spaceParticle ){
    particles_.insert(  particles_list_item_t( key,  spaceParticle ) );
}
unsigned int SDB::getSpaceParticlesNum(){
    return particles_.size();
}

SpaceParticle* SDB::getSpaceParticle( spaceParticle_t key ){
    return particles_[key];
}
