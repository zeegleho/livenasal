
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SIMULATORGLOBAL_H
#define SIMULATORGLOBAL_H
//define some constant
//UNITS
#define UNIT 1
#define ACCURACY 8 
#define RANGE ( pow(2,ACCURACY) * UNIT )

//unit is mm
extern int RANGE_X_BEGIN;
extern int RANGE_X_END;
extern int RANGE_Y_BEGIN;
extern int RANGE_Y_END;
extern int RANGE_Z_BEGIN;
extern int RANGE_Z_END;

typedef unsigned int type_t;
typedef long unsigned int spaceParticleKey_t;   
typedef long unsigned int spaceParticle_t;   
#endif //SIMULATORGLOBAL_H
