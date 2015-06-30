
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <math.h> 
#include <stdlib.h>

#include "inputFileReader.h"
#include "section.h"
#include "sectionParam.h"
#include "sectionParamShape.h"
#include "iPosition.h"
#include "../utils/utils.h"

using namespace std;


InputFileReader::InputFileReader( ){
}

void InputFileReader::inputFileRead( IDBAccessor* idb_accessor, NSIdent* filename ){
	bool is_top = true; 

	fstream file;
	file.open( filename->getValue(), std::ifstream::in );		

	Section* section = NULL;
	string line;	
	std::vector< std::string > items;
	string first_item("");
	
	while( getline(file,line) )  {
	    items.clear();
	    Utils::split( line, Utils::getDelim(), &items );

	    if( !items.empty() ){
		first_item = *(items.begin()++ );
	    }else{
		continue;
	    }

	    if ( first_item.compare( "section" ) == 0 ){
		if( items.size() < 2){
		    std::cout<<"---------zeegle message error----------"<<__FILE__<<":"<<__LINE__<<" "<<std::endl;  
		    continue;
		}
		//std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<line<<std::endl;  
		string section_name = *( ++items.begin() );
		section = new Section( section_name );
		is_top = false;

		//std::size_t found = line.find( "nasalcave" ) ; 
	    }else if ( first_item.compare( "ends" ) == 0 ){
		//std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<line<<std::endl;  
		idb_accessor->addSection( section );
		section = NULL;
		is_top = true;
	    }else{
		if( !is_top ) {
		    //std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<section->getName().c_str()<<" "<<line<<std::endl;  
		}else{
		    //std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<line<<std::endl;  
		}
		
		SectionParam* param = parserParam( section, &items );
		if( is_top ){
		    idb_accessor->addParam( param );
		}else{
		    section->addParam( param );
		}
	    }
	}

	file.close();
}

SectionParam* InputFileReader::parserParam( Section* section, std::vector< std::string > *item ){
    const char* name = (*(item->begin())).c_str();
    const char* value = (*(item->begin()+2)).c_str();

    //std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<name<<std::endl;  
    SectionParam* param;
    if( strcmp( name, "shape")==0 ){
	param = new SectionParamShape( name, value );
	
	parserDataFile( ( SectionParamShape*) param );

	//if( strcmp(section->getName().c_str(), "nasalcave")==0 ){
	//    std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" It is nasalcave"<<std::endl;  
	//}
    }else{
	param = new SectionParam( name, value );
    }
    return ( param ); 
}

void InputFileReader::parserDataFile( SectionParamShape* param ){

    fstream file;
    //std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<param->getValue()<<std::endl;  
    file.open( param->getValue(), std::ifstream::in );
    string line;	
    std::vector< std::string > items;
    std::vector< IPosition *>*  positions = new std::vector< IPosition* >; 
    while( getline(file,line) ){
	items.clear();
	Utils::split( line, Utils::getDelim(), &items );
	//IPosition *p = new IPosition( atof( (*(items.begin())).c_str() ), atof( (*(items.begin()+1)).c_str() ), atof( (*(items.begin()+2)).c_str() ));
	//std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<(*(items.begin()))<<" "<<(*(items.begin()+1))<<" "<<(*(items.begin()+2))<<" "<<std::endl;  
	//std::cout<<"---------zeegle----------"<<strtod( (*(items.begin())).c_str(), NULL)<<" "<<strtod( (*(items.begin()+1)).c_str(), NULL )<<" "<<strtod( (*(items.begin()+2)).c_str(), NULL )<<std::endl;
	IPosition *p = new IPosition( strtod( (*(items.begin())).c_str(), NULL), strtod( (*(items.begin()+1)).c_str(), NULL ), strtod( (*(items.begin()+2)).c_str(), NULL ));
	positions->push_back( p );
	param->setShape( positions );
	//std::cout<<"---------zeegle----------"<<__FILE__<<":"<<__LINE__<<" "<<p->x()<<" "<<p->y()<<" "<<p->z()<<" "<<std::endl;  
    }
}

