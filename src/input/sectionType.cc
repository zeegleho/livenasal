
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <string.h>
#include "sectionType.h"
//#include "section.h"
//#include "../console/global.h"

type_t SectionType::getType( const char* name ){
    if( strcmp(name, "nasalcave")==0 ){
	return type_section_nasalcave; 
    }else{
	return type_section_unknown;
    }
}


char* SectionType::getName( type_t type ){
    if( type == type_section_nasalcave ) {
	return "nasalcave";
    }else{
	return "unknown";
    }

}
