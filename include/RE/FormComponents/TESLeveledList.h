#pragma once

#include "RE/FormComponents/BaseFormComponent.h"
#include "RE/FormComponents/Components/ContainerItemExtra.h"
#include "RE/FormComponents/Enums/FormTypes.h"
#include "RE/Memory/MemoryManager.h"


namespace RE
{
	class TESFaction;
	class TESForm;
	class TESGlobal;


	struct LEVELED_OBJECT
	{
	public:
		// members
		TESForm*			form;		// 00 - LVLO~
		std::uint16_t		count;		// 08
		std::uint16_t		level;		// 0A - ~LVLO
		std::uint32_t		pad0C;		// 0C
		ContainerItemExtra* itemExtra;	// 10 - COED
	};
	static_assert(sizeof(LEVELED_OBJECT) == 0x18);


	class TESLeveledList : public BaseFormComponent
	{
	public:
		inline static constexpr auto RTTI = RTTI_TESLeveledList;


		enum Flag : std::uint8_t  // LVLF
		{
			kCalculateFromAllLevelsLTOrEqPCLevel = 1 << 0,
			kCalculateForEachItemInCount = 1 << 1,
			kUseAll = 1 << 2,
			kSpecialLoot = 1 << 3
		};


		virtual ~TESLeveledList();	// 00

		// override (BaseFormComponent)
		virtual void InitializeDataComponent() override;				// 01
		virtual void ClearDataComponent() override;						// 02
		virtual void CopyComponent(BaseFormComponent* a_rhs) override;	// 03

		// add
		virtual std::uint8_t GetChanceNone();									   // 04 - { if (global) return global->value; else return chanceNone; }
		virtual bool		 GetMultCalc();										   // 05 - { return (flags >> 1) & 1; }
		virtual std::int32_t GetLevDifferenceMax();								   // 06 - { return 0; }
		virtual bool		 GetCanContainFormsOfType(FormType a_type) const = 0;  // 07

		std::vector<TESForm*> GetContainedForms() const;


		// members
		SimpleArray<LEVELED_OBJECT> entries;	   // 08
		std::int8_t					chanceNone;	   // 10 - LVLD
		Flag						llFlags;	   // 11 - LVLF
		std::uint8_t				numEntries;	   // 12 - LLCT
		std::uint8_t				unk13;		   // 13
		std::uint32_t				pad14;		   // 14
		void*						unk18;		   // 18
		TESGlobal*					chanceGlobal;  // 20 - LVLG
	};
	static_assert(sizeof(TESLeveledList) == 0x28);
}
