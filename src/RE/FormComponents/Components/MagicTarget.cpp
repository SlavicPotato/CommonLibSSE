#include "RE/FormComponents/Components/MagicTarget.h"

#include "RE/BSCore/BSTList.h"
#include "RE/FormComponents/Components/ActiveEffect/ActiveEffect.h"
#include "RE/FormComponents/TESForm/EffectSetting.h"


namespace RE
{
	void MagicTarget::DispellEffectsWithArchetype(Archetype a_type, bool a_force)
	{
		auto effects = GetActiveEffectList();
		if (!effects) {
			return;
		}

		EffectSetting* setting = nullptr;
		for (auto& effect : *effects) {
			setting = effect ? effect->GetBaseObject() : nullptr;
			if (setting && setting->HasArchetype(a_type)) {
				effect->Dispell(a_force);
			}
		}
	}


	bool MagicTarget::HasEffectWithArchetype(Archetype a_type)
	{
		auto effects = GetActiveEffectList();
		if (!effects) {
			return false;
		}

		EffectSetting* setting = nullptr;
		for (auto& effect : *effects) {
			setting = effect ? effect->GetBaseObject() : nullptr;
			if (setting && setting->HasArchetype(a_type)) {
				return true;
			}
		}
		return false;
	}


	bool MagicTarget::HasMagicEffect(EffectSetting* a_effect)
	{
		using func_t = decltype(&MagicTarget::HasMagicEffect);
		REL::Offset<func_t> func(Offset::MagicTarget::HasMagicEffect);
		return func(this, a_effect);
	}
}
