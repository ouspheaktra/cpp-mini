#include <windows.h>
#include <tchar.h>
#include <stdlib.h>

HWND pa, hCaption, hNewCaption, global;
HDC hdc;
HBRUSH hbr = CreateSolidBrush(RGB(255,0,0));

HWND *w = new HWND[100];
int ws = 0, wi = 0;		// ws: window [] size,	wi: window [] index

TCHAR caption[100], tmp[100];
RECT wr, wwr;

BOOL CALLBACK enumChild( HWND hwnd, LPARAM lParam ) {
	GetClassName(hwnd, caption, 100);
	if (_tcscmp(caption, TEXT("Button")) == 0) {
		w[ws++] = hwnd;
		if (ws == 100)
			return false;
	}
	return true;
}
bool findWindow() {
	GetWindowText(hCaption, caption, 100);
	pa = FindWindow(NULL, caption);
	if (pa)	return true;
	wsprintf(tmp, TEXT("%s is not opened"), caption);
	MessageBox(global, tmp, TEXT("NOT FOUND"), MB_OK);
	return false;
}
bool collectButtons() {
	if (!findWindow()) return false;
	// get all button
	EnumChildWindows(pa, enumChild, 0);
	// shuffle button
	HWND wt;
	for (int i = ws-1, t; i != 0; i--) {
		t = rand()%i;
		wt = w[t];
		w[t] = w[i];
		w[i] = wt;
	}
	return (ws != 0);			
}
void hideButton() {				
	ShowWindow(w[wi], 0);
	wsprintf(tmp, TEXT("%d"), wi);
	SetWindowText(global, tmp);
	/* FAILED TEST	:	redraw only where button is
	GetWindowRect(pa, &wwr);
	GetWindowRect(w[wi], &wr);
	wr.left -= wwr.left;
	wr.top -= wwr.top;
	wr.right -= wwr.left;
	wr.bottom -= wwr.top;
	InvalidateRect(pa, &wr, true);*/
	InvalidateRect(pa, NULL, false);
	wi++;
}
void showButton() {
	if (--wi < 0)	wi = 0;
	else {
		ShowWindow(w[wi], 1);
		InvalidateRect(pa, NULL, false);	
	}
}
void setCaption() {
	if (!findWindow())	return;
	GetWindowText(hNewCaption, tmp, 100);
	SetWindowText(pa, tmp);
}
	
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	global = hwnd;
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_LBUTTONDOWN: {
			SetFocus(hwnd);
			break;
		}
		
		case WM_KEYUP: {
			switch (wParam) {
				case VK_RETURN: {
					ws <= 0 && collectButtons();
					SetTimer(hwnd, 1, 1500, NULL);
					break;
				}
				case VK_ESCAPE: {
					KillTimer(hwnd, 1);
					break;
				}
				case VK_UP: {
					KillTimer(hwnd, 1);
					ws <= 0 && collectButtons();
					hideButton();
					break;
				}
				case VK_DOWN: {
					KillTimer(hwnd, 1);
					ws <= 0 && collectButtons();
					showButton();
					break;
				}
			}
		}
		
		case WM_TIMER: {
			if (wParam == 1) {
				if (wi >= ws)
					KillTimer(hwnd, 1);
				else
					hideButton();
			}
			break;
		}
		
		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case 2: setCaption(); break;
			}
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
	
	CreateWindowEx(NULL, TEXT("STATIC"),
		TEXT("--- INSTRUCTION ---\n\n\
Hide buttons in a window which has a caption specified in the textbox on ur right-hand side.\n\n\
ENTER:	hide one button every one second\n\n\
ESC:	stop hiding\n\n\
UP:	hide one\n\n\
DOWN:	restore one\n\n\
		"),
		WS_VISIBLE | WS_CHILD, 25, 25, 300, 300, hwnd, NULL, hInstance, 0);

	hCaption = CreateWindowEx(NULL, TEXT("EDIT"),
		TEXT("Calculator"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 400, 75, 200, 25, hwnd, NULL, hInstance, 0);
	hNewCaption = CreateWindowEx(NULL, TEXT("EDIT"),
		TEXT("New Caption"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 400, 150, 200, 25, hwnd, NULL, hInstance, 0);
	CreateWindowEx(NULL, TEXT("BUTTON"),
		TEXT("Set Caption"),
		WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 400, 175, 100, 25, hwnd, (HMENU)2, hInstance, 0);

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
