
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef INPUT_H 
#define INPUT_H
#include "IDBAccessor.h"
#include "inputFileReader.h"
#include "inputEditor.h"
#include "../utils/nsIdent.h"

class Input{
public:
	static void init( char* file_name_ );
	static void inputFileRead( );
	static void inputEdition();  //not impliment yet

	static InputFileReader* getInputFileReader();
	static IDBAccessor* getIDBAccessor();
	static InputEditor* getInputEditor();

	static NSIdent* getInputFilePath();
	static void setInputFilePath( NSIdent* file_path );

	static NSIdent* getInputFileName(); 
	static void setInputFileName( NSIdent* file_name ); 

	static NSIdent* getInputFileBaseName(); 
	static void setInputFileBaseName( NSIdent* file_base_name ); 

	static int getRangeX();
	static int getRangeY();
	static int getRangeZ();
private:
	static InputFileReader* input_file_reader_;
	static IDBAccessor* idb_accessor_;
	static InputEditor* input_editor_;

	static NSIdent* input_file_path_;
	static NSIdent* input_file_name_;
	static NSIdent* input_file_base_name_;

	static int input_range_x;
	static int input_range_y;
	static int input_range_z;
};

#endif //INPUT_H
