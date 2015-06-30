

/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef MESSAGESEVERITYTYPE_H
#define MESSAGESEVERITYTYPE_H


class MessageSeverityType{
public:
	enum Severity_e{
	    msgIgnore,
	    msgNotice,
	    msgWarning,
	    msgAmputate,
	};
};

//typedef severityType MessageSeverityType::Severity_e;
typedef unsigned short Severity_t;
#endif //MESSAGESEVERITYTYPE_H
