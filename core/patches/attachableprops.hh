#pragma once

namespace patch::attachableprops
{
	bool Apply()
	{
		// Prevent return when asset propertySet is nullptr.
		// Due to this the props will be spawned & attached.
		// This can cause issues like props clipping through certain character models.
		// Would require to check all props & characters and modify scale, rotation & translation.
		return qPatcher::Bytes(SDK_RVA_PTR(0x52405B), { 0xEB, 0x04 });
	}

	void ApplyInit()
	{
		const qPropertyList* mainPropList;

		// Replace broken ambient police hat with working one.

		if (auto propSet = PropertySetManager::FindPropertySet(0x309915CE)) // object-physical-character-police_ambient
		{
			if (auto propList = propSet->Get<qPropertyList>(0x1EAE8392))
			{
				mainPropList = propList;

				if (auto itemSymbol = propList->Get<qSymbol>(0)) {
					*itemSymbol = 0x804388F3; // object-physical-prop-Attachable-AmbientHat002
				}
			}
		}

		// Add missing prop list for other police characters.

		if (auto parentSet = PropertySetManager::FindPropertySet(0x1C69EB1E)) // object-physical-character-stats-police_striker
		{
			if (qPropertySet* proxySet = PropertySetManager::CreateOrFindPropertySet(0x52858806)) // object-physical-character-stats-police_striker-proxy
			{
				proxySet->AddParent(parentSet);
				proxySet->Set(0x1EAE8392, mainPropList);

				auto proxySetResource = proxySet->GetResource();
				proxySetResource->SetDebugName(0);

				const qSymbol propNames[] = {
					0x34317ACA, // object-physical-character-police_variation1
					0x39725C13, // object-physical-character-police_variation2
					0x3DB341A4, // object-physical-character-police_variation3
					0x123CA7F1, // object-physical-character-policebuddycopdlc
					0x0C02DD39, // object-physical-character-policeold
					0xEA57FD95	// object-physical-character-policeyoung
				};

				for (auto& name : propNames)
				{
					if (auto propSet = PropertySetManager::FindPropertySet(name))
					{
						if (!propSet->mNumParents) {
							continue;
						}

						auto parent = propSet->mParents.Get();
						parent->Close();

						parent->mNameUID = proxySet->mName.mUID;
						parent->mData = proxySetResource;
					}
				}
			}
		}
	}
}