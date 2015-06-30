
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef INPUTFILEREADER_H 
#define INPUTFILEREADER_H 
#include <iostream>
#include <vector>
#include <string>

#include "IDBAccessor.h"
#include "sectionParam.h"
#include "sectionParamShape.h"
#include "../utils/nsIdent.h"

class InputFileReader{
public:
	InputFileReader( );
	void parserFile( char* filename );
	void inputFileRead( IDBAccessor* idb_accessor_, NSIdent* filename );
	SectionParam* parserParam( Section* section, std::vector< std::string >* item );
	void parserDataFile( SectionParamShape* param );

	void setDelim( std::string d );
private:

};

#endif //INPUTFILEREADER_H 
