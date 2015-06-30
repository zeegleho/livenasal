
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef NSIDENT_H
#define NSIDENT_H
#include <cstring>
#include <iostream>

typedef size_t HashValue;
struct NSIdentHashFunc;

class NSIdent{
public:
    class Variables{
    public:
	Variables(){
	}
	inline bool operator==( const Variables& vars ) const{
	    return (strcmp(var1_, vars.var1_)==0);
	}
	char* var1_;
    };

    static void init();
    static NSIdent* create( char* value, Variables *vars=NULL );
    static NSIdent* create( const char* value, Variables *vars=NULL );
    const char* getValue() const;
    void setValue( char* v );
    inline bool operator==( const NSIdent& ns_ident ) const{
	return ( strcmp( value_, ns_ident.getValue() ) == 0 );
    }
    inline bool operator!=( const NSIdent& ns_ident ) const{
	return ( strcmp( value_, ns_ident.getValue() ) != 0 );
    }
    const HashValue getHash() const;

    NSIdent( char* value );
    NSIdent( const char* value );
    
    NSIdent( HashValue hash, char* value );
    NSIdent( HashValue hash, const char* value );
    
    static NSIdentHashFunc hashFunc_;

    static bool equalVariables(void *variables1, void *variables2 ){
	if( variables1==NULL || variables2==NULL)
	    return false;
	if( variables1==NULL && variables2==NULL)
	    return true;
	Variables* v1 =  (Variables*) variables1 ;
	Variables* v2 =  (Variables*) variables2 ;
	return (v1->var1_)==(v2->var1_);
    }
   Variables* getVariables(){
	return vars_;
    }
private:
    char* value_;
   HashValue hash_;

    Variables *vars_;
};

static HashValue i = 0;
struct NSIdentHashFunc{
    inline HashValue operator()( NSIdent* id ) const {
	std::hash<std::string> hashFunc;
	std::string temp(id->getValue());
	HashValue hash_ = hashFunc( temp );
	return hash_;
    }
    inline HashValue operator()( const char* id ) const {
	//std::hash<std::string> hashFunc;
	//std::string temp(id);
	//HashValue hash = hashFunc( temp );
	HashValue hash = i++;
	return hash;
    }

};

struct NSIdentLess{
    bool operator()( const NSIdent* id1, const NSIdent* id2 ) const {
	return id1->getHash()<id2->getHash() ;
    }
};

struct NSIdentEqual{
    bool operator()( const NSIdent* id1, const NSIdent* id2 ) const {
	//return id1 == id2 ;
	return (strcmp(id1->getValue(), id2->getValue())==0) ;
    }
};
#endif //NSIDENT_H
