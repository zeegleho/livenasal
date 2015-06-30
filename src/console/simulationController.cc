
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include "simulationController.h"
#include "../console/global.h"

bool  SimulationController::useAirSimulator(){
    return simulator_ & simulator_air;           //00000001
}
bool SimulationController::useDustSimulator(){
    return simulator_ & simulator_dust;          //00000010
}
bool SimulationController::useHmiditySimulator(){
    return simulator_ & simulator_hmidity;       //00000100
}
bool SimulationController::useGravitySimulator(){
    return simulator_ & simulator_gravity;       //00001000
}
