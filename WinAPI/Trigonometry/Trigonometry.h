#pragma once

#include "resource.h"

class Segment {
public:
	Point &start, &end;
	String word;
	Line &line;
	bool traceToX;
	COLORREF color;
	Point offset = 0;
	UINT textAlign;
	Segment(String word, Point &start, Point &end, Line &line, bool traceToX, COLORREF color, UINT textAlign) :
		start(start),
		end(end),
		word(word),
		line(line),
		traceToX(traceToX),
		color(color),
		offset(Point(0,0)),
		textAlign(textAlign)
	{ }
	void DrawOn(DRAW &Draw) {
		start += offset;
		end += offset;
		Draw.SetLineStyle(LineStyle.Solid);
		Draw.SetLineWidth(3);
		Draw.SetTextAlign(textAlign);
		Draw.SetColor(color);
		Draw.Line(start, end);
		Draw.Text(word, start.MidPointFrom(end));

		Draw.SetLineStyle(LineStyle.Dot);
		Draw.SetLineWidth(1);
		if (traceToX) {
			Draw.Line(start, line.GetPointAtX(start.x));
			Draw.Line(end, line.GetPointAtX(end.x));
		}
		else {
			Draw.Line(start, line.GetPointAtY(start.y));
			Draw.Line(end, line.GetPointAtY(end.y));
		}
	}
};