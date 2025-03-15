#pragma once

namespace hook::compositedrawablecomponent
{
	void(__fastcall* gReset)(CompositeDrawableComponent*);
	void __fastcall Reset(CompositeDrawableComponent* component)
	{
		gReset(component);

		auto simObj = component->m_pSimObject;
		if (!simObj) {
			return;
		}

		if (simObj->IsProp())
		{
			auto sceneObj = simObj->m_pSceneObj;
			if (gConfig.mUmbrellaColors && sceneObj && patch::umbrellacolors::Apply(sceneObj, reinterpret_cast<SimObjectProp*>(simObj))) {
				return;
			}

			return;
		}
	}
}