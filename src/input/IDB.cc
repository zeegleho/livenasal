
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <vector>
#include <map>
#include "IDB.h"
#include "section.h"
#include "sectionType.h"
#include "sectionParam.h"
#include "sectionParamType.h"
//#include "../console/global.h"

IDB::IDB(){
    sections_ = new section_list_t;	
    global_params_ = new section_params_list_t;	
}
void IDB::addSection( Section* section ){
    sections_->insert( section_list_item_t( SectionType::getType(section->getName().c_str()), section )  ) ;	

}
void IDB::addParam( SectionParam* param ){
    global_params_->insert( section_params_list_item_t( SectionParamType::getType(param->getName()), param )  )  ;	

}
Section* IDB::getSection( type_t section_type ){
    return (*sections_)[ section_type ];
}
SectionParam* IDB::getParam( type_t param_type ){
    return (*global_params_)[ param_type ];
}
