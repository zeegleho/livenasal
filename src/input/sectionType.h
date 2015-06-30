
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SECTIONTYPE_H
#define SECTIONTYPE_H
#include "../console/global.h"
//#include "section.h"

class SectionType{
public:
    static type_t getType( const char* name );
    static char* getName( type_t type );
    
    /*types*/
    static const type_t type_section_unknown = 0x00;
    static const type_t type_section_global = 0x01;
    static const type_t type_section_nasalcave = 0x02;
    static const type_t type_section_nerve  = 0x03;
    static const type_t type_section_vessel = 0x04;
    static const type_t type_section_body   = 0x05;
    static const type_t type_section_air    = 0x06;

};

#endif //SECTIONTYPE_H
