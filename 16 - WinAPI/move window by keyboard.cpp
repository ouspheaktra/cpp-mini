#include <windows.h>

RECT rect;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		case WM_KEYDOWN: {
			switch (wParam) {
				case VK_RETURN: {
					SetWindowPos(hwnd, NULL, 0, 0, 300, 300, NULL);
					break;
				}
				case VK_LEFT: {
					GetWindowRect(hwnd, &rect);
					SetWindowPos(hwnd, NULL, rect.left-5, rect.top, rect.right-rect.left, rect.bottom-rect.top, NULL);
					break;
				}
				case VK_RIGHT: {
					GetWindowRect(hwnd, &rect);
					SetWindowPos(hwnd, NULL, rect.left+5, rect.top, rect.right-rect.left, rect.bottom-rect.top, NULL);
					break;
				}
				case VK_UP: {
					GetWindowRect(hwnd, &rect);
					SetWindowPos(hwnd, NULL, rect.left, rect.top-5, rect.right-rect.left, rect.bottom-rect.top, NULL);
					break;
				}
				case VK_DOWN: {
					GetWindowRect(hwnd, &rect);
					SetWindowPos(hwnd, NULL, rect.left, rect.top+5, rect.right-rect.left, rect.bottom-rect.top, NULL);
					break;
				}
			}
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
		TEXT("--- INSTRUCTION ---\n\nMove Current Window by UP, DOWN, LEFT, RIGHT key"),
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
