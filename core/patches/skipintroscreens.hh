#pragma once

namespace patch::skipintroscreens
{
	bool Apply()
	{
		if (!qPatcher::Bytes(SDK_RVA_PTR(0x420C82), { 0xE9, 0x38, 0x01, 0x00 }) ||	// Legal Screen
			!qPatcher::Bytes(SDK_RVA_PTR(0x5F3FC3), { 0xEB, 0x4E }) ||				// PlayDemo
			!qPatcher::Bytes(SDK_RVA_PTR(0x5F4123), { 0xEB, 0x67 }) ||				// PlaySplash
			!qPatcher::Bytes(SDK_RVA_PTR(0x63FE9C), { 0xE9, 0x82, 0x00 }) ||
			!qPatcher::Bytes(SDK_RVA_PTR(0x63FEB8), { 0xEB, 0x69 }) ||
			!qPatcher::Bytes(SDK_RVA_PTR(0x63FED2), { 0xEB, 0x4F }))
		{
			return false;
		}

		return true;
	}
}