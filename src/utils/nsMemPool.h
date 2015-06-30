
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef NSMEMPOOL_H
#define NSMEMPOOL_H

class NSMemPool{
public:
    NSMemPool* create();
    const char* getValue();
private:
    NSMemPool();
};

#endif //NSMEMPOOL_H
