#include "stdafx.h"
#include "Trigonometry.h"

DRAW Draw;
HWND hOption;
Point oriPoint, sinP, coversinP, excscP, cosP, versinP, exsecP, zeroP, point;
Line radiusL, tanL;
int radius, width, height, optionWidth = 300;
double angle;

const int segmentsSize = 11;
struct {
	int buttonId;
	Segment segment;
} segments[segmentsSize] = {
	{ IDC_CHECK_COS,	Segment("cos", zeroP, cosP, radiusL, true, Color.Blue, TextAlign.Center | TextAlign.Bottom) },
	{ IDC_CHECK_VERSIN, Segment("versin", cosP, versinP, radiusL, true, Color.LightBlue, TextAlign.Center | TextAlign.Bottom) },
	{ IDC_CHECK_EXSEC,	Segment("exsec", versinP, exsecP, radiusL, true, Color.Aqua, TextAlign.Center | TextAlign.Bottom) },
	{ IDC_CHECK_SEC,	Segment("sec", zeroP, exsecP, radiusL, true, Color.DarkBlue, TextAlign.Center | TextAlign.Top) },
	{ IDC_CHECK_SIN,	Segment("sin", zeroP, sinP, radiusL, false, Color.Red, TextAlign.Left) },
	{ IDC_CHECK_COVERSIN,	Segment("coversin", sinP, coversinP, radiusL, false, Color.Pink, TextAlign.Left) },
	{ IDC_CHECK_EXCSC,	Segment("excsc", coversinP, excscP, radiusL, false, Color.Violet, TextAlign.Left) },
	{ IDC_CHECK_COSEC,	Segment("cosec", zeroP, excscP, radiusL, false, Color.DarkRed, TextAlign.Right) },
	{ IDC_CHECK_TAN,	Segment("tan", point, exsecP, tanL, false, Color.Brown, TextAlign.Left | TextAlign.Bottom) },
	{ IDC_CHECK_COTAN,	Segment("cotan", point, excscP, tanL, false, Color.Gold, TextAlign.Left | TextAlign.Bottom) },
	{ IDC_CHECK_CRD,	Segment("crd", point, versinP, radiusL, false, Color.Gray, TextAlign.Right | TextAlign.Top) },
};

void DrawOut(HWND hWnd) {
	static Point pivot, min, max;
	static int length;
	pivot.Set(width / 2, height / 2);
	Draw.Begin(hWnd);
	Draw.Reset();
	Draw.SetPivot(pivot, 1);

	if (oriPoint.x < 0) {
		oriPoint.x *= -1;
		oriPoint.y *= -1;
		point = Draw.Map(oriPoint);
		radius = Point(0).DistanceFrom(point);
		angle = point.AngleFrom(0);
	}

	// calculate
	min = Draw.Map({ 0, height });
	max = Draw.Map({ width, 0 });
	length = max(point.DistanceFrom(min), point.DistanceFrom(max)) * (point.x > 0 ? 1 : -1);
	cosP = Point(point.x, 0);
	versinP = Point(radius, 0);
	exsecP = versinP + Point(exsec(angle)*radius, 0);
	sinP = Point(0, point.y);
	coversinP = Point(0, radius);
	excscP = coversinP + Point(0, excsc(angle)*radius);
	
	// circle
	Draw.SetBackgroundColor(Color.Transparent);
	Draw.Circle(Point(0, 0), radius);
	// cross
	Draw.Line(min.x, 0, max.x, 0);
	Draw.Line(0, min.y, 0, max.y);
	// radius
	Draw.SetLineStyle(LineStyle.Dot);
	radiusL.Set(zeroP, point);
	Draw.Line(0, radiusL.GetPointAtDistanceFromPoint(length, Point(0)));
	// tan
	tanL.Set(point, exsecP);
	Draw.Line(tanL.GetPointAtDistanceFromPoint(length, point), tanL.GetPointAtDistanceFromPoint(-length, point));
	// angle
	Draw.SetLineWidth(3);
	Draw.Arc(0, 25, 0, angle);
	
	// draw segments
	for (int i = 0; i < segmentsSize; i++)
		if (IsDlgButtonChecked(hOption, segments[i].buttonId) == BST_CHECKED)
			segments[i].segment.DrawOn(Draw);

	// point
	Draw.SetBackgroundColor(Color.Black);
	Draw.SetColor(Color.Black);
	Draw.SetLineStyle(LineStyle.Solid);
	Draw.Circle(point, 5);

	Draw.End();
}

BOOL CALLBACK OptionProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: {
		switch (HIWORD(wParam)) {
		case BN_CLICKED:
			InvalidateRect(GetParent(hWnd), NULL, true);
			break;
		default:
			return 0;
		}
	} break;
	default:
		return 0;
	}
	return 1;
}

BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawOut(hWnd);
		EndPaint(hWnd, &ps);
	} break;
	case WM_LBUTTONUP:
		oriPoint.x = - (int)LOWORD(lParam);
		oriPoint.y = - (int)HIWORD(lParam);
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_SIZE:
	case WM_INITDIALOG: {
		RECT rect;
		GetClientRect(hWnd, &rect);
		width = rect.right - optionWidth;
		height = rect.bottom;
		if (!hOption)
			hOption = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_OPTION), hWnd, OptionProc);
		SetWindowPos(hOption, NULL, rect.right - optionWidth, 0, optionWidth, rect.bottom, SWP_SHOWWINDOW);
		if (message == WM_SIZE) {
			InvalidateRect(GetParent(hWnd), NULL, true);
		} else {
			oriPoint.x = -width / 4 * 3;
			oriPoint.y = -height / 4;
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
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, WndProc);
}