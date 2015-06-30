
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include "SDBCreator.h"
#include "SDBAccessor.h"
#include "../input/IDBAccessor.h"
#include "../input/section.h"
#include "../input/sectionParam.h"
#include "../input/sectionType.h"
#include "../input/sectionParamType.h"
#include "../input/iPosition.h"
#include "../input/sectionParamShape.h"
#include "../utils/utils.h"

#include "createSpaceParticles.h"

SDBAccessor::SDBAccessor( ){
    SDB_ = new SDB();
}

void SDBAccessor::addSpaceParticle( spaceParticle_t key, SpaceParticle * particle ){
	SDB_->addSpaceParticle( key, particle );
}

int SDBAccessor::getSpaceParticlesNum(){
    SDB_->getSpaceParticlesNum();
}

void SDBAccessor::getSpaceParticle( spaceParticle_t key ){
    SDB_->getSpaceParticle( key );
}
