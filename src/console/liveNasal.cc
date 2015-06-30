
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include <string>
#include <unistd.h>

//from console
#include "liveNasal.h"
#include "console.h"
#include "performance.h"
#include "options.h"
#include "optionDef.h"
#include "../utils/utils.h"
#include "../debug/debug.h"
//from input
#include "../input/input.h"
#include "../input/IDBAccessor.h"
//from simulator
#include "../simulator/simulator.h"
#include "../simulator/SDBAccessor.h"
//from output
#include "../output/output.h"
#include "../output/VDBAccessor.h"
//for utils
//from message
#include "../messages/messageInterface.h"

#define DEBUG

void LiveNasal::run( int argc, char* argv[] ){

    MessageInterface::initProcInfo();
    if( argc<2 ){
	/*MsgInterface *msg = MsgInterface::getMsgInterface();
	  msg->print( filename, line, MSG_noEnoughArg, args );
	 */
	MessageInterface::getMsgInterface()->print( MSG_NoEnoughArg_0 );
	//Utils::getMsgInterface()->print( "-------------zeegle message %s----------------- no enough args! specify at least %d!", "error", 1);
	return;
    }
    char* filename = NULL;

    for( int i=1; i<argc; i++ ){
	char head = argv[i][0];
	if( head=='-' || head=='+' || head=='=' ){
	    if( strcmp( argv[i], "-D")==0 ){
		Debug::DUMP_DEBUG = true;
		Debug::setDebugFileName ( argv[++i] );
	    }else if( strcmp( argv[i], "-d")==0 ){
		Debug::setDebugFileName ( argv[++i] );
	    }else if( strcmp( argv[i], "-h")==0 ){
	    }else if( strcmp( argv[i], "--help")==0 ){
		help();
		exit(0);
	    }else{
		NSIdent* opt_name = NSIdent::create( argv[i]+1 );
		OptionDef* opt = Options::getOption( opt_name );
		if( opt == NULL) {
		    MessageInterface::getMsgInterface()->print( MSG_UnknowArg_0,argv[i]);
		}else{
		    int value_size = opt->getValueSize();
		    if( value_size==0 ){
			//OptionValueType::type_bool, 
			opt->setValue( true );
		    }else if( strcmp(argv[i+1], "file")==0){
			//OptionValueType::type_file,
		    }else{
			opt->setValues( NSIdent::create(argv[++i]) );
		    }
		}
	    }

	}else{
	    filename = argv[i];
	}

    }
/*
    char* filename = argv[1];
    int ch=-1;
    while((ch = getopt(argc-1, argv+1, "a:bcd:D:e")) != -1)
    {
	switch(ch)
	{
	case 'a':
	    MessageInterface::getMsgInterface()->print("option a:%s\n",optarg);  break;
	case 'b':
	    MessageInterface::getMsgInterface()->print("option b :b\n");  break;
	case 'd':
	    Debug::setDebugFileName ( optarg );
	    break;
	case 'D':
	    Debug::DUMP_DEBUG = true;
	    Debug::setDebugFileName ( optarg );
	    break;
	default:
	    MessageInterface::getMsgInterface()->print("------zeegle message error --------unkown option :-%c",ch);
	}
    }
    */

//#ifdef  DEBUG
//#endif //DEBUG

#ifdef  DEBUG
    Debug::readDebugVariables( );
    if( Debug::DUMP_DEBUG )
	Debug::dumpDebugVariables( );
#endif //DEBUG
    
    Console::init();

    Input::init( filename );
    Input::inputFileRead( );
    //Input::inputEdition();  //not impliment yet

#ifdef  DEBUG
    if( Debug::DUMP_CONSOLE )
	Console::DumpConsole();
    if( Debug::DUMP_IDB )
	Debug::dumpIDB( Input::getIDBAccessor() );
#endif //DEBUG

    Simulator::init( );
    Simulator::createSDB( Input::getIDBAccessor() );
    Simulator::simulation();

    Output::init();
    Output::createVDB();
    Output::runLocalView();
    //Output::runWebView();    //not impliment yet

    MessageInterface::showProcInfo( Console::getPid() );
    Console::quit( );
}
void LiveNasal::help(){
 MessageInterface::getMsgInterface()->print( "\
[usage:]\n\ 
livenasal [=/-/--/+options [values]] netlist.ns\n\
\n\
[NOTICE!] \n\
\n\
[description:]\n\
This software do the following tasks:\n\
\t1.\n\
\t2.\n\
\t3.\n\
Something else:\n\
\t1.\n\ 
\t2.\n\ 
\t3.\n\
you can run the following cmd to get detail info about netlist:\n\
\tlivenasal --help netlist\n\
\n\
[options:] \n\
(this should  got form options.cc)\n\
-d\t\tspecife the debug variable files.\n\
\t\tDon't dump all the debug variables. \n\
\t\tfor detail info of debug variables, you can run livenasal --help debug. \n\
-D\t\tspecife the debug variable files.\n\
\t\tAnd dump all the debug variables.\n\
\t\tfor detail info of debug variables, you can run livenasal --help debug. \n\
--help option\tShow detail help info.\n\
--help\t\tShow detail help info.\n\
-h\t\tShow simplified help info.\n\
"
    );

}
