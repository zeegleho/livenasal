
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef ONPUT_H 
#define ONPUT_H
#include "VDBCreator.h"
#include "VDBAccessor.h"
#include "VDB.h"
#include "LocalView.h"
#include "WebView.h"

class Output{
public:
	static void init();
	static void createVDB();
	static void runLocalView();
	static void runWebView();    //not impliment yet
private:
	static VDBCreator* VDB_creator_;
	static VDBAccessor* VDB_accessor_;
	static VDB* VDB_;
	static LocalView* local_view_;
	static WebView* web_view_;
};
#endif //ONPUT_H 
