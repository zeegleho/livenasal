
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include "optionDef.h"
#include "options.h"

OptionDef::OptionDef(
		     NSIdent* name, 
		     NSIdent* value_type, 
		     NSIdent* validate_value, 
		     NSIdent* default_value, 
		     NSIdent* description, 
		     int value_size,
		     int option_id){
    name_ = name; 
    description_= description; 
    value_type_  = Options::mapValueType(value_type) ;
    //std::vector<VALUETYPE> validate_value_;

    defautl_value_idx_ = -1;  
    //int option_value_idx_;
    int value_idx_= -1; 
    value_size_ =  value_size;
    option_idx_ = option_id; 

    //NSIdent* default_value, 
    if( strcmp(default_value->getValue(), "")!=0 )
	setValues( value_type_, value_size, default_value);

    Options::addOption( option_id, this );
    Options::addOptionIndex( name, option_id );
}

OptionDef::OptionDef(
		     NSIdent* name,
		     NSIdent* description,
		     NSIdent* value_type,
		     std::vector<VALUETYPE> validate_value,
		     int defautl_value_idx,
		     int value_idx,
		     int value_size,
		     int option_idx 
		    ){
    name  =             name; 
    description =       description;
    value_type_  =        Options::mapValueType(value_type);
    validate_value =    validate_value;
    defautl_value_idx = defautl_value_idx;
    value_idx =         value_idx; 
    value_size_ =  value_size ;
    option_idx =        option_idx ;     
    
    Options::addOption( option_idx, this );
}


OptionDef::OptionDef(
		     NSIdent* name,
		     NSIdent* description,
		     NSIdent* value_type,
		     NSIdent* validate_value,
		     int defautl_value_idx,
		     int value_idx,
		     int value_size,
		     int option_idx 
		    ){
    name  =             name; 
    description =       description;
    value_type_  =       Options::mapValueType(value_type) ;
    createValidateValue( validate_value );
    defautl_value_idx = defautl_value_idx;
    value_idx =         value_idx; 
    value_size_ =  value_size ;
    option_idx =        option_idx ;     
    
    Options::addOption( option_idx, this );
}
/*
OptionValue_t OptionDef::mapValueType( NSIdent* type ){
    if( Options::options_type_->size()==0 )
	Options::initOptionType( );
    std::cout<<"--------zeegle----"<<__FILE__<<":"<<__LINE__<<" "<<type->getValue()<<" "<<(*Options::options_type_)[type]<<std::endl;
    return (*Options::options_type_)[type];
}
*/
OptionValue_t OptionDef::getValueType(){
    return value_type_; 
}

int OptionDef::getValue(){
    return 8;
    //return validate_value_[ value_idx_];
}
void OptionDef::setValue( bool value, int index ){
}
void OptionDef::setValue( int value, int index ){
    if( validate_value_int_array_==0 )
	validate_value_int_array_ = new std::vector<int>;

    if( validate_value_int_array_->size()==index ){
	validate_value_int_array_->push_back(value);
    }else if( validate_value_int_array_->size()<index ){
	validate_value_int_array_->resize( index );
	validate_value_int_array_->push_back(value);
    }else if( validate_value_int_array_->size()>index ){
	validate_value_int_array_->at(index) = value;
    }
}
void OptionDef::setValue( double value, int index ){
}
void OptionDef::setValue( NSIdent* value , int index ) {
}

void OptionDef::setBoolArray( std::vector<bool>* ){ 
}
void OptionDef::setIntArray( std::vector<int>* ){
}
void OptionDef::setDoubleArray(std::vector<double>*  ){
}
void OptionDef::setStringArray(std::vector<NSIdent*>*){
}

void OptionDef::createValidateValue( NSIdent* validate_value ){
    //validate_value from validate_value
}
void OptionDef::setValueSize( int num ){
     value_size_ = num;
}
int OptionDef::getValueSize( ){
    return value_size_ ;
}
bool OptionDef::getBool(int index){}
int OptionDef::getInt(int index){
    if( validate_value_int_array_ != NULL){
    return validate_value_int_array_->at(index);
    }else{
	return -1;
    }
}
double OptionDef::getDouble(int index){}
NSIdent* OptionDef::getString(int index){}
std::vector<bool>* OptionDef::getBoolArray(){}
std::vector<int>* OptionDef::getIntArray(){}
std::vector<double>* OptionDef::getDoubleArray(){}
std::vector<NSIdent*>* OptionDef::getStringArray(){}
NSIdent* OptionDef::getFile(){}
void OptionDef::setFile( NSIdent* file ) {}

void OptionDef::setValueType(OptionValue_t type){
    value_type_ = type;
}

void OptionDef::setValues(NSIdent* values){
    setValues(value_type_, value_size_, values);
}
void OptionDef::setValues(OptionValue_t type, int value_size,  NSIdent* value){
    switch( type ){
    case( OptionValueType::type_string ):
    case( OptionValueType::type_stringarray):
	{
	    for( int n=1;n<=value_size;n++){
		setValue( value, n );
	    }
	    break;
	}
    case(  OptionValueType::type_boolarray ):
	{
	    break;
	}
    case(OptionValueType::type_int ):
    case(OptionValueType::type_intarray ):
	{
	    if( validate_value_int_array_==0 )
		validate_value_int_array_ = new std::vector<int>;
	    int n = 1;
	    std::string vs(  value->getValue() );
	    for(std::size_t found = vs.find(",");
		n<=value_size;
		found = vs.find(","), n++){
		std::string::size_type sz;
		int v = std::stoi( vs, &sz );
		setValue( v, n-1 );
	    }
	}
    case(OptionValueType::type_double):
    case(OptionValueType::type_doublearray ):
	{
	    std::string vs( value->getValue() );
	    int n = 1;
	    for(std::size_t found = vs.find(",");
		n<=value_size;
		found = vs.find(","), n++){
		std::string::size_type sz;
		double v = std::stod( vs, &sz );
		setValue( v, n-1 );
	    }
	    break;
	}
    default:
	{
	    setValue( value );
	}
    }

}
