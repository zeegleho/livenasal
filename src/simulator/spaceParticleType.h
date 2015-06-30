
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SPACEPARTICLETYPE_H 
#define SPACEPARTICLETYPE_H
#include "../console/global.h"

class  spaceParticleTypy{
public:

/*types*/
static const type_t type_unknown = 0x00;
static const type_t type_outer = 0x01;
static const type_t type_inner = 0x02;
static const type_t type_surface = 0x03;
static const type_t type_entrance = 0x04;

};

#endif //SPACEPARTICLETYPE_H
