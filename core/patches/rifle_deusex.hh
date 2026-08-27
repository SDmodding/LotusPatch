#pragma once

namespace patch::rifle_deusex
{
    void ApplyInit()
    {
		if (auto propSet = PropertySetManager::FindPropertySet(0x3F9A40AA)) // object-physical-weapon-firearm-rifle-Rifle_DeusEx001
		{
			if (auto bulletType = propSet->Get<qSymbolUC>(0xB982B350))
			{
				*bulletType = 0x40283CD1; // Bullet_Rifle

				for (auto& weaponTypeInfo : UFG::SimObjectWeaponPropertiesComponent::sWeaponTypeInfos)
				{
					if (weaponTypeInfo.mPropertySetSymbol != propSet->mName) {
						continue;
					}

					weaponTypeInfo.mFireModes[0]->mBulletTypeID = *bulletType;
					break;
				}
			}
		}
    }
}