#pragma once

namespace hook::componentfactory
{
	SDK::Hook gPropertiesOnActivate;

	void __fastcall PropertiesOnActivate(SceneObjectProperties* sceneObj, qMatrix44* worldMatrix, const qSymbol& objType, TransformNodeComponent* parentTransform)
	{
		gPropertiesOnActivate(sceneObj, worldMatrix, objType, parentTransform);

		if (objType == 0x8A5A95FC) // Weapon
		{
			if (gConfig.mUmbrellaColors && patch::umbrellacolors::Apply(sceneObj, reinterpret_cast<SimObjectProp*>(sceneObj->m_pSimObject))) {
				return;
			}

			return;
		}
	}
}