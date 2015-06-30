
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include "nsIdent.h"
#include "nsIdentTable.h"    


NSIdentTable::NSIdentMap *NSIdentTable::table_ = new NSIdentTable::NSIdentMap; 
NSIdentTable::PageTable *NSIdentTable::pages_  = new NSIdentTable::PageTable ; 
int NSIdentTable::page_size_ = 100;
int NSIdentTable::current_pos_ = 100;
int NSIdentTable::current_page_ = 0;
int NSIdentTable::hit_ = 0;
int NSIdentTable::miss_= 0;
    
void NSIdentTable::init(){
    //table_ = new NSIdentMap; 
    //pages_  = new PageTable ; 
}

NSIdentTable::Page NSIdentTable::newPage( ){
    char * page = new char[page_size_];
    memset( page, 0, page_size_);
    return page; 
}
char*  NSIdentTable::nsMalloc( int length ){
    if( page_size_- current_pos_ < length ){
	//new page
	pages_->push_back( newPage() );
	current_pos_ = 0;
	current_page_= pages_->size()-1;
    }

    char* result = pages_->at( current_page_ )+current_pos_;
    current_pos_ = current_pos_+length+1;
    return result;
}

NSIdent*  NSIdentTable::createIdent( const char* str, void* vars, bool(*equalVariables)(void*, void*) ){
    if(  !table_ ){
	//table_ = new NSIdentMap; 
	//pages_  = new PageTable ; 
    }

    HashValue index = NSIdent::hashFunc_( str );
    NSIdentMap::iterator it = table_->find(index); 

    if( it != table_->end() ){
	NSIdentList *p = it->second;
	for( NSIdentList::iterator it = p->begin(); it!=p->end();it++) 
	{
	    if( std::strcmp( str, (*it)->getValue() )==0 && (*equalVariables)( vars, (*it)->getVariables() ) ){
		hit_ ++;
		return *it;
	    }
	}
    
	//maatch failed, insert new one

	int length = strlen(str);
	char* buffer = nsMalloc( length+1 );
	strcpy( buffer, str );
	buffer[length]='\0';
	NSIdent* ident = new NSIdent( index, buffer );
	p->push_back( ident );
    }
    miss_ ++;
    //maatch failed, new one
    {
	int length = strlen(str);
	char* buffer = nsMalloc( length+1 );
	strcpy( buffer, str );
	buffer[length]='\0';
	NSIdent* ident = new NSIdent( index, buffer );

	NSIdentList *p = new NSIdentList;
	p->push_back( ident );
	table_->insert( NSIdentMapPair( index, p ) );

	return ident;
    }
}
