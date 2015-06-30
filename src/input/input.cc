
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>

#include "input.h"
#include "IDBAccessor.h"
#include "inputFileReader.h"
#include "inputEditor.h"
#include "../utils/nsIdent.h"

int Input::input_range_x = 256;   //should be caculate by input shape files, or be set by options
int Input::input_range_y = 256;
int Input::input_range_z = 256;

InputFileReader* Input::input_file_reader_ = NULL;
IDBAccessor* Input::idb_accessor_ = NULL;
InputEditor* Input::input_editor_ = NULL;

NSIdent* Input::input_file_path_=NULL;
NSIdent* Input::input_file_name_=NULL;
NSIdent* Input::input_file_base_name_=NULL;

void Input::init( char* file_name ){
	input_file_name_ = NSIdent::create( file_name );


	if( idb_accessor_== 0 )
		idb_accessor_ = new IDBAccessor( );

	if( input_file_reader_== 0 )
		input_file_reader_ = new InputFileReader( );

	if( input_editor_ == 0 )
		input_editor_ = new InputEditor() ;
}

void Input::inputFileRead( ){
	input_file_reader_->inputFileRead( idb_accessor_, input_file_name_ );
}

//void Input::inputEdition(){
//not impliment yet
//}

InputFileReader* Input::getInputFileReader(){
	return input_file_reader_ ;
}
IDBAccessor* Input::getIDBAccessor(){
	return idb_accessor_ ;
}
InputEditor* Input::getInputEditor(){
	return input_editor_;
}


NSIdent* Input::getInputFilePath(){
    return input_file_path_;
}
void Input::setInputFilePath( NSIdent* file_path ){
    input_file_path_ = file_path;
}

NSIdent* Input::getInputFileName(){
    return input_file_name_;
} 
void Input::setInputFileName( NSIdent* file_name ){
    input_file_name_ = file_name;
} 

NSIdent* Input::getInputFileBaseName(){
    return input_file_base_name_;

} 
void Input::setInputFileBaseName( NSIdent* file_base_name ){
    input_file_base_name_ = file_base_name;
} 
int Input::getRangeX(){
    return input_range_x;
}
int Input::getRangeY(){
    return input_range_y;
}
int Input::getRangeZ(){
    return input_range_z;
}
