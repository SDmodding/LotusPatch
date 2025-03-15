#pragma once
#include <SDK/sdhd_sdk.hh>
#include <SDK/contrib/MinHook.h>

#include "utils/patcher.hh"

//--------------------------------

#define PROJECT_VERSION		"v1.0.0"
#define PROJECT_NAME		("LotusPatch " PROJECT_VERSION)

#define MsgBox_Error(msg)	MessageBoxA(0, msg, PROJECT_NAME, MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);

//--------------------------------

namespace core
{
	bool Initialize();
}