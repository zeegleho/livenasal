
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "interP.h"

#define USE_OCTAVE 

double  InterP::interP1( std::vector<double> v1, std::vector<double> v2, double xi ){
#ifdef USE_OCTAVE 

    octave_value_list functionArguments;
    Matrix inMatrix01 ( 1, (int)(v1.size()) );
    for( unsigned int i=0;i<v1.size();i++){
	inMatrix01 (i) = v1[i];
    }


    Matrix inMatrix02 ( 1, v2.size());
    for( unsigned int i=0;i<v2.size();i++){
	inMatrix02 (i) = v2[i];
    }

    functionArguments(0) = inMatrix01;
    functionArguments(1) = inMatrix02;
    functionArguments(2) = xi;
    functionArguments(3) = "nearest";

    const octave_value_list result = feval ("interp1", functionArguments, 1);     //interp
    Matrix outMatrix;
    outMatrix = result (0).matrix_value ();
    //std::cout << "resultMatrix is\n" << outMatrix << std::endl;
    
#endif //USE_OCTAVE 

    return 0;
}
double  InterP::interP2( std::vector<double> v1, std::vector<double> v2, std::vector<double> v3, double xi, double yi ){
    return 0;
}
void InterP::createSDB( ){
    octave_value_list functionArguments;
    const octave_value_list result = feval ("createSDB", functionArguments, 1);     
}
