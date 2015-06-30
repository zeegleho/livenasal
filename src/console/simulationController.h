
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#ifndef SIMULATIONCONTROLLER_H
#define SIMULATIONCONTROLLER_H
#include "../console/global.h"

class SimulationController{

public:
//simulator = [air dust humidity gravity] 
    type_t simulator_;

    static const type_t type_unknown = 0;
    static const type_t simulator_air = 1;           //00000001
    static const type_t simulator_dust = 2;          //00000010
    static const type_t simulator_hmidity = 4;       //00000100
    static const type_t simulator_gravity = 8;       //00001000

    bool useAirSimulator();
    bool useDustSimulator();
    bool useHmiditySimulator();
    bool useGravitySimulator();

    double starttime_ = 0;
    double stoptime_ = 0;  

    int accuracy_; 
//accuracy=1/2/3/DEBUG        
};
#endif //SIMULATIONCONTROLLER_H
