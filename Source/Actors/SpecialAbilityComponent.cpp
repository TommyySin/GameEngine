#include "SpecialAbilityComponent.h"

const char* SpeicalAbility::g_Name = "SpeicalAbility";


bool SpeicalAbility::VInit(TiXmlElement* pData)
{
	return true;
}
void SpeicalAbility::VApply(WeakActorPtr pActor)
{
	StrongActorPtr pStrongActor = MakeStrongPtr(pActor);
	if (pStrongActor)
	{
		cout << "Applying Special Ability to actor id " << (string)(pStrongActor->GetId());
	}
}