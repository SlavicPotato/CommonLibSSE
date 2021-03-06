#pragma once

#include "RE/BSExtraData/BSExtraData.h"
#include "RE/BSExtraData/Enums/ExtraDataTypes.h"
#include "RE/NetImmerse/NiSmartPointer.h"


namespace RE
{
	class NiNode;


	class ExtraCell3D : public BSExtraData
	{
	public:
		inline static constexpr auto RTTI = RTTI_ExtraCell3D;
		inline static constexpr auto EXTRADATATYPE = ExtraDataType::kCell3D;


		virtual ~ExtraCell3D();	 // 00

		// override (BSExtraData)
		virtual ExtraDataType GetType() const override;	 // 01 - { return kCell3D; }


		// members
		NiPointer<NiNode> cellNode;	 // 10
	};
	static_assert(sizeof(ExtraCell3D) == 0x18);
}
