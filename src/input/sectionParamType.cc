
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */

#include "sectionParamType.h"
//#include "sectionParam.h"
//#include "../console/global.h"
type_t SectionParamType::getType(const char* name ){
    if( strcmp(name, "shape")==0 ){
	return type_section_param_shape; 
    }else{
	return type_section_param_unknown;  
    }
}
const char* SectionParamType::getName( type_t type ){
    if( type == type_section_param_shape) {
	return "shape";
    }else{
	return "param_unknown";  
    }
}
