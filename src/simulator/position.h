
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef POSITION_H
#define POSITION_H
class Position {
public:
	int x_;
	int y_;
	int z_;

public:
	Position(int x, int y, int z); 
	int x();
	int y();
	int z();
};
#endif //POSITION_H
