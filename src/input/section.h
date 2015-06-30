
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SECTION_H
#define SECTION_H
#include <string>
#include <map>
#include "sectionParam.h"
#include "../console/global.h"

class Section{
public:
    Section( std::string& name );
    void addParam( SectionParam* param );
    SectionParam* getParam( type_t param_type );

    std::string& getName();

private:
    std::string name_;
    std::map< type_t, SectionParam* > *params_;	
};

#endif //SECTION_H
