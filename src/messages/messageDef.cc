

/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "messageDef.h"

MessageDef::MessageDef(
	       NSIdent * name,
	       NSIdent * msg,
	       Severity_t sev,
	       message_id_type id
	      )
{
    name_ = name;
    msg_ = msg;
    sev_ = sev;
    id_ = id;
}
