#pragma once

namespace hook
{
	void __fastcall SetWindow(int w, int h)
	{
		auto hwnd = SDK_VAR_GET(HWND, 0x249CDF0);

		RECT rc;
		GetWindowRect(hwnd, &rc);

		RECT rcNew = { 0, 0, w, h };
		AdjustWindowRectEx(&rcNew, (Render::IsFullscreen() ? 0 : (WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)), FALSE, 0);
		MoveWindow(hwnd, rc.left, rc.top, rcNew.right - rcNew.left, rcNew.bottom - rcNew.top, TRUE);
	}
}