#include "stdafx.h"
#include "Trigonometry.h"

DRAW Draw;
HWND hOption, hMain, hPaint;
WNDPROC oldEditProc;
Point pivot, oriPoint, sinP, coversinP, excscP, cosP, versinP, exsecP, zeroP(0), point;
Line radiusL, tanL, cosL(Point(0), Point(1, 0)), sinL(Point(0), Point(0, 1));
int radius, width, height, optionWidth = 300;
double angle;
bool	isDegree = true,
		calcByAngle = false,
		reCalculate = false;

const int segmentsSize = 11;
struct {
	int checkId;
	Segment segment;
	int editId;
	double (*calcToValue)(double);
	double (*calcToAngle)(double);
} segments[segmentsSize] = {
	{ IDC_CHECK_COS,	Segment("cos", zeroP, cosP, radiusL, 0, XIn, Color.Blue, point, Draw),			IDC_EDIT_COS,		cos,	acos },
	{ IDC_CHECK_VERSIN, Segment("versin", cosP, versinP, cosL, 1, XIn, Color.LightBlue, point, Draw),	IDC_EDIT_VERSIN,	versin,	aversin },
	{ IDC_CHECK_EXSEC,	Segment("exsec", versinP, exsecP, cosL, 2, XIn, Color.Aqua, point, Draw),		IDC_EDIT_EXSEC,		exsec,	aexsec },
	{ IDC_CHECK_SEC,	Segment("sec", zeroP, exsecP, cosL, 3, XOut, Color.DarkBlue, point, Draw),		IDC_EDIT_SEC,		sec,	asec },
	{ IDC_CHECK_SIN,	Segment("sin", zeroP, sinP, radiusL, 0, YIn, Color.Red, point, Draw),			IDC_EDIT_SIN,		sin,	asin },
	{ IDC_CHECK_COVERSIN,	Segment("coversin", sinP, coversinP, sinL, 1, YIn, Color.Pink, point, Draw),	IDC_EDIT_COVERSIN, coversin,	acoversin },
	{ IDC_CHECK_EXCSC,	Segment("excsc", coversinP, excscP, sinL, 2, YIn, Color.Violet, point, Draw),	IDC_EDIT_EXCSC,		excsc,	aexcsc },
	{ IDC_CHECK_COSEC,	Segment("cosec", zeroP, excscP, sinL, 3, YOut, Color.DarkRed, point, Draw),		IDC_EDIT_COSEC,		cosec,	acosec },
	{ IDC_CHECK_TAN,	Segment("tan", point, exsecP, tanL, 0, YIn, Color.Brown, point, Draw),			IDC_EDIT_TAN,		tan,	atan },
	{ IDC_CHECK_COTAN,	Segment("cotan", point, excscP, tanL, 0, YIn, Color.Gold, point, Draw),			IDC_EDIT_COTAN,		cotan,	acotan },
	{ IDC_CHECK_CRD,	Segment("crd", point, versinP, radiusL, 0, YOut, Color.Gray, point, Draw),		IDC_EDIT_CRD,		crd,	acrd },
};

