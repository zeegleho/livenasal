
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cfloat>
#include <cassert>
#include<sys/types.h>

#include "SDBCreator.h"
#include "SDBAccessor.h"
#include "../console/console.h"
#include "../input/input.h"
#include "../input/IDBAccessor.h"
#include "../input/section.h"
#include "../input/sectionParam.h"
#include "../input/sectionType.h"
#include "../input/sectionParamType.h"
#include "../input/iPosition.h"
#include "../input/sectionParamShape.h"
#include "../utils/utils.h"
#include "../utils/multiKeyMap.h"
#include "../debug/debug.h"

#include "../algorithm/algorithmInterface.h"
#include "createSpaceParticles.h"
#include "spaceParticle.h"
#include "simulator.h"

#define MAPUNIT_INTERP
#define MAPUNIT_CURVEFITTING

SDBCreator::SDBCreator(){
}
    
void SDBCreator::createSDB(SDBAccessor* sdb_accessor, IDBAccessor* idb_accessor ){

    Section* nasalcave = idb_accessor->getSection( SectionType::type_section_nasalcave );
    SectionParam* nasalcave_shape = nasalcave->getParam(  SectionParamType::type_section_param_shape );
    std::vector< IPosition *>* poss = ( (SectionParamShape*)(nasalcave_shape) )->getShape();

#ifdef MAPUNIT_INTERP
    std::map<key, std::set<spaceParticle_t>* > nasal_cave;
    std::map<key, unsigned int > mutli_z;
    std::set<spaceParticle_t> xv;
    std::set<spaceParticle_t> yv;
    std::vector< std::vector<spaceParticle_t> > zv;
    spaceParticle_t x_min=INT_MAX, x_max=0;
    spaceParticle_t y_min=INT_MAX, y_max=0;
    spaceParticle_t z_min=INT_MAX, z_max=0;
    for( std::vector< IPosition *>::iterator it = poss->begin(); it!=poss->end(); it++ ){
	IPosition *pos = *(it); 
	std::map<key, std::set<spaceParticle_t>* >::iterator ns_cave_it = nasal_cave.find( key( mapUnitX(pos->x()), mapUnitX(pos->x()) ) );
	if( ns_cave_it == nasal_cave.end() ){
	    std::set<spaceParticle_t>* zv_temp = new std::set<spaceParticle_t>;
	    zv_temp->insert( mapUnitX(pos->z()) );
	    nasal_cave.insert( make_pair(key(mapUnitX(pos->x()), mapUnitY(pos->y())), zv_temp ) );
	}else{
	    std::set<spaceParticle_t>* zv_temp = (*ns_cave_it).second;
	    zv_temp->insert( mapUnitZ(pos->z()) );
	}
	x_min = std::min(x_min, mapUnitX(pos->x()));
	x_max = std::max(x_max, mapUnitX(pos->x()));
	y_min = std::min(y_min, mapUnitY(pos->y()));
	y_max = std::max(y_max, mapUnitY(pos->y()));
	//z_min = std::min(z_min, mapUnitX(pos->z()));
	//z_max = std::max(z_max, mapUnitX(pos->z()));
	xv.insert( mapUnitX(pos->x()) );
	yv.insert( mapUnitY(pos->y()) );
    }

    zv.resize( yv.size() );
    int i=0;
    for( std::set<spaceParticle_t>::iterator ity=yv.begin(); i<yv.size()&&ity!=yv.end();ity++,i++){
	std::vector<spaceParticle_t> zvs = zv.at(i);
	//zvs.resize( xv.size() );
	for( std::set<spaceParticle_t>::iterator itx=xv.begin(); itx!=xv.end();itx++){
	    std::map<key, std::set<spaceParticle_t>* >::iterator p =  nasal_cave.find( key( *itx, *ity ) );
	    if( p==nasal_cave.end() ){
	        zvs.push_back( (spaceParticle_t)(LONG_MAX));	
	    }else{
		zvs.push_back( *((*p).second->begin()) );
	    }
	}
    }

    std::vector< std::vector<spaceParticle_t> > zi;
    AlgorithmInterface::interP2s( zi, xv, yv, zv, x_max, x_min, y_max, y_min );
    
    /*
    FILE *m_file;
    m_file = fopen( Console::getFullSDBCreationMFile()->getValue(), "w");
    if( m_file!=NULL){
	std::cout<<"----------zeegle------"<<Console::getFullSDBCreationMFile()->getValue()<<std::endl; 
    }
    fclose( m_file );
    */

/*
    for( std::vector< IPosition *>::iterator it = poss->begin(); it!=poss->end(); it++ ){
	IPosition *pos = *(it); 
	xv.push_back( mapUnitX(pos->x()) );
	x_min = std::min(x_min, pos->x());
	x_max = std::max(x_max, pos->x());
    }
    for( unsigned int x=x_min; x<x_max; x++){   //Input::getRangeX()
	zv.clear();
	yv.clear();
	for( std::vector< IPosition *>::iterator it = poss->begin(); it!=poss->end(); it++ ){
	    IPosition *pos = *(it); 
	    if( fabs( pos->x()-x )< 1 ){  //x is double, so all the num from 0.000 to 0.99999 are solve as 0 
		yv.push_back( mapUnitY(pos->y()) );
		y_min = std::min(y_min, pos->y());
		y_max = std::max(y_max, pos->y());
		zv.push_back( mapUnitY(pos->z()) );
		z_min = std::min(z_min, pos->z());
		z_max = std::max(z_max, pos->z());
	    }
	}
	for( unsigned int y=y_min; y<y_max; y++){     //Input::getRangeY()
	    double z = AlgorithmInterface::interP1( yv, zv, y );
	    yv.push_back( y );
	    zv.push_back( z );
	    addSpaceParticle(  sdb_accessor, x, y, z );
	}
	for( unsigned int z=z_min; z<z_max; z++){  //Input::getRangeZ() 
	    double y = AlgorithmInterface::interP1( zv, yv, z );
	    yv.push_back( y );
	    zv.push_back( z );
	    addSpaceParticle( sdb_accessor, x, y, z );
	}

	assert( yv.size()==zv.size() );
	
    }
    */
#else 
    //process without mapUnit
       for( std::vector< IPosition *>::iterator it = poss->begin(); it!=poss->end(); it++ ){
	   IPosition *pos = *(it); 
	   addSpaceParticle( sdb_accessor, pos->x(),  pos->y(),  pos->z() );
       }
#endif

    if( Debug::getDebugVariable( NSIdent::create("DUMP_SPACEPARTICLESNUM")) == 1 )
	//std::cout<<"----------zeegle------- space particles number is "<<sdb_accessor->getSpaceParticlesNum()<<std::endl;
	MessageInterface::getMsgInterface()->print( MSG_DUMP_SPACEPARTICLESNUM_0, sdb_accessor->getSpaceParticlesNum() );

}

