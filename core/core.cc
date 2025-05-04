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
#include "patches/mouseinput.hh"
#include "patches/mousexbutton.hh"
#include "patches/valvetshirtpack.hh"

//--------------------------------
//	Hooks
//--------------------------------

#include "hooks/compositelook.hh"
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
		//hook::componentfactory::gPropertiesOnActivate.I_SceneObjectProperties(SDK::Hook::SceneObjectProperties_Activate, hook::componentfactory::PropertiesOnActivate);
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
			return 0;
		}

		if (!patch::mouseinput::Apply()) {
			return 0;
		}

		if (!patch::mousexbutton::Apply()) {
			return 0;
		}

		// Optionals

		if (gConfig.mSkipIntroScreens && !patch::skipintroscreens::Apply()) {
			return 0;
		}

		if (gConfig.mBorderlessWindow && !patch::borderlesswindow::Apply()) {
			return 0;
		}

		return 1;
	}

	bool InitializeHooks()
	{
		struct
		{
			uintptr_t mRVA;
			void* mFunc;
			void* mOriginal = nullptr;
		} const hooks[] = {
			{ 0x6A2250, hook::SetWindow },
		};

		for (auto& hook : hooks)
		{
			if (MH_CreateHook(SDK_RVA_PTR(hook.mRVA), hook.mFunc, (void**)hook.mOriginal) != MH_OK) {
				return 0;
			}
		}

		reinterpret_cast<SDK::Hook*>(&hook::compositelook::gOnDrawSkin)->I_FuncPtr(SDK_RVA(0x17C3598), hook::compositelook::OnDrawSkin);

		SDK::Hook hook;
		hook.I_FuncPtr(SDK_RVA(0x17C35A0), hook::compositelook::OnDrawRigid);

		return 1;
	}

	bool Initialize()
	{
		ini_parse("plugins/LotusPatch.ini", ini_config, 0);

		if (!InitializePatches())
		{
			MsgBox_Error("Failed to initialize patches.");
			return 0;
		}

		if (!InitializeHooks())
		{
			MsgBox_Error("Failed to initialize hooks.");
			return 0;
		}

		gInitGameSystems.I_InitGameSystems(InitGameSystems);
		return 1;
	}
}