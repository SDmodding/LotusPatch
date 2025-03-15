#include "core/core.hh"

int __stdcall DllMain(HMODULE mod, DWORD reason, LPVOID reserved)
{   
    if (reason == DLL_PROCESS_ATTACH)
    {
        if (!SDK::IsValidExecutable())
        {
            MsgBox_Error("Only the Steam v1.0 executable is supported!\nVisit github.com/SDmodding for more details.");
            return 0;
        }

        if (!core::Initialize()) {
            return 0;
        }

        DisableThreadLibraryCalls(mod);
    }

    return 1;
}