#pragma once

namespace hook::gamestateingame
{
	SDK::Hook gOnEnter;

	void __fastcall OnEnter(UFG::GameState* game_state, float fRealTimeDelta)
	{
		gOnEnter(game_state, fRealTimeDelta);

		auto resource = reinterpret_cast<UFG::qChunk*>(gResource_LOF_BUSHLARGE002_A)->GetData();
		if (!resource->mResourceHandles.mNode.mNext) {
			UFG::StreamResourceLoader::Load(gResource_LOF_BUSHLARGE002_A, sizeof(gResource_LOF_BUSHLARGE002_A));
		}

		if (gConfig.mValveTShirtPack) {
			patch::valvetshirtpack::Apply();
		}
	}
}