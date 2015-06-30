

/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef MESSAGESDEF_H
#define MESSAGESDEF_H

#include <map>
#include "messageSeverityType.h"
#include "../utils/nsIdent.h"

#define msgAmputate 0
#define msgWarning 1
#define msgNotice 2
#define msgIgnore 3

typedef int message_id_type;

class MessageDef{

public:
    NSIdent * name_;
    NSIdent * msg_;
    Severity_t sev_;
    message_id_type id_;

    MessageDef(
	       NSIdent * Name,
	       NSIdent * msg,
	       Severity_t sev,
	       message_id_type id
	      );
};

//typedef std::map< message_id_type, MessageDef* > messageList_t;
//static messageList_t message_list_;

#endif //MESSAGESDEF_H
