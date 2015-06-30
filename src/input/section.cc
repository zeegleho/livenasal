
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "section.h"
#include "sectionParam.h"
#include "sectionParamType.h"
#include "../console/global.h"
#include "IDB.h"


Section::Section( std::string& name ){
    name_ = name;
    params_ = new section_params_list_t;	
}
void Section::addParam( SectionParam* param ){
    params_->insert( section_params_list_item_t( SectionParamType::getType(param->getName()), param )  )  ;	
}
SectionParam* Section::getParam( type_t param_type ){
    return (*params_)[param_type];
}
std::string& Section::getName(){
    return name_;
}
