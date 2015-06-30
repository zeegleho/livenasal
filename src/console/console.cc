
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
//#include <direct.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "console.h"
#include "simulationController.h"
#include "../utils/nsIdent.h"
#include "../messages/messageInterface.h"
#include "../algorithm/algorithmInterface.h"

int Console::editor_accuracy_=0;
int Console::view_accuracy_=0;
int Console::log_out_=0;          //std::cout only             
bool Console::performance_info_=true;
NSIdent* Console::log_file_name_ = NULL;
SimulationController* Console:: simulation_controller_ = NULL;
pid_t Console::pid_ = 0;

NSIdent * Console::work_path_ = NULL;
NSIdent * Console::netlist_name_ = NULL;
NSIdent * Console::temp_path_ = NULL;
NSIdent * Console::sdb_creation_m_file_ = NULL;

void Console::init(){
    NSIdent::init();
    setPid();

    char buffer[BUFSIZ];
    getcwd(buffer, sizeof(buffer));;
    work_path_ = NSIdent::create( buffer );
    netlist_name_ = NULL;
    std::string m_file( buffer );
    m_file.append( "/" );
    m_file.append( ".livenasalTemp" );
    temp_path_ = NSIdent::create(m_file.c_str());
    m_file.append( "/" );
    m_file.append( "createSDB.m" );
    sdb_creation_m_file_ = NSIdent::create( m_file.c_str() );

    if( access(temp_path_->getValue(), F_OK) == -1 ){
	if (mkdir(temp_path_->getValue(), 0777) != 0){
	    MessageInterface::getMsgInterface()->print( MSG_CannotCreateTempDir_0, temp_path_->getValue() );
	}
    }
}

void Console::DumpConsole(){
    MessageInterface::getMsgInterface()->printLog( "-------------zeegle dump console begin----------------+-" );
    MessageInterface::getMsgInterface()->printLog( pid_ );
    /*
     MessageInterface::getMsgInterface()->printLog( editor_accuracy_ );
     MessageInterface::getMsgInterface()->printLog( view_accuracy_ );

     MessageInterface::getMsgInterface()->printLog( performance_info_ );
    
    MessageInterface::getMsgInterface()->printLog( log_out_ ) ;                 //0: std::out only, 1: file only, 2: std::out and file
    MessageInterface::getMsgInterface()->printLog( log_file_name_->getValue() );
    */
    MessageInterface::getMsgInterface()->printLog( "-------------zeegle dump console end   ----------------" );
}

int Console::getEditorAccuracy(){
    return editor_accuracy_;
}
void Console::setEditorAccuracy( int acc ){
    editor_accuracy_ = acc ;
}

int Console::getViewAccuracy(){
    return view_accuracy_;

}
void Console::setViewAccuracy( int acc ){
    view_accuracy_ = acc;
}

bool Console::getPerformanceInfo(){
    return performance_info_;

}
void Console::setPerformanceInfo( bool p ){
    performance_info_ = p ;
}

int Console::getLogOut(){
    return log_out_;                 //0: std::out only, 1: file only, 2: std::out and file
}
void Console::setLogOut( int l ){
    log_out_ = l;                 //0: std::out only, 1: file only, 2: std::out and file
}
NSIdent* Console::getLogFile(){
    return log_file_name_;
}
void Console::setLogFile( NSIdent* l ){
    log_file_name_ = l;
}

pid_t Console::getPid(){
    return pid_;
}
void Console::setPid( ){
    pid_ = getpid();
}

NSIdent* Console::getWorkPath(){
    return  work_path_;
}
void Console::setWorkPath( NSIdent* p ){
    work_path_ = p;
}

NSIdent* Console::getFullSDBCreationMFile(){
    return sdb_creation_m_file_;
}
void Console::setFullSDBCreationMFile( NSIdent* p ){
    sdb_creation_m_file_ = p;
}

NSIdent* Console::getFullTempPath(){
    return temp_path_;
}
void Console::setFullTempPath( NSIdent* p ){
    temp_path_ = p;
}
void Console::quit( ){
    AlgorithmInterface::clearup();
}