void DrawOut(HWND hWnd) {
	static Point min, max;
	static int length;
	static double degree;
	Draw.Begin(hWnd);
	Draw.Reset();
	Draw.SetPivot(pivot, 1);

	if (reCalculate) {
		if (!calcByAngle) {
			point = Draw.Map(oriPoint);
			radius = (int)Point(0).DistanceFrom(point);
			angle = point.AngleFrom(0);
		} else
			point = Circle(Point(0), radius).GetPointAtAngle(angle);

		// calculate
		min = Draw.Map({ 0, height });
		max = Draw.Map({ width, 0 });
		length = (int)max(point.DistanceFrom(min), point.DistanceFrom(max)) * (point.x > 0 ? 1 : -1);
		cosP = Point(point.x, 0);
		versinP = Point(radius, 0);
		exsecP = versinP + Point(exsec(angle)*radius, 0);
		sinP = Point(0, point.y);
		coversinP = Point(0, radius);
		excscP = coversinP + Point(0, excsc(angle)*radius);
		radiusL.Set(zeroP, point);
		tanL.Set(excscP, exsecP);
		degree = toDegree(angle);
		degree += (degree >= 0 ? 0 : 2 * 180);

		// set edit text
		SetWindowText(GetDlgItem(hOption, IDC_EDIT_ANGLE), String(isDegree ? degree : angle));
		for (int i = 0; i < segmentsSize; i++)
			SetWindowText(GetDlgItem(hOption, segments[i].editId), String(segments[i].calcToValue(angle)));

		//static int i = 0;
		//SetWindowText(GetParent(hWnd), String(point.x) + String(" ") + String(point.y));
	}
	
	// circle
	Draw.SetBackgroundColor(Color.Transparent);
	Draw.Circle(Point(0, 0), radius);
	// cross
	Draw.Line(min.x, 0, max.x, 0);
	Draw.Line(0, min.y, 0, max.y);
	// radius
	Draw.SetLineStyle(LineStyle.Dash);
	Draw.Line(0, radiusL.GetPointAtDistanceFromPoint(length, Point(0)));
	// tan
	Draw.Line(tanL.GetPointAtDistanceFromPoint(length, point), tanL.GetPointAtDistanceFromPoint(-length, point));
	// angle
	Draw.SetLineWidth(3);
	Draw.Arc(0, 25, 0, angle);
	Draw.SetTextAlign(TextAlign.Center);
	Draw.Text(String(isDegree ? degree : angle), Circle(Point(0), 50).GetPointAtAngle(toRadian(degree / 2)));
	
	// draw segments
	for (int i = 0; i < segmentsSize; i++)
		if (IsDlgButtonChecked(hOption, segments[i].checkId) == BST_CHECKED)
			segments[i].segment.DrawOut();

	// point
	Draw.SetBackgroundColor(Color.Black);
	Draw.SetColor(Color.Black);
	Draw.SetLineStyle(LineStyle.Solid);
	Draw.Circle(point, 5);

	Draw.End();
	reCalculate = false;
	calcByAngle = false;
}

const int maxChar = 10;
BOOL CALLBACK EditNumberProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CHAR: {
		TCHAR key, tmp[maxChar + 1];
		String text;
		key = (TCHAR)wParam;
		GetWindowText(hWnd, tmp, maxChar);
		text.SetValue(tmp);
		if ((text.Length() < maxChar) &&
			(
				(key >= '0' && key <= '9') || 
				(key == '.' && (text.Find(".") < 0)) || 
				((key == '-' || key == '+') && !text) ||
				key == VK_BACK
			)
		)
			return CallWindowProc(oldEditProc, hWnd, message, wParam, lParam);
	} break;
	case WM_KEYUP: {
		char key = (char)wParam;
		if (key == VK_RETURN) {
			String text;
			TCHAR tmp[maxChar + 1];
			int id;
			GetWindowText(hWnd, tmp, maxChar);
			text.SetValue(tmp);
			id = GetDlgCtrlID(hWnd);
			if (id == IDC_EDIT_ANGLE) {
				angle = text.ToDouble();
				if (isDegree)
					angle = toRadian(angle);
			} else {
				for (int i = 0; i < segmentsSize; i++)
					if (segments[i].editId == id) {
						angle = segments[i].calcToAngle(text.ToDouble());
						break;
					}
			}
			calcByAngle = true;
			reCalculate = true;
			InvalidateRect(hPaint, NULL, true);
		} else
			return CallWindowProc(oldEditProc, hWnd, message, wParam, lParam);
	} break;
	default:
		return CallWindowProc(oldEditProc, hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK OptionProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_COMMAND: {
		int id = LOWORD(wParam);
		HWND handle = HWND(lParam);
		switch (HIWORD(wParam)) {
		case BN_CLICKED: {
			if (id == IDC_RADIO_DEGREE)
				isDegree = true;
			else if (id == IDC_RADIO_RADIAN)
				isDegree = false;
			reCalculate = true;
			calcByAngle = true;
			InvalidateRect(hPaint, NULL, true);
		}	break;
		default:
			return 0;
		}
	} break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	} break;
	case WM_INITDIALOG: {
		CheckDlgButton(hWnd, IDC_CHECK_COS, BST_CHECKED);
		CheckDlgButton(hWnd, IDC_CHECK_SIN, BST_CHECKED);
		oldEditProc = (WNDPROC)SetWindowLong(GetDlgItem(hWnd, IDC_EDIT_ANGLE), GWLP_WNDPROC, (LONG)EditNumberProc);
		for (int i = 0; i < segmentsSize; i++)
			SetWindowLong(GetDlgItem(hWnd, segments[i].editId), GWLP_WNDPROC, (LONG)EditNumberProc);
	} break;
	default:
		return 0;
	}
	return 1;
}

