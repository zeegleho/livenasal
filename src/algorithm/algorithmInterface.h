
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef OCTAVEINTERFACE_H
#define OCTAVEINTERFACE_H

#include <vector>
#include <set>
#include "../simulator/simulatorGlobal.h"

class AlgorithmInterface{
public:
    static bool inited_;
    static void init();
    static void clearup();

    static double interP1( std::vector<double> v1, std::vector<double> v2, double xi );
    static double interP2( std::vector<double> v1, std::vector<double> v2, std::vector<double> v3, double xi, double yi );


    static void createSDB( );
    static bool interP2s( std::vector<std::vector<spaceParticle_t>>& zi,
		   std::set<spaceParticle_t>&xv,
		   std::set<spaceParticle_t>&yv,
		   std::vector<std::vector<spaceParticle_t>>& zv,
		   spaceParticle_t x_max,spaceParticle_t x_min,
		   spaceParticle_t y_max,spaceParticle_t y_min
		 );

};
#endif //OCTAVEINTERFACE_H