spaceParticle_t SDBCreator::getKey( spaceParticle_t x, spaceParticle_t y, spaceParticle_t z){
    return  ((x<<ACCURACY)<<ACCURACY) + (y<<ACCURACY) + z;
}
spaceParticle_t SDBCreator::mapUnitX( double i ){
    return mapUnit( i, Simulator::getRangeX(), Input::getRangeX() );
}
spaceParticle_t SDBCreator::mapUnitY( double i ){
    return mapUnit( i, Simulator::getRangeY(), Input::getRangeY() );
}
spaceParticle_t SDBCreator::mapUnitZ( double i ){
    return mapUnit( i, Simulator::getRangeZ(), Input::getRangeZ() );
}
spaceParticle_t SDBCreator::mapUnit( double i, unsigned int dest_range, unsigned int src_range ){
    return ( i * ( dest_range/src_range ) );
}

double SDBCreator::curveFitting( ){
    return 0;
}

SpaceParticle * SDBCreator::addSpaceParticle( SDBAccessor* sdb_accessor, double x, double y, double z ){
       spaceParticleKey_t key = getKey( mapUnitX(x),  mapUnitY(y),  mapUnitZ(z) );
       SpaceParticle* particle = new SpaceParticle();
       sdb_accessor->addSpaceParticle( key, particle );
       return particle;
}
