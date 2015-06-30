
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include "sectionParam.h"
#include "iPosition.h"

class SectionParamShape:public SectionParam {
public:
    SectionParamShape( const char* name, const char* value );
    std::vector< IPosition *>* getShape();
    void setShape( std::vector< IPosition *>*  shape );
private:
    std::vector< IPosition *>*  shape_;
};
#endif //SHAPE_H
