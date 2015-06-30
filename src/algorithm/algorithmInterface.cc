
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <fstream>
#include "algorithmInterface.h"
#include "../console/console.h"
#include "interP.h"
#include "curveFitting.h"

bool AlgorithmInterface::inited_ = false;

//#define USE_OCTAVE 
void AlgorithmInterface::init(){
    const char * argvv [] = {"" /* interP */,  "--silent"};
    octave_main (2, (char **) argvv, true );
    inited_ =  true;

    octave_value_list functionArguments;
    //addpath(genpath("/home/mike/mfiles"))
    functionArguments(0) = Console::getFullTempPath()->getValue(); //inMatrix01;
    feval ("addpath", functionArguments, 1);
    feval ("savepath");     

}
void AlgorithmInterface::clearup(){
    //do_octave_atexit();
    inited_ =  false;
    clean_up_and_exit (0);
}
double AlgorithmInterface::interP1( std::vector<double> v1, std::vector<double> v2, double xi ){
    if( !inited_ ) init();
    return  InterP::interP1( v1,  v2, xi );
}
double AlgorithmInterface::interP2( std::vector<double> v1, std::vector<double> v2, std::vector<double> v3, double xi, double yi ){
    if( !inited_ ) init();
    return  InterP::interP2(v1, v2, v3, xi, yi  );
}
void AlgorithmInterface::createSDB( ){
    if( !inited_ ) init();
    InterP::createSDB( );
}

bool AlgorithmInterface::interP2s( std::vector<std::vector<spaceParticle_t>>& zi,
	       std::set<spaceParticle_t>&xv,
	       std::set<spaceParticle_t>&yv,
	       std::vector<std::vector<spaceParticle_t>>& zv,
	       spaceParticle_t x_max,spaceParticle_t x_min,
	       spaceParticle_t y_max,spaceParticle_t y_min
	       ){

    char M_COMMENT='%';
    std::ofstream m_file( Console::getFullSDBCreationMFile()->getValue() );

    m_file<<"function [resultMatrix]=createSDB()"<<std::endl;
    m_file<<M_COMMENT<< "xv size is: "<<xv.size()<<std::endl;
    //std::sort( xv.begin(),xv.end());
    m_file<< "xv = [";
    for( std::set<spaceParticle_t>::iterator it=xv.begin(); it!=xv.end();it++){
	m_file<<" "<<*it;
    }
    m_file<< " ];"<<std::endl;
    //std::sort( yv.begin(),yv.end());
    m_file<<M_COMMENT<< "yv size is: "<<yv.size()<<std::endl;
    m_file<< "yv = [";
    for( std::set<spaceParticle_t>::iterator it=yv.begin(); it!=yv.end();it++){
	m_file<<" "<<*it;
    }
    m_file<< " ];"<<std::endl;

    m_file<<M_COMMENT<< "zv size is: "<<zv.size()<<std::endl;
    m_file<< "zv = [";
    for( std::vector<std::vector<spaceParticle_t>>::iterator itz=zv.begin(); itz!=zv.end();itz++){
	std::vector<spaceParticle_t> zvs = *itz;
	for( std::vector<spaceParticle_t>::iterator itx=zvs.begin(); itx!=zvs.end();itx++){
	    m_file<<" "<<*(itx);
	}
	m_file<<std::endl;
    }
    /*for( std::vector<spaceParticle_t>::iterator it1=zv.begin(); it1!=zv.end();it1++){
	for( std::vector<spaceParticle_t>::iterator it=zv.begin(); it!=zv.end();it++){
	    m_file<<" "<<*it;
	}
	    m_file<<std::endl;
    }*/
    m_file<< " ];"<<std::endl;

    spaceParticle_t xi_range=x_max+1-x_min;
    spaceParticle_t yi_range=y_max+1-y_min;
    m_file<<M_COMMENT<< "xi range: "<< x_min<<"-"<<x_max<<" "<<xi_range<<std::endl;
    m_file<<M_COMMENT<< "yi range: "<< y_min<<"-"<<y_max<<" "<<yi_range<<std::endl;
    m_file<<M_COMMENT<< "xi and yi size is : "<<xi_range*yi_range<<std::endl;
    m_file<< "xi = [";
    for( spaceParticle_t i=x_min;i<x_max+1;i++){
	for( spaceParticle_t j=y_min;j<y_max+1;j++){
	    m_file<<" "<<i;
	}
    }
    m_file<< " ];"<<std::endl;
    m_file<< "yi = [";
    for( spaceParticle_t j=x_min;j<x_max+1;j++){
	for( spaceParticle_t i=y_min;i<y_max+1;i++){
	    m_file<<" "<<i;
	}
    }
    m_file<< " ];"<<std::endl;
    
    m_file<<"resultMatrix=interp2( xv,yv,zv, xi, yi );\nendfunction\n"<<std::endl;
}
