
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef INTERP_H
#define INTERP_H

#include <octave/oct.h>
#include <octave/octave.h>
#include <octave/parse.h>
#include <octave/toplev.h> /* do_octave_atexit */

class InterP{
public:
    static double interP1( std::vector<double> v1, std::vector<double> v2, double xi );
    static double interP2( std::vector<double> v1, std::vector<double> v2, std::vector<double> v3,double xi, double yi );
    static void createSDB( );

};
#endif //INTERP_H
