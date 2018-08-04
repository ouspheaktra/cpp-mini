// WinAPI.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Test.h"

DRAW Draw;

BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Draw.Begin(hdc);

		Point point(100, 100);

		Draw.SetBackgroundColor(Color.Red);
		Draw.Circle(point, 15);

		Draw.SetBackgroundColor(Color.Aqua);
		Draw.Circle(200, 200, 10);

		Draw.SetPivot(Point(200, 200), 3);
		Draw.SetBackgroundColor(Color.Blue);
		Draw.Circle(Draw.Convert(point), 5);

		SetWindowText(hWnd, String(Draw.Convert(point).x) + String(" ") + String(Draw.Convert(point).y));

		Draw.End();
		EndPaint(hWnd, &ps);
	} break;
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		switch (wmId) {
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return 0;
		}
	} break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return 0;
	}
	return 1;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WndProc);
}