#include <windows.h>
#include "..\..\classes\time.h"
#include "..\..\classes\string.h"
#include "..\..\classes\winapi.h"
#include "..\..\classes\geometry.h"

Time t;
Draw draw;//

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_TIMER: {
			if (wParam == 1) {
				t.SetNow();
				InvalidateRect(hwnd, NULL, false);
			}
			break;
		}
		
		case WM_PAINT: {
			draw.SetWindow(hwnd);
			HDC hdc = draw.GetHDC();
			POINT center = draw.GetCenter();
			
			draw.Circle(center.x, center.y, 150);
			
			Circle co(center.x, center.y, 145);
			Circle cs(center.x, center.y, 138);
			Circle cl(center.x, center.y, 125);
			Circle ct(center.x, center.y, 115);
			SetTextAlign(hdc, TA_CENTER);
			for (int deg = 270, s = 0; deg < 270+360; deg += 360/60, s++) {
				POINT 	p1 = co.GetPointAtDegree(deg),
						p2 = (s % 5 ? cs : cl).GetPointAtDegree(deg);
				draw.Line(p1.x, p1.y, p2.x, p2.y);
				if (s % 15 == 0) {
					int n = s/5;
					if (n == 0)	n = 12;
					String str(n);
					POINT pt = ct.GetPointAtDegree(deg);
					TextOut(hdc, pt.x, pt.y, str, str.Length());
				}
			}
			
			POINT	ph = Circle(center.x, center.y, 80).GetPointAtDegree(360/12*t.GetHour() + 270),
					pm = Circle(center.x, center.y, 110).GetPointAtDegree(360/60*t.GetMinute() + 270),
					ps = cl.GetPointAtDegree(360/60*t.GetSecond() + 270);
					
			draw.SetWidth(2);		
			draw.Line(center.x, center.y, ps.x, ps.y);
			draw.SetWidth(3);
			draw.Line(center.x, center.y, pm.x, pm.y);
			draw.SetWidth(6);
			draw.Line(center.x, center.y, ph.x, ph.y);
			
			return DefWindowProc(hwnd, Message, wParam, lParam);
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Caption",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
	t.SetNow();
	SetTimer(hwnd, 1, 1000, NULL);

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
