
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef UTILS_H
#define UTILS_H
#include <string>
#include "../messages/messageInterface.h"

//define some useful fuctions

class Utils {
public:
    static char* substr(const char*str, unsigned start, unsigned end);
    static void reStyle(std::string& s);
    static void split(std::string& s, std::string& delim,std::vector< std::string >* ret);
    static std::string& getDelim();
    void setDelim( std::string& delim );
    
private:
    static std::string & delim_;
    static std::string delim;
};
#endif //UTILS_H
