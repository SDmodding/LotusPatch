#pragma once

namespace hook
{
	void __fastcall SetWindow(int w, int h)
	{
		auto hwnd = SDK_VAR_GET(HWND, 0x249CDF0);

		auto style = (Render::IsFullscreen() ? 0 : static_cast<DWORD>(GetWindowLongPtrA(hwnd, GWL_STYLE)));

		RECT rc;
		GetWindowRect(hwnd, &rc);

		RECT rcNew = { 0, 0, w, h };
		AdjustWindowRectEx(&rcNew, style, FALSE, 0);

		if (gConfig.mBorderlessWindow)
		{
			MoveWindow(hwnd, 0, 0, rcNew.right - rcNew.left, rcNew.bottom - rcNew.top, TRUE);
			return;
		}

		MoveWindow(hwnd, rc.left, rc.top, rcNew.right - rcNew.left, rcNew.bottom - rcNew.top, TRUE);
	}
}