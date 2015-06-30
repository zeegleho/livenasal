
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SDBCREATOR_H
#define SDBCREATOR_H
#include "SDBAccessor.h"
#include "SDB.h"
#include "createSpaceParticles.h"
#include "../input/IDBAccessor.h"
class SDBCreator {
public:
    SDBCreator();
    void createSDB(SDBAccessor*, IDBAccessor*  );
    spaceParticle_t getKey( spaceParticle_t, spaceParticle_t, spaceParticle_t );
    spaceParticle_t mapUnitX( double i );
    spaceParticle_t mapUnitY( double i );
    spaceParticle_t mapUnitZ( double i );
    spaceParticle_t mapUnit( double i, unsigned int dest_range, unsigned int src_range );
    SpaceParticle *addSpaceParticle( SDBAccessor* sdb_accessor, double x, double y, double z );

    double interP( double i, std::vector<double> v1, std::vector<double> v2 );
    double curveFitting( );

};
#endif //SDBCREATOR_H
