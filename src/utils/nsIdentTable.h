
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef NSIDENTTABLE_H
#define NSIDENTTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>
#include <map>

class NSIdentTable{
public:
    typedef char* Page;
    typedef std::vector< Page > PageTable;
    typedef std::vector<NSIdent*> NSIdentList;
    typedef std::map< HashValue , NSIdentList* > NSIdentMap;
    typedef std::pair< HashValue, NSIdentList* > NSIdentMapPair;

    static void init();
    static NSIdent* createIdent( const char*,void* vars, bool(*equalVariables)(void*, void*) = NSIdent::equalVariables );

    static Page newPage( );
    static char* nsMalloc( int length );

    static NSIdentMap *table_;
    static PageTable *pages_;
    static int page_size_;
    static int current_page_;
    static int current_pos_;
    
    static int hit_;
    static int miss_;

private:
    
    
};

#endif //NSIDENTTABLE_H
