#pragma once

namespace helper
{
	bool IsUmbrella(SceneObjectProperties* sceneObj)
	{
		auto propSet = sceneObj->mpWritableProperties;
		if (!propSet)
		{
			propSet = sceneObj->mpConstProperties;
			if (!propSet) {
				return false;
			}
		}

		const qSymbol nameUID = 0x949A4909; // object-physical-weapon-melee-umbrella
		if (propSet->mName == nameUID ||
			propSet->mNumParents && propSet->GetParentFromIdx(0)->mName == nameUID) {
			return true;
		}

		return false;
	}
}