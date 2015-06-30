

/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef MESSAGEINTERFACE_H
#define MESSAGEINTERFACE_H

#include "messageSeverityType.h"
#include "messageDef.h"
#include "messages.h"

class MessageInterface {
public:
    MessageInterface();
    
    static void setMsgInterface( MessageInterface *msgInterface_ );
    static MessageInterface * getMsgInterface();
    void printLog( char* str );
    void printLog( int i );
    void print( char* fmt, ... );
    void print( message_id_type  msg_id, ... );
    void print( MessageDef* msg, ... );
    void printMsg( char* str, ... );

    static NSIdent* getStage();
    static void setStage(NSIdent* );
    static void initProcInfo();
    static void caculateProcInfo();
    static void showProcInfo(pid_t p);
private: 
    static MessageInterface *msgInterface_;

    static NSIdent* stage_;

};
#endif //MESSAGEINTERFACE_H
