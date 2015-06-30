
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SPACEPARTICAL_H
#define SPACEPARTICAL_H
#include "../console/global.h"
#include "position.h"
#include "spaceParticleFace.h"
#include "airPartical.h"


class SpaceParticle{
public:
    SpaceParticle();
    int x( int index );
    int y( int index );
    int z( int index );
    int getX( int index );
    int getY( int index );
    int getZ( int index );
    void setX( );
    void setY( );
    void setZ( );

    Position getPosition( int index );
    void setPosition( Position p );

    SpaceParticleFace getFace( int index );

    AirPartical getAirPartical( int index );
    void setAir_partical( AirPartical air_partical_);

private:
    Position *position_;
    AirPartical *air_partical_;
};
#endif //SPACEPARTICAL_H
