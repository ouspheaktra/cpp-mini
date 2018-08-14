#ifndef WINAPI_H
#define WINAPI_H

#include <windows.h>
#include <math.h>
#include "string.h"
#include "geometry.h"

class COLOR {
public:
	static const COLORREF
		Red = RGB(255, 0, 0),
		DarkRed = RGB(139, 0, 0),

		Green = RGB(0, 255, 0),
		DarkGreen = RGB(0, 100, 0),
		LightGreen = RGB(144, 238, 144),

		Blue = RGB(0, 0, 255),
		DarkBlue = RGB(0, 0, 139),
		LightBlue = RGB(135, 206, 235),

		Pink = RGB(255, 192, 203),
		DeepPink = RGB(255, 20, 147),
		
		Violet = RGB(238, 130, 238),
		DarkViolet = RGB(148, 0, 211),
		Purple = RGB(128, 0, 128),

		Aqua = RGB(0, 255, 255),
		Yellow = RGB(255, 255, 0),
		Gold = RGB(255, 215, 0),
		Brown = RGB(165, 42, 42),
		Gray = RGB(128, 128, 128),
		Black = RGB(0, 0, 0),
		White = RGB(255, 255, 255),
		Transparent = RGB(255, 255, 255) + 1;
	static COLORREF Rgb(unsigned char red, unsigned char green, unsigned char blue) {
		return RGB(red, green, blue);
	}
};
extern COLOR Color;

class TEXTALIGN {
public:
	static const UINT
		Left = TA_LEFT,
		Right = TA_RIGHT,
		Center = TA_CENTER,
		Top = TA_TOP,
		Bottom = TA_BOTTOM,
		BaseLine = TA_BASELINE;
};
extern TEXTALIGN TextAlign;

class LINESTYLE {
public:
	static const UINT
		Solid = PS_SOLID,
		Dash = PS_DASH,
		Dot = PS_DOT,
		DotDash = PS_DASHDOT;
};
extern LINESTYLE LineStyle;

class DRAW {
	HDC hdc;
	COLORREF color, backgroundColor;
	int lineWidth;
	int lineStyle;
	Point pivot;
public:
	short positiveQuadrant;
	DRAW();
	void SetPivot(Point point, short positiveQuadrant=4);

	// draw on specific area
	//void SetArea(Point start, Point end);

	void SetColor(COLORREF color);
	void SetBackgroundColor(COLORREF color);
	void SetLineWidth(int lineWidth);
	void SetLineStyle(int lineStyle);
	void SetTextAlign(UINT textAlign);
	
	HDC GetHDC();

	void Begin(HWND hwnd);
	void Begin(HDC hdc);
	void Reset();
	void End();
	
	Point GetCenter();
	int GetWidth();
	int GetHeight();
	Point GetMin();
	Point GetMax();
	Point Convert(Point point);
	Point Map(Point point);
	
	void Line(int x1, int y1, int x2, int y2);
	void Line(Point point1, Point point2);
	void Circle(int x, int y, int radius);
	void Circle(Point point, int radius);
	void Arc(int x, int y, int radius, double startAngle, double endAngle);
	void Arc(Point point, int radius, double startAngle, double endAngle);
	void Rectangle(int x, int y, int width, int height);
	void Rectangle(Point point, int width, int height);
	void Rectangle(int x, int y, int width, int height, double angle);
	void Rectangle(Point point, int width, int height, double angle);
	void Text(String s, int x, int y);
	void Text(String s, Point point);
	void Image(int RESOURCE_ID, int x, int y);
	void Image(int RESOURCE_ID, Point point);
};

#endif