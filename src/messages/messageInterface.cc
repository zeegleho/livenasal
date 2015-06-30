

/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <stdarg.h>
#include <iostream>
#include <string>
#include <sstream>
#include "messageInterface.h"
#include "messageDef.h"
#include "procInfo.h"

MessageInterface *MessageInterface::msgInterface_ = new MessageInterface();
NSIdent* MessageInterface::stage_ = NSIdent::create("livenasal");

MessageInterface::MessageInterface(){
}
void MessageInterface::printLog( int i  ){
    std::cout<<"----"<<i<<std::endl;
}
void MessageInterface::printLog( char* str ){
    std::cout<<"----"<<str<<std::endl;
}

void MessageInterface::print( MessageDef* msg, ... ){
    std::ostringstream result_stream;
    result_stream<<stage_->getValue()<<"-"<<msg->id_<<": ";
    
    const char* str = msg->msg_->getValue();
    int arg1;
    float arg2;
    char token,*arg3;
    va_list ap;
    va_start(ap,msg);

    while(*str!='\0')
    {
	if(*str=='%')
	{
	    token=*(++str);
	    switch(token)
	    {
	    case 'd':
		arg1=va_arg(ap,int);
		result_stream<<arg1;
		break;
	    case '%':
		result_stream<<token;
		break;
	    case 's':
		arg3 = va_arg(ap,char *);
		result_stream<<arg3;
		break;
	    case 'f':
		arg2 = va_arg(ap,double);
		result_stream<<arg2;
		break;
	    }
	}
	else
	   result_stream<<(*str);

	str++;
    }
    result_stream<<('\n');

    std::string result = result_stream.str();
    printf( result.c_str() );
}

void MessageInterface::print( message_id_type  msg_id, ... ){
//    MessageDef *msg = message_list_[msg_id];
//    const char *fmt = msg->msg_->getValue();

}

void MessageInterface::print( char* str, ... )
{
    int arg1;
    float arg2;
    char token,*arg3;

    va_list ap;
    va_start(ap,str);

    while(*str!='\0')
    {
	if(*str=='%')
	{
	    token=*(++str);
	    switch(token)
	    {
	    case 'd':
		arg1=va_arg(ap,int);
		printf("%d",arg1);
		break;
	    case '%':
		putchar(token);
		break;
	    case 's':
		arg3 = va_arg(ap,char *);
		printf("%s", arg3 );
		break;
	    case 'f':
		arg2 = va_arg(ap,double);
		printf("%f", arg2 );
		break;
	    }
	}
	else
	    putchar(*str);

	str++;

    }
    /*
       char * s;
       int d;
       va_list vl;
    //va_start( vl, str );
     */

    /*do{
      s = va_arg( vl, char* );
      if( s!=NULL ) std::cout<<"----"<<s;
      }while( s!=NULL );
      std::cout<<std::endl;
     */
    /*   
	 d = va_arg( vl, int );
	 std::cout<<"----"<<d<<std::endl;
     */
    /*
       char *str;
       va_list v1;
       str = first;
       va_start(v1,first);
       do 
       {
       printf("%s\n",str);
       str=va_arg(v1,char*);
       } while (str != NULL );
       va_end(v1);
     */

    /*
       va_list args;
       int i;

       va_start(args, fmt);
       write(1,printbuf,i=vsprintf(printbuf, fmt, args));
       va_end(args);
     */

}

void MessageInterface::printMsg( char* str, ... )
{}


void MessageInterface::setMsgInterface( MessageInterface *msgInterface ){
    msgInterface_ = msgInterface ; 
}
MessageInterface * MessageInterface::getMsgInterface(){
    return msgInterface_; 
}
NSIdent* MessageInterface::getStage(){
    return stage_;
}
void MessageInterface::setStage(NSIdent* stage ){
    stage_ = stage;
}
void MessageInterface::initProcInfo(){
    ProcInfo::initProcInfo();
}
void MessageInterface::caculateProcInfo(){

}
void MessageInterface::showProcInfo(pid_t p){
    ProcInfo::getPmem( p );
    //ProcInfo::getPcpu( p );
    double t =  ProcInfo::getProcTime();
    msgInterface_->print( "livenasal running time: %f\n", t );
}
