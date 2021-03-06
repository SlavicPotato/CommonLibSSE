#include "RE/FormComponents/Components/ActiveEffect/ActiveEffect.h"

#include "RE/FormComponents/Components/Effect.h"
#include "RE/FormComponents/TESForm/TESObjectREFR/Actor/Actor.h"


namespace RE
{
	void ActiveEffect::Dispell(bool a_force)
	{
		using func_t = decltype(&ActiveEffect::Dispell);
		REL::Offset<func_t> func(Offset::ActiveEffect::Dispell);
		return func(this, a_force);
	}


	EffectSetting* ActiveEffect::GetBaseObject()
	{
		return effect ? effect->baseEffect : nullptr;
	}


	const EffectSetting* ActiveEffect::GetBaseObject() const
	{
		return effect ? effect->baseEffect : nullptr;
	}


	NiPointer<Actor> ActiveEffect::GetCasterActor() const
	{
		return caster.get();
	}


	Actor* ActiveEffect::GetTargetActor()
	{
		if (target && target->MagicTargetIsActor()) {
			return static_cast<Actor*>(target);
		} else {
			return nullptr;
		}
	}


	const Actor* ActiveEffect::GetTargetActor() const
	{
		if (target && target->MagicTargetIsActor()) {
			return static_cast<const Actor*>(target);
		} else {
			return nullptr;
		}
	}
}
