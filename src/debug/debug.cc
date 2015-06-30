
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include <fstream>
#include  <string>
#include  <map>
#include  <set>
#include "debug.h"
#include "../input/section.h"
#include "../input/sectionParam.h"
#include "../input/sectionType.h"
#include "../input/sectionParamType.h"
#include "../input/iPosition.h"
#include "../input/sectionParamShape.h"
#include "../utils/utils.h"

char* Debug::debug_filename_ = NULL;
bool Debug::DUMP_DEBUG = false;
bool Debug::DUMP_IDB = false;
bool Debug::DUMP_CONSOLE = false;
bool Debug::DUMP_OPTIONS = false;
std::set<type_t> *Debug::dump_sections = NULL;
std::map< type_t, std::set<type_t> * > *Debug::dump_params = NULL;
// bool Debug::DUMP_SECTION = false;
// bool Debug::DUMP_SECTION_PARAM = false; 
bool Debug::DUMP_SDB = false;
bool Debug::DUMP_VDB = false;
std::map< NSIdent*, int,  NSIdentLess > Debug::debug_variables_;

void Debug::readDebugVariables( ){
    if( debug_filename_==NULL ) return;

    std::fstream file;
    file.open( debug_filename_, std::ifstream::in );		
    std::string line;	
    std::vector< std::string > items;
    while( getline(file,line) )  
    {
	items.clear();
	Utils::split( line, Utils::getDelim(), &items );

	std::vector< std::string >::iterator it=items.begin(); 
	//SectionType::getType();
	if( (*it).compare("DUMP_IDB")==0){
	    DUMP_IDB = true;
	}else if( (*it).compare("DUMP_SDB")==0){
	    DUMP_SDB = true;
	}else if( (*it).compare("DUMP_VDB")==0){
	    DUMP_VDB = true;
	}else if( (*it).compare("DUMP_CONSOLE")==0){
	    DUMP_CONSOLE = true;
	}else if( (*it).compare("DUMP_OPTIONS")==0){
	    DUMP_OPTIONS = true;
	}else if( (*it).compare("DUMP_SECTION")==0){
	    //static std::set<type_t> *dump_sections; ;
	    it++;
	    if( it == items.end() ) {
		std::cout<<"--------zeegle warning message------dump section but no section specified"<<std::endl;
		continue;
	    }
	    type_t section = SectionType::getType((*it).c_str());
	    it++;
	    if( it != items.end() ) {
		std::cout<<"--------zeegle warning message------dump section but params specified, use DUMP_SECTION_PARAM instead"<<"-"<<*it<<"-"<<std::endl;
	    }
	    if( dump_params == NULL) dump_sections=new std::set<type_t>;
	    dump_sections->insert( section );

	}else if( (*it).compare("DUMP_SECTION_PARAM")==0 ){
	    //static std::map< type_t, std::set<type_t> * > *dump_params;
	    if( dump_params == NULL) dump_params=new std::map< type_t, std::set<type_t> * >;
	    it++;
	    if( it == items.end() ) {
		std::cout<<"--------zeegle warning message------dump section params but no section specified"<<std::endl;
		continue;
	    }
	    type_t section = SectionType::getType((*it).c_str());
	    it++;
	    if( it == items.end() ) {
		std::cout<<"--------zeegle warning message------dump section params but no params specified"<<std::endl;
		continue;
	    }

	    std::map< type_t, std::set<type_t> * >::iterator it1 = dump_params->find( section );
	    std::set<type_t>* params;
	    if( it1 == dump_params->end() ) {
		params = new std::set<type_t>;
	    }else{
		if( (*it1).second!=NULL ){
		    params = (*it1).second;
		}else{
		    params = new std::set<type_t>;
		}
		dump_params->erase( it1 );
	    }
	    for( ; it!=items.end();it++){
		params->insert( SectionParamType::getType( (*it).c_str() ) );
	    }

	    dump_params->insert( std::pair<type_t, std::set<type_t>*>(section, params) );
	}else{
	    int value = 0;
	    if( (*it).length()==0 ) continue;
	    if(items.size() >=2){
		it++;
		std::string::size_type sz;   // alias of size_t
		value = std::stoi (*it,&sz);
	    }
	    debug_variables_.insert(  std::pair<NSIdent*, int>( NSIdent::create((*it).c_str()), value ) );
	}

    }
}
void Debug::dumpDebugVariables( ){
    std::cout<<"-------------zeegle dump debug info begin--------------"<<std::endl;
    if( debug_filename_ == NULL ){
	std::cout<<" no debug variables specified."<<std::endl;
	return;
    }

    std::cout<<"Debug variable file: \t"<<debug_filename_<<std::endl;
    std::cout<<"DUMP_IDB: \t\t"<<DUMP_IDB<<std::endl;
    std::cout<<"DUMP_SDB: \t\t"<<DUMP_SDB<<std::endl;
    std::cout<<"DUMP_VDB: \t\t"<<DUMP_VDB<<std::endl;
    std::cout<<"DUMP_CONSOLE: \t\t"<<DUMP_CONSOLE<<std::endl;
    std::cout<<"DUMP_OPTIONS: \t\t"<<DUMP_OPTIONS<<std::endl;
 
    //static std::set<type_t> *dump_sections;
    if( dump_sections && dump_sections->size()!=0 ){
	std::cout<<"DUMP_SECTION \t\t";
	for( std::set<type_t>::iterator it=dump_sections->begin(); it!= dump_sections->end(); it++){
	    std::cout<<SectionType::getName(*it);
	}
	std::cout<<std::endl;
    }

    //static std::map< type_t, std::set<type_t> * > *dump_params;
    if( dump_params && dump_params->size()!=0 ){
	for( std::map< type_t, std::set<type_t> * >::iterator it=dump_params->begin();
	     it!=dump_params->end(); it++) {
	    std::cout<<"DUMP_SECTION_PARAM \t"<<SectionType::getName( (*it).first ) <<" ";
	    std::set<type_t> *params=(*it).second;
	    if( params!=NULL ){
		for( std::set<type_t>::iterator it1=params->begin(); it1!= params->end(); it1++){
		    std::cout<<" "<<SectionParamType::getName(*it1);
		}
	    }
	    std::cout<<std::endl;
	}
    }
    //static bool DUMP_SECTION;
    //static bool DUMP_SECTION_PARAM; 

    std::cout<<"-------------zeegle dump debug info end--------------"<<std::endl;

}
void Debug::dumpIDB( IDBAccessor *idb_accessor ){
    Section* s = idb_accessor->getSection( SectionType::type_section_nasalcave );
    SectionParam* p = s->getParam( SectionParamType::type_section_param_shape );
    std::vector< IPosition *>* poss = ( (SectionParamShape*)(p) )->getShape();
    IPosition *pos = *(poss->begin()); 
    std::cout<<"-----------zeegle---------- IDB first pos is "<<pos->x()<<" "<<pos->y()<<" "<<pos->z()<<std::endl;
}
void Debug::dumpSDB( SDBAccessor *sdb_accessor ){
    int n = sdb_accessor->getSpaceParticlesNum();
    std::cout<<"-----------zeegle---------- SDB space particle num is "<<n<<std::endl;
}
