#include <windows.h>

HDC hdc;
HBRUSH	hbrBlack = CreateSolidBrush(RGB(0,0,0)),
		//hbrWhite = CreateSolidBrush(RGB(255,255,255),
		hbrGreen = CreateSolidBrush(RGB(0,255,0));
PAINTSTRUCT ps;
HRGN hrgnOut, hrgnIn;
RECT rect;
TCHAR tmp[100];
int mx, my;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_PAINT: {
			hdc = BeginPaint(hwnd, &ps);
			
			SelectObject(hdc, hbrBlack);
			GetClientRect(hwnd, &rect);
			rect.top += 50;
			rect.left += 50;
			rect.right -= 50;
			rect.bottom -= 50;
			hrgnOut = CreateRectRgn(rect.top, rect.left, rect.right, rect.bottom);
			Rectangle(hdc, rect.top, rect.left, rect.right, rect.bottom);
			
			SelectObject(hdc, hbrGreen);
			rect.top += 10;
			rect.left += 10;
			rect.right -= 10;
			rect.bottom -= 10;
			hrgnIn = CreateRectRgn(rect.top, rect.left, rect.right, rect.bottom);
			Rectangle(hdc, rect.top, rect.left, rect.right, rect.bottom);
			EndPaint(hwnd, &ps);
			return DefWindowProc(hwnd, Message, wParam, lParam);
		}
		
		case WM_LBUTTONDOWN: {
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			if (PtInRegion(hrgnIn, mx, my))
				SetWindowText(hwnd, TEXT("IN"));
			else if (PtInRegion(hrgnOut, mx, my))
				SetWindowText(hwnd, TEXT("ON"));
			else
				SetWindowText(hwnd, TEXT("OUT"));
			break;
		}
		
		case WM_RBUTTONDOWN: {
			GetClientRect(hwnd, &rect);
			wsprintf(tmp, TEXT("Width:%d Height:%d"), rect.right, rect.bottom);
			SetWindowText(hwnd, tmp);
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
		TEXT("--- INSTRUCTION ---\n\nDisplay on Caption about where u click on/in/out of the box"),
		WS_VISIBLE | WS_CHILD, 25, 25, 225, 75, hwnd, NULL, hInstance, 0);

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
