#include "winapi.h"

BOOL (__stdcall *_Rectangle)(HDC, int, int, int, int) = Rectangle;
BOOL (__stdcall *_Arc)(HDC, int, int, int, int, int, int, int, int) = Arc;
UINT (__stdcall *_SetTextAlign)(HDC, UINT) = SetTextAlign;

typedef Circle _Circle;

DRAW::DRAW() {
	positiveQuadrant = 4;
}
void DRAW::SetPivot(Point point, short positiveQuadrant) {
	if (positiveQuadrant < 1 || positiveQuadrant > 4)
		positiveQuadrant = 4;
	this->positiveQuadrant = positiveQuadrant;
	pivot = point;
}

void DRAW::SetColor(COLORREF color) {
	this->color = color;
	SelectObject(hdc, CreatePen(lineStyle, lineWidth, color));
	SetTextColor(hdc, color);
}
void DRAW::SetBackgroundColor(COLORREF color) {
	this->backgroundColor = color;
	if (color == Color.Transparent) {
		SetBkMode(hdc, TRANSPARENT);
		SelectObject(hdc, GetStockObject(NULL_BRUSH));
	} else {
		SetBkMode(hdc, OPAQUE);
		SelectObject(hdc, CreateSolidBrush(color));
	}
}
void DRAW::SetLineWidth(int lineWidth) {
	this->lineWidth = lineWidth;
	SelectObject(hdc, CreatePen(lineStyle, lineWidth, color));
}

void DRAW::SetLineStyle(int lineStyle) {
	this->lineStyle = lineStyle;
	SelectObject(hdc, CreatePen(lineStyle, lineWidth, color));
}

void DRAW::SetTextAlign(UINT textAlign) {
	_SetTextAlign(hdc, textAlign);
}

HDC DRAW::GetHDC() {
	return hdc;
}

void DRAW::Begin(HWND hwnd) {
	return Begin(GetDC(hwnd));
}
void DRAW::Begin(HDC hdc) {
	this->hdc = hdc;
}
void DRAW::Reset() {
	SetColor(Color.Black);
	SetBackgroundColor(Color.White);
	SetLineWidth(1);
	SetLineStyle(PS_SOLID);
}
void DRAW::End() {
	ReleaseDC(WindowFromDC(hdc), hdc);
}

Point DRAW::GetCenter() {
	RECT rect;
	GetClientRect(WindowFromDC(hdc), &rect);
	Point p(rect.right/2, rect.bottom/2);
	return Convert(p);
}

int DRAW::GetWidth() {
	RECT rect;
	GetClientRect(WindowFromDC(hdc), &rect);
	return rect.right;
}

int DRAW::GetHeight() {
	RECT rect;
	GetClientRect(WindowFromDC(hdc), &rect);
	return rect.bottom;
}

Point DRAW::GetMin() {
	switch (positiveQuadrant) {
	case 1:
		return Map({ 0, GetHeight() });
	case 2:
		return Map({ GetWidth(), GetHeight() });
	case 3:
		return Map({ GetWidth(), 0 });
	case 4:
		return Map({ 0, 0 });
	}
}

Point DRAW::GetMax() {
	switch (positiveQuadrant) {
	case 1:
		return Map({ GetWidth(), 0 });
	case 2:
		return Map({ 0, 0 });
	case 3:
		return Map({ 0, GetHeight() });
	case 4:
		return Map({ GetWidth(), GetHeight() });
	}
}

Point DRAW::Convert(Point point) {
	if (!pivot && positiveQuadrant == 4)
		return point;
	switch (positiveQuadrant) {
	case 1:
		point.y = -point.y;
		break;
	case 2:
		point.y = -point.y;
		point.x = -point.x;
		break;
	case 3:
		point.x = -point.x;
	}
	return point + pivot;
}

