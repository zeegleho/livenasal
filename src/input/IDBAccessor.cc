
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "IDBAccessor.h"
#include "../input/sectionParamType.h"
#include "../input/sectionType.h"


IDBAccessor::IDBAccessor( ){
    IDB_ = new IDB( );
}
void IDBAccessor::addParam( SectionParam* param ){
    IDB_->addParam( param );
}

void IDBAccessor::addSection( Section* section ){
    IDB_->addSection( section );
}


SectionParam* IDBAccessor::getParam( type_t param_type ){
    return IDB_->getParam( param_type );
}
Section* IDBAccessor::getSection( type_t section_type ){
    return IDB_->getSection( section_type );
}
