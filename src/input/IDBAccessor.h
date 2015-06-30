
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef IDBACCESSOR_H
#define IDBACCESSOR_H
#include "sectionParam.h"
#include "section.h"
#include "IDB.h"
#include "../input/sectionParamType.h"
#include "../input/sectionType.h"

class IDBAccessor{
public:
	IDBAccessor( );
	void addParam( SectionParam* param );
	SectionParam* getParam( type_t param_type );
	void addSection( Section* section );
	Section* getSection( type_t section_type );
private:
	IDB *IDB_;
};

#endif //IDBACCESSOR_H
