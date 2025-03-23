#pragma once

namespace patch::borderlesswindow
{
	bool Apply()
	{
		DWORD style = WS_POPUP;

		return qPatcher::Bytes(SDK_RVA_PTR(0x6A07E1), &style, sizeof(style))
			&& qPatcher::Bytes(SDK_RVA_PTR(0x6A082A), &style, sizeof(style))
			&& qPatcher::Bytes(SDK_RVA_PTR(0x6A083A), 0)
			&& qPatcher::Bytes(SDK_RVA_PTR(0x6A0842), 0);
	}
}