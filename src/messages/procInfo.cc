

/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "procInfo.h"

time_t ProcInfo::init_time_ = 0;
time_t ProcInfo::cur_time_ = 0;

int ProcInfo::getPhyMem(const pid_t p)
{
    //get the line vmrss
    char file[64] = {0};

    FILE *fd;         
    char line_buff[256] = {0};  
    sprintf(file,"/proc/%d/status",p);

    //fprintf (stderr, "current pid:%d\n", p);
    fd = fopen (file, "r"); 


    int i;
    char name[32];
    int vmrss;
    for (i=0;i<VMRSS_LINE-1;i++)
    {
	fgets (line_buff, sizeof(line_buff), fd);
    }
    fgets (line_buff, sizeof(line_buff), fd);
    sscanf (line_buff, "%s %d", name,&vmrss);
    //fprintf (stderr, "====%s**%d====\n", name,vmrss);
    fclose(fd);     
    return vmrss;
}

int ProcInfo::getRmem(pid_t p)
{
    return getPhyMem(p);
}


int ProcInfo::getTotalMem()
{
    char* file = "/proc/meminfo";

    FILE *fd;         
    char line_buff[256] = {0};  
    fd = fopen (file, "r"); 


    int i;
    char name[32];
    int memtotal;
    fgets (line_buff, sizeof(line_buff), fd);
    sscanf (line_buff, "%s %d", name,&memtotal);
    //fprintf (stderr, "====%s**%d====\n", name,memtotal);
    fclose(fd);     
    return memtotal;
}

float ProcInfo::getPmem(pid_t p)
{
    int phy = getPhyMem(p);
    int total = getTotalMem();
    float occupy = (phy*1.0)/(total*1.0);
    fprintf(stderr,"====process mem occupy:%.6f, used %d, total %d\n====",occupy, phy, total);
    return occupy;
}

unsigned int ProcInfo::getCpuProcessOccupy(const pid_t p)
{
    char file[64] = {0};
    process_cpu_occupy_t t;

    FILE *fd;         
    char line_buff[1024] = {0};  
    sprintf(file,"/proc/%d/stat",p);

    //fprintf (stderr, "current pid:%d\n", p);
    fd = fopen (file, "r"); 
    fgets (line_buff, sizeof(line_buff), fd); 

    sscanf(line_buff,"%u",&t.pid);
    const char* q = getItems(line_buff,PROCESS_ITEM);
    sscanf(q,"%u %u %u %u",&t.utime,&t.stime,&t.cutime,&t.cstime);

    //fprintf (stderr, "====pid%u:%u %u %u %u====\n", t.pid, t.utime,t.stime,t.cutime,t.cstime);
    fclose(fd);     
    return (t.utime + t.stime + t.cutime + t.cstime);
}


unsigned int ProcInfo::getCpuTotalOccupy()
{
    FILE *fd;         
    char buff[1024] = {0};  
    total_cpu_occupy_t t;

    fd = fopen ("/proc/stat", "r"); 
    fgets (buff, sizeof(buff), fd); 
    /*************buff************************format********************************************************* */
    char name[16];
    sscanf (buff, "%s %u %u %u %u", name, &t.user, &t.nice,&t.system, &t.idle);


    //fprintf (stderr, "====%s:%u %u %u %u====\n", name, t.user, t.nice,t.system, t.idle);
    fclose(fd);     
    return (t.user + t.nice + t.system + t.idle);
}


float ProcInfo::getPcpu(pid_t p)
{
    unsigned int totalcputime1,totalcputime2;
    unsigned int procputime1,procputime2;
    totalcputime1 = getCpuTotalOccupy();
    procputime1 = getCpuProcessOccupy(p);
    usleep(500000);
    totalcputime2 = getCpuTotalOccupy();
    procputime2 = getCpuProcessOccupy(p);
    float pcpu = 100.0*(procputime2 - procputime1)/(totalcputime2 - totalcputime1);
    fprintf(stderr,"====pcpu:%.6f\n====",pcpu);
    return pcpu;
}

const char* ProcInfo::getItems(const char* buffer,int ie)
{
    assert(buffer);
    const char* p = buffer;
    int len = strlen(buffer);
    int count = 0;
    if (1 == ie || ie < 1)
    {
	return p;
    }
    int i;

    for (i=0; i<len; i++)
    {
	if (' ' == *p)
	{
	    count++;
	    if (count == ie-1)
	    {
		p++;
		break;
	    }
	}
	p++;
    }

    return p;
}


void ProcInfo::initProcInfo(){
    init_time_ = time(NULL);
    localTime();
}
void ProcInfo::curProcTime(){
    cur_time_ = time(NULL); ;
}
double ProcInfo::getProcTime(){
    curProcTime();
    return difftime( cur_time_, init_time_ ); 
}
void ProcInfo::localTime(){
    struct tm* current_time = localtime(&init_time_);
    /*printf("Simulation running at: %d-%d-%d\r\n",
	   1900 + current_time->tm_year,
	   1 + current_time->tm_mon,
	   current_time->tm_mday);*/
    /*printf("current day of year is %d;current day in week is %d\r\n",
	   current_time->tm_yday,
	   current_time->tm_wday);*/

    /*printf("time part %d:%d:%d \r\n",
	   current_time->tm_hour,
	   current_time->tm_min,
	   current_time->tm_sec);*/

    printf("local time: \t%d-%d-%d %d:%d:%d\r\n",
	   current_time->tm_year + 1900,
	   current_time->tm_mon + 1,
	   current_time->tm_mday,
	   current_time->tm_hour,
	   current_time->tm_min,
	   current_time->tm_sec);
    struct tm* current_gmtime = gmtime(&init_time_);

    printf("greenwich time: %d-%d-%d %d:%d:%d\r\n",
	   current_gmtime->tm_year + 1900,
	   current_gmtime->tm_mon + 1,
	   current_gmtime->tm_mday,
	   current_gmtime->tm_hour,
	   current_gmtime->tm_min,
	   current_gmtime->tm_sec);
}
void ProcInfo::getMachineInfo(){
}
