
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef OPTIONDEF_H
#define OPTIONDEF_H
#include <iostream>
#include <vector>
#include "../utils/nsIdent.h"

#define VALUETYPE int
#define OPTIONSNAME num
typedef unsigned short OptionValue_t;

class OptionValueType{
public:
    enum Vlue_e{
	type_bool, 
	type_int, 
	type_double, 
	type_string, 
	type_boolarray, 
	type_intarray, 
	type_doublearray, 
	type_stringarray, 
	type_file,
	type_unknow,
    };
};

class OptionDef{
public:
    OptionDef(
	      NSIdent* name,
	      NSIdent* description,
	      NSIdent* value_type,
	      std::vector<VALUETYPE> validate_value,
	      int defautl_value_idx,
	      int value_idx,
	      int value_size,
	      int option_idx 
	     );
    OptionDef(
	      NSIdent* name,
	      NSIdent* description,
	      NSIdent* value_type,
	      NSIdent* validate_value,
	      int defautl_value_idx,
	      int value_idx,
	      int value_size,
	      int option_idx 
	     );
    OptionDef(
	      NSIdent* name, 
	      NSIdent* value_type, 
	      NSIdent* validate_value, 
	      NSIdent* default_value, 
	      NSIdent* description, 
	      int value_size,
	      int option_id);


    NSIdent* getName( ){
	return name_;
    }

    int getValue();   //for debug
    std::vector<bool>* getBoolArray();
    std::vector<int>* getIntArray();
    std::vector<double>* getDoubleArray();
    std::vector<NSIdent*>* getStringArray();
    bool getBool( int index=0 );
    int getInt( int index=0 );
    double getDouble( int index=0 );
    NSIdent* getString( int index=0 );
    //for value file
    NSIdent* getFile();
   
    OptionValue_t getValueType();
    void setValueType(OptionValue_t type);

/*    void setValue( bool );
    void setValue( int );
    void setValue( double );
    void setValue( NSIdent* ) ;
    */
    void setValues(OptionValue_t type, int value_size, NSIdent* value);
    void setValues(NSIdent* value);
    void setBoolArray( std::vector<bool>* );
    void setIntArray( std::vector<int>* );
    void setDoubleArray(std::vector<double>*  );
    void setStringArray(std::vector<NSIdent*>*);
    void setValue( bool, int index=0);
    void setValue( int, int index=0);
    void setValue( double, int index=0);
    void setValue( NSIdent*, int index=0 ) ;
    void setFile( NSIdent* file ) ;

    void createValidateValue( NSIdent* validate_value );
    void setValueSize( int size );
    int getValueSize( );

    //OptionValue_t mapValueType( NSIdent* type );
private:
    NSIdent* name_; 
    NSIdent* description_; 
    OptionValue_t value_type_; 
    std::vector<int> *validate_value_int_array_;
    std::vector<double> *validate_value_double_array_;
    std::vector<NSIdent*> *validate_value_string_array_;
    int defautl_value_idx_; 
    int value_size_; 
    
    std::vector<int> *value_idx_; 

    int option_idx_; 
};

#endif //OPTIONDEF_H
