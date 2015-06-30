
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "sectionParam.h"

SectionParam::SectionParam( const char* name, const char* value ){
    name_ = name;
    value_ = value;
}

const char* SectionParam::getName(){
    return name_;
}
const char* SectionParam::getValue(){
    return value_;
}
