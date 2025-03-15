#pragma once

namespace hook::gamestateingame
{
	SDK::Hook gOnEnter;

	void __fastcall OnEnter(UFG::GameState* game_state, float fRealTimeDelta)
	{
		gOnEnter(game_state, fRealTimeDelta);

		if (gConfig.mValveTShirtPack) {
			patch::valvetshirtpack::Apply();
		}
	}
}