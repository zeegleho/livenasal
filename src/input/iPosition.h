
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef IPOSITION_H
#define IPOSITION_H
class IPosition{
public:
    IPosition(double x, double y, double z):
	x_(x),y_(y),z_(z)
    { }
    double x() {return x_;}
    double y() {return y_;}
    double z() {return z_;}
private:
    double x_, y_,z_;
};
#endif //IPOSITION_H
