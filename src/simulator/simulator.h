
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */

#ifndef SIMULATOR_H 
#define SIMULATOR_H 
#include "SDBAccessor.h"
#include "simulatorEngine.h"
#include "SDBCreator.h"
#include "SDBAccessor.h"
#include "SDB.h"
#include "../input/IDBAccessor.h"
	
class Simulator
{
public:
	static void init( );
	static void createSDB( IDBAccessor* idb_accessor );
	static void simulation();
	
	static int getRangeX();
	static int getRangeY();
	static int getRangeZ();
private:
	static SDBCreator* sdb_creator_;
	static SDBAccessor* sdb_accessor_;
	static SimulatorEngine* simulator_engine_;
	
	static int input_range_x;
	static int input_range_y;
	static int input_range_z;
};
#endif //SIMULATOR_H 
