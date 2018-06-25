#include <windows.h>

int maxx = GetSystemMetrics(SM_CXSCREEN),
	maxy = GetSystemMetrics(SM_CYSCREEN),
	width, height, left, top,
	dir = 0,	// direction: left-to-right is 0, top-to-bottom is 1, right-to-left is 2, bottom-to-top is 3
	stepSize = 10;
	
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_KEYUP: {
			switch (wParam) {
				case VK_RETURN: {
					RECT rect;
					GetWindowRect(hwnd, &rect);
					left = rect.left;
					top = rect.top;
					width = rect.right - rect.left;
					height = rect.bottom - rect.top;
					SetTimer(hwnd, 1, 100, NULL);
					break;
				}
				case VK_ESCAPE: {
					KillTimer(hwnd, 1);
					break;
				}
			}
		}
		
		case WM_TIMER: {
			if (wParam == 1) {
				switch (dir) {
					case 0:
						left += stepSize;
						if (width + left >= maxx)
							dir = 1;
							break;
					case 1:
						top += stepSize;
						if (height + top >= maxy)
							dir = 2;
						break;
					case 2:
						left -= stepSize;
						if (left <= 0)
							dir = 3;
						break;
					case 3:
						top -= stepSize;
						if (top <= 0)
							dir = 0;
						break;
				}
				SetWindowPos( hwnd, NULL, left, top, width, height, NULL );
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
		TEXT("--- INSTRUCTION ---\n\nMove Current Window around, when hit Enter. Esc to stop"),
		WS_VISIBLE | WS_CHILD, 25, 25, 300, 300, hwnd, NULL, hInstance, 0);

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
