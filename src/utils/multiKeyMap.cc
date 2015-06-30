
#include "multiKeyMap.h"
bool operator < (const key& kl, const key& kr){
    if( kl.x_!=kr.x_){
	return kl.x_<kr.x_;
    }else{
	return kl.y_<kr.y_;
    }
}