Point DRAW::Map(Point point) {
	if (!pivot && positiveQuadrant == 4)
		return point;
	switch (positiveQuadrant) {
	case 1:
		point.x = point.x - pivot.x;
		point.y = pivot.y - point.y;
		break;
	case 2:
		point.x = pivot.x - point.x;
		point.y = pivot.y - point.y;
		break;
	case 3:
		point.x = pivot.x - point.x;
		point.y = point.y - pivot.y;
		break;
	case 4:
		point.x = point.x - pivot.x;
		point.y = point.y - pivot.y;
	}
	return point;
}

void DRAW::Line(int x1, int y1, int x2, int y2) {
	Line(Point(x1, y1), Point(x2, y2));
}
void DRAW::Line(Point point1, Point point2) {
	point1 = Convert(point1);
	point2 = Convert(point2);
	MoveToEx(hdc, point1.x, point1.y, NULL);
	LineTo(hdc, point2.x, point2.y);
}
void DRAW::Circle(int x, int y, int radius) {
	Circle(Point(x, y), radius);
}
void DRAW::Circle(Point point, int radius) {
	point = Convert(point);
	Ellipse(hdc, point.x - radius, point.y - radius, point.x + radius, point.y + radius);
}
void DRAW::Arc(int x, int y, int radius, double startAngle, double endAngle) {
	Arc(Point(x, y), radius, startAngle, endAngle);
}
void DRAW::Arc(Point point, int radius, double startAngle, double endAngle) {
	_Circle circle(point, radius);
	Point startPoint = circle.GetPointAtAngle(startAngle);
	Point endPoint = circle.GetPointAtAngle(endAngle);
	point = Convert(point);
	startPoint = Convert(startPoint);
	endPoint = Convert(endPoint);
	_Arc(
		hdc,
		point.x - radius, point.y - radius,
		point.x + radius, point.y + radius,
		startPoint.x, startPoint.y,
		endPoint.x, endPoint.y
	);
}
void DRAW::Rectangle(int x, int y, int width, int height) {
	Rectangle(Point(x, y), width, height);
}
void DRAW::Rectangle(Point point, int width, int height) {
	point = Convert(point);
	_Rectangle(hdc, point.x, point.y, point.x + width, point.y + height);
}
void DRAW::Rectangle(int x, int y, int width, int height, double angle) {
	Rectangle(Point(x, y), width, height, angle);
}
void DRAW::Rectangle(Point point, int width, int height, double angle) {
	point = Convert(point);
	double w = (width / 2) * cos(angle) - (height / 2) * sin(angle);
	double h = (height / 2) * cos(angle) + (width / 2) * sin(angle);
	POINT p[4];
	p[0].x = point.x + w;
	p[0].y = point.y + h;
	p[1].x = point.x - w;
	p[1].y = point.y + h;
	p[2].x = point.x - w;
	p[2].y = point.y - h;
	p[3].x = point.x + w;
	p[3].y = point.y - h;
	Polygon(hdc, p, 4);
}
void DRAW::Text(String s, int x, int y) {
	Text(s, Point(x, y));
}
void DRAW::Text(String s, Point point) {
	point = Convert(point);
	TextOut(hdc, point.x, point.y, s, s.Length());
}
void DRAW::Image(int RESOURCE_ID, int x, int y) {
	Image(RESOURCE_ID, Point(x, y));
}
void DRAW::Image(int RESOURCE_ID, Point point) {
	point = Convert(point);
	HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(RESOURCE_ID));
	BITMAP bitmap;
	GetObject(hBitmap, sizeof(bitmap), &bitmap);

	HDC hdcBitmap = CreateCompatibleDC(hdc);
	SelectObject(hdcBitmap, hBitmap);
	BitBlt(hdc, point.x, point.y, bitmap.bmWidth, bitmap.bmHeight, hdcBitmap, 0, 0, SRCCOPY);
	DeleteDC(hdcBitmap);
	DeleteObject(hBitmap);
}