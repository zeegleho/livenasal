
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SECTIONPARAMTYPE_H
#define SECTIONPARAMTYPE_H
#include <string.h>

#include "../console/global.h"
//#include "sectionParam.h"

class SectionParamType{
public:
    static type_t getType( const char* name );
    static const char* getName( type_t type );
/*types*/
//unknown
//global 
static const type_t type_section_param_unknown = 0x0;

//nasalcave 
static const type_t type_section_param_shape = 0x1;
static const type_t type_section_param_temperature = 0x2;
static const type_t type_section_param_dust_sensitive = 0x3;

//nerve  
//static const type_t type_section_param_shape = 0x3;

//vessel 
//static const type_t type_section_param_shape = 0x4;

//body   
//static const type_t type_section_param_temperature = 0x5;

//air    
static const type_t type_section_param_dust = 0x6;
//static const type_t type_section_param_temperature = 0x7;
static const type_t type_section_param_pressure = 0x8;

};

#endif //SECTIONPARAMTYPE_H
