// Mini Buses.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Mini Buses.h"

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

int random(int from, int to) {
	if (from == to)	return from;
	return from + (rand() % (to - from));
}

int passengersAmount = 0;
Passenger **passengers = NULL;
Passenger *NewPassenger() {
	Passenger **temp = new Passenger*[passengersAmount + 1];
	for (int i = 0; i < passengersAmount; i++)
		temp[i] = passengers[i];
	temp[passengersAmount] = new Passenger;
	delete[] passengers;
	passengers = temp;
	return passengers[passengersAmount++];
}

const int busesAmount = 10;
Bus buses[busesAmount];

const int stopsAmount = 7;
Stop stops[stopsAmount];
Route route;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);



	srand(time(NULL));
	stops[0].SetCoordXY(50, 240);
	stops[1].SetCoordXY(175, 300);
	stops[2].SetCoordXY(300, 400);
	stops[3].SetCoordXY(500, 230);
	stops[4].SetCoordXY(650, 250);
	stops[5].SetCoordXY(800, 300);
	stops[6].SetCoordXY(900, 400);
	// add stop into route
	for (int i = 0; i < stopsAmount; i++) {
		route.AddStop(&stops[i]);
		stops[i].id = i;
	}
	// random buses's seats
	for (int i = 0; i < busesAmount; i++) {
		buses[i].SetSeatAmount(random(10, 20+1));
		buses[i].SetRoute(&route);
	}
	


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MINIBUSES, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIBUSES));

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

	// destroy
	for (int i = 0; i < passengersAmount; i++)
		delete passengers[i];
	delete[] passengers;

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIBUSES));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MINIBUSES);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
DRAW Draw;
double minutes = 0;
int minutesPerPassenger = 10;
int minutesPerBus = 35;
int minutesPerRealSecond = 15;
int minutePassengersStartWaiting[stopsAmount] = { 0 };
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            
			// TODO: Add any Drawing code that uses hdc here...
			Draw.Begin(hdc);

			// Draw paths
			Draw.SetBackgroundColor(RGB(0, 0, 0));
			Draw.SetColor(RGB(0, 0, 0));
			Point prevPoint, curPoint;
			for (int i = 0; i < stopsAmount; i++) {
				if (i == 0) {
					prevPoint.x = 0;
					prevPoint.y = 200;
				}
				curPoint = stops[i].GetCoord();
				Draw.Line(prevPoint.x, prevPoint.y, curPoint.x, curPoint.y);
				Draw.Circle(curPoint.x, curPoint.y, 10);
				prevPoint = curPoint;
			}
			Draw.Line(prevPoint.x, prevPoint.y, prevPoint.x+500, 200);

			// Draw buses
			Point p;
			for (int i = 0; i < busesAmount; i++) {
				if (buses[i].isGoing()) {
					p = buses[i].GetCoord();
					p.x -= 25;
					p.y -= 50;
					Draw.Text(String("seat: ") + String(buses[i].GetSeatAmount()), p.x, p.y - 75);
					Draw.Text(String("available: ") + String(buses[i].GetSeatAmount() - buses[i].GetPassengersAmount()), p.x, p.y - 50);
					Draw.Text(String("passenger: ") + String(buses[i].GetPassengersAmount()), p.x, p.y - 25);
					Draw.Rectangle(p.x, p.y, 50, 25);
				}
			}
			// Draw passengers
			for (int i = 0, j, m; i < stopsAmount; i++) {
				p = stops[i].GetCoord();
				for (j = 0, m = stops[i].GetPassengersAmount(); j < m; j++)
					Draw.Circle(p.x, p.y + (j+1) * 20, 5);
			}
			Draw.End();
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
		switch (wParam) {
			case 1: {
				// passengers're waiting
				for (int i = 0; i < passengersAmount; i++)
					if (passengers[i]->isWaiting())
						passengers[i]->Wait(1);
				// passengers're coming
				int restMinutes = (long)minutes % minutesPerPassenger + 1;
				Passenger *newPassenger;
				for (int i = 0; i < stopsAmount; i++)
					if (minutePassengersStartWaiting[i] == restMinutes) {
						newPassenger = NewPassenger();
						newPassenger->SetDestination(&stops[random(i + 1, stopsAmount)]);
						stops[i].AddPassenger(newPassenger);
					}

				int busId = (int)(minutes / minutesPerBus) - 1;
				// start the bus
				if (busId >= 0 && busId < busesAmount && !buses[busId].isGoing()) {
					buses[busId].Start();
					buses[busId].AtStop();
				}
				// move the bus
				for (int i = 0; i < busesAmount; i++)
					if (buses[i].isGoing())
						buses[i].Move(1.0 / minutesPerBus);

				int allWaitMinutes = 0;
				for (int i = 0; i < passengersAmount; i++)
					allWaitMinutes += passengers[i]->GetWaitMinutes();
				if (passengersAmount > 0)
				SetWindowText(hWnd, String(allWaitMinutes/ passengersAmount));
				
				// if end
				if (!buses[busesAmount - 1].GetNextStop()) {
					KillTimer(hWnd, 1);
					KillTimer(hWnd, 2);
				}
				minutes++;
				InvalidateRect(hWnd, NULL, true);
			} break;
			case 2: {
				int startWaiting = 0,
					stopWaiting = stopsAmount - 1;
				for (int i = 0; i < stopsAmount; i++) {
					if (&stops[i] == buses[busesAmount - 1].GetNextStop())
						startWaiting = i;
					if (&stops[i] == buses[0].GetNextStop())
						stopWaiting = i + 1;
					minutePassengersStartWaiting[i] = -1;
				}
				if (stopWaiting >= stopsAmount - 2)
					stopWaiting = stopsAmount - 2;
				for (int i = startWaiting; i <= stopWaiting; i++)
					minutePassengersStartWaiting[i] = random(1, minutesPerPassenger+1);
			} break;
		}
		break;
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000/minutesPerRealSecond, NULL);
		SetTimer(hWnd, 2, 1000/minutesPerRealSecond*minutesPerPassenger, NULL);
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
