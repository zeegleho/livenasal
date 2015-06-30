
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef COSOLE_H
#define COSOLE_H
#include <unistd.h>

#include "simulationController.h"
#include "../utils/nsIdent.h"

//get/set simulation variables 

class Console{
public:
    static void init();
    static void DumpConsole();

    static int getEditorAccuracy();
    static void setEditorAccuracy( int acc );

    static int getViewAccuracy();
    static void setViewAccuracy( int acc );

    static bool getPerformanceInfo();
    static void setPerformanceInfo( bool p );

    static int getLogOut();
    static void setLogOut( int l );
    static NSIdent* getLogFile();
    static void setLogFile( NSIdent* l );

    static pid_t getPid();
    //static void setPid( pid_t p );
    static void setPid( );

    static NSIdent* getWorkPath();
    static void setWorkPath( NSIdent* p );
    
    static NSIdent* getFullSDBCreationMFile();
    static void setFullSDBCreationMFile( NSIdent* p );
    
    static NSIdent* getFullTempPath();
    static void setFullTempPath( NSIdent* p );
    
    static void quit( );
private:    

    static int editor_accuracy_;
    static int view_accuracy_;

    static bool performance_info_;
    
    static int log_out_;                 //0: std::out only, 1: file only, 2: std::out and file
    static NSIdent* log_file_name_;

    static SimulationController* simulation_controller_;

    static pid_t pid_;
    
    static NSIdent * work_path_;
    static NSIdent * temp_path_;
    static NSIdent * netlist_name_;
    static NSIdent * sdb_creation_m_file_;

};
#endif //COSOLE_H
