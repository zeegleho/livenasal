

/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef PROCINFO_H
#define PROCINFO_H
#include <time.h>

class ProcInfo{
    //get mem info:
    // /proc/pid/status
    //get cpu info:
    // /proc/pid/stat
    //processCpuTime = utime + stime + cutime + cstime

#define VMRSS_LINE 17
#define PROCESS_ITEM 14

    typedef struct        
    {
	unsigned int user;  
	unsigned int nice;  
	unsigned int system;
	unsigned int idle;  
    }total_cpu_occupy_t;

    typedef struct
    {
	pid_t pid;
	unsigned int utime;  
	unsigned int stime;  
	unsigned int cutime;
	unsigned int cstime;  
    }process_cpu_occupy_t;
public:
    static void getMachineInfo();
    static void getProcInfo();

    static int getPhyMem(const pid_t p);
    static int getTotalMem();
    static unsigned int getCpuTotalOccupy();
    static unsigned int getCpuProcessOccupy(const pid_t p);
    static const char* getItems(const char* buffer,int ie);

    static float getPcpu(pid_t p);
    static float getPmem(pid_t p);
    static int getRmem(pid_t p);

    static void initProcInfo();
    static void curProcTime();
    static double getProcTime();

private:
    static time_t init_time_ ;
    static time_t cur_time_ ;
    static void localTime();

};
#endif //PROCINFO_H

