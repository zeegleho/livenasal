
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include <cmath>
#include "simulator.h"
#include "../input/sectionParamType.h"
#include "../input/sectionParam.h"
#include "../input/sectionParamShape.h"
#include "../input/sectionType.h"
#include "../input/section.h"
#include "../input/iPosition.h"
#include "../console/options.h"
#include "SDBCreator.h"
#include "spaceParticle.h"
#include "spaceParticleType.h"
#include "simulatorGlobal.h"

int Simulator::input_range_x = std::pow(2,ACCURACY);   //should be caculate by input shape files, or be set by options
int Simulator::input_range_y = std::pow(2,ACCURACY);
int Simulator::input_range_z = std::pow(2,ACCURACY);

SDBCreator *Simulator::sdb_creator_=NULL;
SDBAccessor *Simulator::sdb_accessor_=NULL;
SimulatorEngine* Simulator::simulator_engine_=NULL;


void Simulator::init( ){
    int accuracy = Macors_accuracy->getInt();
    if( accuracy != ACCURACY ){
	input_range_x = std::pow(2,accuracy);   
	input_range_y = std::pow(2,accuracy);
	input_range_z = std::pow(2,accuracy);
    }

    Simulator::sdb_creator_ = new SDBCreator();
    sdb_accessor_ = new SDBAccessor();
}
void Simulator::createSDB( IDBAccessor* idb_accessor ){
    sdb_creator_->createSDB( sdb_accessor_, idb_accessor );
}
void Simulator::simulation(){

}
static bool print = false;
int Simulator::getRangeX(){
    if( !print ){
	print = true;
    }
    return input_range_x;
}
int Simulator::getRangeY(){
    return input_range_y;
}
int Simulator::getRangeZ(){
    return input_range_z;
}
