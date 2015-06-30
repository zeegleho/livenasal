
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "sectionParam.h"
#include "sectionParamShape.h"
#include "iPosition.h"

SectionParamShape::SectionParamShape( const char* name, const char* value )
:SectionParam( name, value )
{
}
std::vector< IPosition *>* SectionParamShape::getShape( ){
    return shape_;
}
void SectionParamShape::setShape( std::vector< IPosition *>*  shape ){
    shape_ = shape;
}
