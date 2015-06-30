
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef IDB_H
#define IDB_H
#include <vector>
#include <map>
#include "section.h"      
#include "sectionNasalCave.h" 
#include "sectionValue.h"
#include "sectionName.h"  
#include "sectionParam.h"
#include "../console/global.h"

typedef std::map< type_t, Section* > section_list_t;	
typedef std::pair<type_t, Section*>  section_list_item_t;	
typedef std::map< type_t, SectionParam* > section_params_list_t;	
typedef std::pair<type_t, SectionParam*>  section_params_list_item_t;	

class IDB{
public:
    IDB();
    void addSection( Section* section );
    Section* getSection( type_t section_type );
    void addParam( SectionParam* param );
    SectionParam* getParam( type_t param_type );
private:
    section_list_t *sections_;	
    section_params_list_t  *global_params_;	
};

#endif //IDB_H
