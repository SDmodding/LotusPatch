#include "../contrib/ini.h"

#include "core.hh"
#include "globals.hh"

using namespace UFG;

#include "utils/helpers.hh"

//--------------------------------
//	Patches
//--------------------------------

#include "patches/attachableprops.hh"
#include "patches/borderlesswindow.hh"
#include "patches/skipintroscreens.hh"
#include "patches/mousexbutton.hh"
#include "patches/umbrellacolors.hh"
#include "patches/valvetshirtpack.hh"

//--------------------------------
//	Hooks
//--------------------------------

#include "hooks/componentfactory.hh"
#include "hooks/compositedrawablecomponent.hh"
#include "hooks/gamestateingame.hh"
#include "hooks/setwindow.hh"

//--------------------------------
//	Core
//--------------------------------

namespace core
{
	// Configuration (INI)

	struct qVarINI
	{
		u32 mName;
		bool* mValue;
	};

#define MAP_INI(name, val) { cStringHashUpper32(name), &val }

	int ini_config(void* user, const char* section, const char* name, const char* value)
	{
		static const qVarINI vars[] = {
			MAP_INI("AttachableProps", gConfig.mAttachableProps),
			MAP_INI("UmbrellaColors", gConfig.mUmbrellaColors),
			MAP_INI("ValveTShirtPack", gConfig.mValveTShirtPack),

			// Optionals
			MAP_INI("SkipIntroScreens", gConfig.mSkipIntroScreens),
			MAP_INI("Borderless", gConfig.mBorderlessWindow),
		};

		const u32 nameHash = qStringHashUpper32(name);

		for (auto& var : vars)
		{
			if (var.mName == nameHash)
			{
				*var.mValue = atoi(value);
				break;
			}
		}

		return 0;
	}

	// Initializers

	SDK::Hook gInitGameSystems;

	void InitGameSystems()
	{
		hook::componentfactory::gPropertiesOnActivate.I_SceneObjectProperties(SDK::Hook::SceneObjectProperties_Activate, hook::componentfactory::PropertiesOnActivate);
		hook::gamestateingame::gOnEnter.I_GameStateInGame(SDK::Hook::GameState_OnEnter, hook::gamestateingame::OnEnter);

		patch::attachableprops::ApplyInit();

		gInitGameSystems();
	}

	bool InitializePatches()
	{
#ifdef _DEBUG
		// Don't install keyboard hook for debugging purposes.
		qPatcher::Bytes(SDK_RVA_PTR(0xA3FF00), 0xC3);
#endif

		if (gConfig.mAttachableProps && !patch::attachableprops::Apply()) {
			return false;
		}

		if (!patch::mousexbutton::Apply()) {
			return false;
		}

		// Optionals

		if (gConfig.mSkipIntroScreens && !patch::skipintroscreens::Apply()) {
			return false;
		}

		if (gConfig.mBorderlessWindow && !patch::borderlesswindow::Apply()) {
			return false;
		}

		return true;
	}

	bool InitializeHooks()
	{
		struct
		{
			uintptr_t mRVA;
			void* mFunc;
			void* mOriginal = nullptr;
		} const hooks[] = {
			{ 0x3DC0, hook::compositedrawablecomponent::Reset, &hook::compositedrawablecomponent::gReset },
			{ 0x6A2250, hook::SetWindow },
		};

		for (auto& hook : hooks)
		{
			if (MH_CreateHook(SDK_RVA_PTR(hook.mRVA), hook.mFunc, (void**)hook.mOriginal) != MH_OK) {
				return false;
			}
		}

		return true;
	}

	bool Initialize()
	{
		ini_parse("plugins/LotusPatch.ini", ini_config, 0);

		if (!InitializePatches())
		{
			MsgBox_Error("Failed to initialize patches.");
			return false;
		}

		if (!InitializeHooks())
		{
			MsgBox_Error("Failed to initialize hooks.");
			return false;
		}

		gInitGameSystems.I_InitGameSystems(InitGameSystems);
		return true;
	}
}