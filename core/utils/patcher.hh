#pragma once
#include <initializer_list>

class qPatcher
{
public:
	static bool Bytes(void* address, const void* buffer, size_t size)
	{
		DWORD dwProtect;
		if (!VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &dwProtect)) {
			return false;
		}

		memcpy(address, buffer, size);
		FlushInstructionCache(reinterpret_cast<HANDLE>(-1), address, size);

		VirtualProtect(address, size, dwProtect, &dwProtect);
		return true;
	}

	static __forceinline bool Bytes(void* address, std::initializer_list<uint8_t> bytes)
	{
		return Bytes(address, bytes.begin(), bytes.size());
	}

	static bool Bytes(void* address, uint8_t byte, size_t size = 1)
	{
		DWORD dwProtect;
		if (!VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &dwProtect)) {
			return false;
		}

		memset(address, byte, size);
		FlushInstructionCache(reinterpret_cast<HANDLE>(-1), address, size);

		VirtualProtect(address, size, dwProtect, &dwProtect);
		return true;
	}

};