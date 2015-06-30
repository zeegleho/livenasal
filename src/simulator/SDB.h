
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SDB_H
#define SDB_H
#include <map>
#include "spaceParticle.h"
typedef std::map<spaceParticle_t, SpaceParticle*> particles_list_t;
typedef std::pair<int, SpaceParticle*> particles_list_item_t;

class SDB {
public:
    SDB();
    void addSpaceParticle( int,  SpaceParticle* );
    unsigned int getSpaceParticlesNum();
    SpaceParticle* getSpaceParticle(  spaceParticle_t key );
private:
    particles_list_t  particles_;
};
#endif //SDB_H
