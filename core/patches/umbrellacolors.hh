#pragma once

namespace patch::umbrellacolors
{
	bool Apply(SceneObjectProperties* sceneObj, SimObjectProp* simObj)
	{
		if (!helper::IsUmbrella(sceneObj)) {
			return false;
		}

		auto compositeDrawable = simObj->GetCompositeDrawable();
		if (!compositeDrawable) {
			return false;
		}

		// Pseudo RNG based on object nameUID, change this if need better range of colors or make list?
		static u32 sLastPrime = 0xF7AD9A67;
		const u32 prime = sLastPrime + (0xB9B30BBF * simObj->m_Name.mUID);
		sLastPrime = prime;

		const u32 huePrime = prime % 360;
		const float saturation = 0.5f + qRandom(0.25f);
		const float vibrance = qRandom(1.f);

		auto col = reinterpret_cast<qColour*>(compositeDrawable->mSceneryInstance.ColourTint);
		qColourHSVToRGB(*col, { static_cast<f32>(huePrime), saturation, vibrance });
		return true;
	}
}