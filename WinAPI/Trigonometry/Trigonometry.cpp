#include "stdafx.h"
#include "Trigonometry.h"

DRAW Draw;
Point point;
int width, height;

void DrawSegment(String word, Point start, Point end, COLORREF color, Point offset = 0, UINT textAlign=TextAlign.Center|TextAlign.Bottom) {
	start += offset;
	end += offset;
	Draw.SetTextAlign(textAlign);
	Draw.SetColor(color);
	Draw.Line(start, end);
	Draw.Text(word, start.MidPointFrom(end));
}

void Drawwing(HWND hWnd) {
	static double angle;
	static int radius;
	static Point start, end, middle, pointOnCircle;
	static const Point
		toLeft = Point(-5, 0),
		toRight = Point(5, 0),
		toUp = Point(0, 5),
		toDown = Point(0, -5);
	Draw.Begin(hWnd);
	Draw.Reset();
	Draw.SetPivot(Point(width / 2, height / 2), 1);

	point = Draw.Map(point);
	radius = Point(0).DistanceFrom(point);
	angle = point.AngleFrom(0);
	pointOnCircle = Circle(0, radius).GetPointAtAngle(angle);
	
	// circle
	Draw.Circle(Point(0, 0), radius);
	// cross
	Draw.Line(-width / 2, 0, width / 2, 0);
	Draw.Line(0, -height / 2, 0, height / 2);
	// point
	Draw.SetBackgroundColor(Color.Black);
	Draw.Circle(point, 5);
	// center to point, infinite
	end = Circle(0, width / 1.5).GetPointAtAngle(angle);
	Draw.SetLineStyle(LineStyle.Dot);
	Draw.Line(0, end);

	// setup for lines
	Draw.SetBackgroundColor(Color.Transparent);
	Draw.SetLineWidth(3);

	// angle
	Draw.Arc(0, 25, 0, angle);
	
	DrawSegment("cos",
		0,
		Point(point.x, 0),
		Color.Blue, 0
	);
	DrawSegment("versin",
		Point(radius, 0),
		Point(radius - radius * (1 - cos(angle)), 0),
		Color.LightBlue, toDown * 2
	);
	DrawSegment("exsec",
		Point(radius, 0),
		Point(radius * (1 / cos(angle)), 0),
		Color.Aqua, toDown * 4
	);
	DrawSegment("sec",
		0,
		Point(radius * (1 / cos(angle)), 0),
		Color.DarkBlue, toDown * 6, TextAlign.Center | TextAlign.Top
	);
	
	DrawSegment(" sin",
		0,
		Point(0, point.y),
		Color.Red, 0, TextAlign.Left
	);
	DrawSegment(" coversin",
		Point(0, radius),
		Point(0, radius - radius * (1 - sin(angle))),
		Color.Pink, toLeft * 2, TextAlign.Left
	);
	DrawSegment(" excsec",
		Point(0, radius),
		Point(0, radius * (1 / sin(angle))),
		Color.Violet, toLeft * 4, TextAlign.Left
	);
	DrawSegment("cosec ",
		0,
		Point(0, radius * (1 / sin(angle))),
		Color.DarkRed, toLeft * 6, TextAlign.Right
	);
	
	DrawSegment(" tan",
		pointOnCircle,
		Point(radius * (1 / cos(angle)), 0),
		Color.Brown, 0, TextAlign.Left | TextAlign.Bottom
	);
	DrawSegment(" cotan",
		pointOnCircle,
		Point(0, radius * (1 / sin(angle))),
		Color.Gold, 0, TextAlign.Left | TextAlign.Bottom
	);
	DrawSegment("crd ",
		pointOnCircle,
		Point(radius, 0),
		Color.Gray, 0, TextAlign.Right | TextAlign.Top
	);

	Draw.End();
}

BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		Drawwing(hWnd);
		EndPaint(hWnd, &ps);
	} break;
	case WM_LBUTTONDOWN:
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_SIZE:
	case WM_INITDIALOG:
		RECT rect;
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		point.x = width - 50;
		point.y = height / 2 - 50;
		break;
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
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, WndProc);
}