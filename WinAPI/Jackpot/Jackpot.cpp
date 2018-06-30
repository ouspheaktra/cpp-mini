// Jackpot.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Jackpot.h"
#include "resource.h"
#include <cstdlib>
#include <ctime>
#include "..\..\classes\winapi.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	srand(time(NULL));

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_JACKPOT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JACKPOT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JACKPOT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_JACKPOT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
double random(double from, double to) {
	return from + (rand() / (RAND_MAX / (to - from)));
}
void SetWindowTextNum(HWND hWnd, double num) {
	TCHAR t[20];
	_stprintf_s(t, TEXT("%f"), num);
	SetWindowText(hWnd, t);
}
class Slot {
	int IDB[20];
	int size;
	HDC hdc;
	HWND hWnd;
	int id;
	bool spinning;
	int spinTo;
	double spinId;
	double spinSpeed;
public:
	Slot() {
		id = 0;
		spinId = 0;
		size = 0;
		spinning = false;
	}
	~Slot() {
		DeleteObject(hdc);
	}
	void SetHWND(HWND hWnd) {
		this->hWnd = hWnd;
		GetHDC();
	}
	int GetId() {
		return id;
	}
	HDC GetHDC() {
		if (hdc)	return hdc;
		HDC hdcWindow = GetDC(hWnd);
		HBITMAP hbmWindow = CreateCompatibleBitmap(hdcWindow, 200, 200 * (size + 3));
		hdc = CreateCompatibleDC(hdcWindow);
		SelectObject(hdc, hbmWindow);
		Draw draw;
		draw.Begin(hdc);
		for (int i = 0, n = size + 3; i < n; i++)
			draw.Image(IDB[i < size ? i : i-size], 0, 200 * i);
		draw.End();
		DeleteObject(hbmWindow);
		ReleaseDC(hWnd, hdcWindow);
		return hdc;
	}
	bool isSpinning() {
		return spinning;
	}

	void AddIDB(int IDB) {
		this->IDB[size++] = IDB;
	}
	void DrawOn(HDC hdc, int x, int y) {
		double _spinId = spinId;
		while (_spinId >= size)
			_spinId -= size;
		if (_spinId < 0.5)
			_spinId += size;
		BitBlt(hdc, x, y, 200, 400, this->GetHDC(), 0, 200 * _spinId - 100, SRCCOPY);
	}

	void PreSpin() {
		spinId = id;
		id = (int)random(0, (float)size - 0.1);
		spinSpeed = random(0.25, 0.75);
		spinTo = spinId + (int)random(2, 4)*(size);
		spinning = true;
	}
	void Spin(HDC hdc, int x, int y) {
		if (!isSpinning())	return;
		spinId += spinSpeed;
		if (spinId >= spinTo) {
			spinId = spinTo;
			spinning = false;
		}
		DrawOn(hdc, x, y);
	}
};

Slot slot1, slot2, slot3;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: {
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case 1:
			slot1.PreSpin();
			slot2.PreSpin();
			slot3.PreSpin();
			SetTimer(hWnd, 1, 50, NULL);
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_TIMER:
		if (wParam == 1) {
			HDC hdc = GetDC(hWnd);
			slot1.Spin(hdc, 25, 25);
			slot2.Spin(hdc, 325, 25);
			slot3.Spin(hdc, 625, 25);
			if (!slot1.isSpinning() && !slot2.isSpinning() && !slot3.isSpinning()) {
				KillTimer(hWnd, 1);
				TCHAR t[100];
				_stprintf_s(t, TEXT("%d %d %d"), slot1.GetId(), slot2.GetId(), slot3.GetId());
				SetWindowText(hWnd, t);
			}
			ReleaseDC(hWnd, hdc);
		}
		break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		slot1.DrawOn(hdc, 25, 25);
		slot2.DrawOn(hdc, 325, 25);
		slot3.DrawOn(hdc, 625, 25);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE:
		CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("SPIN"), WS_VISIBLE|SS_CENTER|WS_CHILD, 850, 100, 100, 30, hWnd, (HMENU)1, NULL, NULL);
		slot1.AddIDB(IDB_APPLE);
		slot1.AddIDB(IDB_BANANA);
		slot1.AddIDB(IDB_CHERRY);
		slot1.AddIDB(IDB_ORANGE);
		slot1.AddIDB(IDB_PINEAPPLE);
		slot1.AddIDB(IDB_SERRY);
		slot1.AddIDB(IDB_STRAWBERRY);
		slot1.AddIDB(IDB_WATERMELON);
		slot1.SetHWND(hWnd);
		slot2 = slot1;
		slot3 = slot1;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
