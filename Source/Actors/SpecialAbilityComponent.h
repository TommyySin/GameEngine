#pragma once
#include "AbilitiesInterface.h"

class SpeicalAbility : public AbilitiesInterface
{
public:
	virtual bool VInit(TiXmlElement* pData);
	virtual void VApply(WeakActorPtr pActor);
};