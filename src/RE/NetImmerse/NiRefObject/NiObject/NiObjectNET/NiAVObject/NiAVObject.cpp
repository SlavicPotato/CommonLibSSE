#include "RE/NetImmerse/NiRefObject/NiObject/NiObjectNET/NiAVObject/NiAVObject.h"

#include "RE/BSCore/BSTSmartPointer.h"
#include "RE/BSGraphics/State.h"
#include "RE/BSShader/BSEffectShaderData.h"
#include "RE/BSShader/BSShaderMaterial/BSLightingShaderMaterialBase/BSLightingShaderMaterialFacegenTint.h"
#include "RE/BSShader/BSShaderMaterial/BSLightingShaderMaterialBase/BSLightingShaderMaterialHairTint.h"
#include "RE/BSShader/BSShaderMaterial/BSShaderMaterial.h"
#include "RE/NetImmerse/BSVisit.h"
#include "RE/NetImmerse/NiColor.h"
#include "RE/NetImmerse/NiRTTI.h"
#include "RE/NetImmerse/NiRefObject/NiObject/NiObjectNET/NiAVObject/BSGeometry/BSGeometry.h"
#include "RE/NetImmerse/NiRefObject/NiObject/NiObjectNET/NiAVObject/NiNode/NiNode.h"
#include "RE/NetImmerse/NiRefObject/NiObject/NiObjectNET/NiProperty/NiProperty.h"
#include "RE/NetImmerse/NiRefObject/NiObject/NiObjectNET/NiProperty/NiShadeProperty/BSShaderProperty/BSLightingShaderProperty.h"
#include "RE/NetImmerse/NiRefObject/NiObject/NiObjectNET/NiProperty/NiShadeProperty/BSShaderProperty/BSShaderProperty.h"


namespace RE
{
	bool NiAVObject::GetAppCulled() const
	{
		return flags.all(Flag::kHidden);
	}


	bool NiAVObject::SetMotionType(std::uint32_t a_motionType, bool a_arg2, bool a_arg3, bool a_allowActivate)
	{
		using func_t = decltype(&NiAVObject::SetMotionType);
		REL::Offset<func_t> func(Offset::NiAVObject::SetMotionType);
		return func(this, a_motionType, a_arg2, a_arg3, a_allowActivate);
	}


	void NiAVObject::TintScenegraph(const NiColorA& a_color)
	{
		auto gState = RE::BSGraphics::State::GetSingleton();
		BSTSmartPointer<BSEffectShaderData> newShaderData(new RE::BSEffectShaderData());
		newShaderData->fillColor = a_color;
		newShaderData->baseTexture = gState->defaultTextureWhite;

		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			auto effect = a_geometry->properties[BSGeometry::States::kEffect];
			auto shaderProp = netimmerse_cast<BSShaderProperty*>(effect.get());
			if (shaderProp && shaderProp->AcceptsEffectData()) {
				auto shaderData = shaderProp->effectData;
				if (!shaderData || shaderData->baseTexture == gState->defaultTextureWhite) {
					shaderProp->SetEffectShaderData(newShaderData);
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}


	void NiAVObject::Update(NiUpdateData& a_data)
	{
		using func_t = decltype(&NiAVObject::Update);
		REL::Offset<func_t> func(Offset::NiAVObject::Update);
		return func(this, a_data);
	}


	void NiAVObject::UpdateBodyTint(const NiColor& a_color)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kFaceGenRGBTint) {
						auto facegenTint = static_cast<BSLightingShaderMaterialFacegenTint*>(material);
						facegenTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}


	void NiAVObject::UpdateHairColor(const NiColor& a_color)
	{
		BSVisit::TraverseScenegraphGeometries(this, [&](BSGeometry* a_geometry) -> BSVisit::BSVisitControl {
			using State = BSGeometry::States;
			using Feature = BSShaderMaterial::Feature;

			auto effect = a_geometry->properties[State::kEffect].get();
			if (effect) {
				auto lightingShader = netimmerse_cast<BSLightingShaderProperty*>(effect);
				if (lightingShader) {
					auto material = lightingShader->material;
					if (material && material->GetFeature() == Feature::kHairTint) {
						auto hairTint = static_cast<BSLightingShaderMaterialHairTint*>(material);
						hairTint->tintColor = a_color;
					}
				}
			}

			return BSVisit::BSVisitControl::kContinue;
		});
	}
}
