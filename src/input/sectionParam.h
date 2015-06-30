
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SECTIONPARAM_H
#define SECTIONPARAM_H

class SectionParam{
public:
    SectionParam( const char* name, const char* value);

    const char* getName();
    const char* getValue();
private:
    const char * name_;
    const char * value_;

};

#endif //SECTIONPARAM_H