bool	preCatch = false,
		isCatching = false;
INT_PTR CALLBACK PaintProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static Point preMouse;
	switch (message) {
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawOut(hWnd);
		EndPaint(hWnd, &ps);
	} break;
	case WM_LBUTTONDOWN: {
		if (preCatch) {
			isCatching = true;
			preMouse.x = LOWORD(lParam);
			preMouse.y = HIWORD(lParam);
		}
	} break;
	case WM_LBUTTONUP: {
		if (!isCatching) {
			oriPoint.x = (int)LOWORD(lParam);
			oriPoint.y = (int)HIWORD(lParam);
			reCalculate = true;
			InvalidateRect(hWnd, NULL, true);
			SetFocus(hWnd);
		} else
			isCatching = false;
	}
	break;
	case WM_MOUSEMOVE: {
		if (isCatching) {
			Point mouse(LOWORD(lParam), HIWORD(lParam));
			Point newPivot = pivot;
			newPivot.x += mouse.x - preMouse.x;
			newPivot.y += mouse.y - preMouse.y;
			if (newPivot.x > 25 && newPivot.x < width - 25 && newPivot.y > 25 && newPivot.y < height - 25) {
				pivot = newPivot;
				reCalculate = true;
				calcByAngle = true;
				InvalidateRect(hWnd, NULL, true);
				static int i = 0;
				SetWindowText(GetParent(hWnd), String(i));
			}
			preMouse = mouse;
		}
	} break;
	case WM_KEYDOWN: {
		if ((char)wParam == VK_SPACE) {
			preCatch = true;
		}
	} break;
	case WM_KEYUP: {
		if ((char)wParam == VK_SPACE) {
			preCatch = false;
		}
	} break;
	case WM_SIZE:
	case WM_INITDIALOG: {
		RECT rect;
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		pivot.Set(width / 2, height / 2);
		reCalculate = true;
		calcByAngle = true;
		if (message == WM_SIZE) {
			InvalidateRect(hWnd, NULL, true);
		} else {
			CheckDlgButton(hOption, IDC_RADIO_DEGREE, BST_CHECKED);
			angle = PI / 4;
			radius = min(width, height) / 3 * 2;
		}
	} break;
	default:
		return 0;
	}
	return 1;
}

INT_PTR CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_INITDIALOG:
		hOption = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_OPTION), hWnd, OptionProc);
		hPaint = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PAINT), hWnd, PaintProc);
	case WM_SIZE: {
		RECT rect;
		GetClientRect(hWnd, &rect);
		SetWindowPos(hOption, NULL, rect.right - optionWidth, 0, optionWidth, rect.bottom, SWP_SHOWWINDOW);
		SetWindowPos(hPaint, NULL, 0, 0, rect.right - optionWidth, rect.bottom, SWP_SHOWWINDOW);
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