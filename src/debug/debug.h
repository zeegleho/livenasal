
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef DEBUG_H
#define DEBUG_H
#include <fstream>
#include <vector>
#include <map>
#include <hash_map>
#include <string>
#include <set>
#include "../console/global.h"
#include "../input/IDBAccessor.h"
#include "../simulator/SDBAccessor.h"
#include "../utils/nsIdent.h"
#define DUMPFILELINE std::cout<<"------------zeegle--------"<<__FILE__<<" "<<__LINE__<<std::endl;
class Debug{
public:
    static void readDebugVariables();
    static void dumpDebugVariables();

    static bool DUMP_DEBUG;

    static int getDebugVariable( NSIdent* str ){
	//std::map< NSIdent* , int,  NSIdentLess >::iterator it;
	int it = debug_variables_[str];
	/*if(it!=debug_variables_.end()) {
	    return (*it).second;
	} else {
	    return -1;
	}*/
	return it;
    }
    
    static char* getDebugFileName(){
	return debug_filename_;
    }
    static void setDebugFileName ( char* debug_filename ){
	debug_filename_ = debug_filename ;
    }

    static void dumpIDB( IDBAccessor *idb_accessor );
    static void dumpSDB( SDBAccessor *sdb_accessor );

    static bool DUMP_CONSOLE;

    static bool DUMP_OPTIONS;

    static bool DUMP_IDB;

    static std::set<type_t> *dump_sections;
    static std::map< type_t, std::set<type_t> * > *dump_params;
    //static bool DUMP_SECTION;
    //static bool DUMP_SECTION_PARAM; 

    static bool DUMP_SDB;
    static bool DUMP_VDB;

private:
    static char* debug_filename_;
    static std::map< NSIdent*, int,  NSIdentLess > debug_variables_;

};

#endif //DEBUG_H
