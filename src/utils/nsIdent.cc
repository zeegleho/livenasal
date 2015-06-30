
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

NSIdentHashFunc NSIdent::hashFunc_;


void NSIdent::init(){
    NSIdentTable::init();
}

NSIdent::NSIdent( HashValue hash, char* v ){
    value_ = (char*) malloc( strlen( v ) +1 );
    strcpy( value_, v );
    value_[strlen(v)]='\0';

    hash_ = hash;
}
NSIdent::NSIdent( HashValue hash, const char* v ){
    value_ = (char*) malloc( strlen( v ) +1 );
    strcpy( value_, v );
    value_[strlen(v)]='\0';

    hash_ = hash;
}

NSIdent::NSIdent( const char* v ){
    hash_ = hashFunc_( v );
    
    value_ = (char*) malloc( strlen( v ) +1 );
    strcpy( value_, v );
    value_[strlen(v)]='\0';
}

NSIdent::NSIdent( char* v ){
    NSIdentHashFunc h;
    hash_ = h(v);

    value_ = (char*) malloc( strlen( v ) +1 );
    strcpy( value_, v );
    value_[strlen(v)]='\0';
}
NSIdent* NSIdent::create( const char* value, Variables *vars ){
    //return NSIdentTable::createIdent( value, vars );
    return new NSIdent( value );
}
NSIdent* NSIdent::create( char* value, Variables *vars ){
    //return NSIdentTable::createIdent( value, vars );
    return new NSIdent( value );
}
const HashValue NSIdent::getHash() const{
    return hash_;
}

const char* NSIdent::getValue() const{
    return value_;
}

void NSIdent::setValue( char* v ){
    value_ = (char*) malloc( strlen( v ) +1 );
    strcpy( value_, v );
}
/*
bool NSIdent::operator==( const NSIdent& ns_ident ) const{
    return ( strcmp( value_, ns_ident.getValue() ) == 0 );
}
bool NSIdent::operator!=( const NSIdent& ns_ident ) const{
    return ( strcmp( value_, ns_ident.getValue() ) != 0 );
}
*/
