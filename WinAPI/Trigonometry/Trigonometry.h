#pragma once

#include "resource.h"

class SEGMENTPOS {
public:
	static const int
		X = 1,
		Y = 0,
		In = 2,
		Out = 0;
};
#define XIn		SEGMENTPOS::X | SEGMENTPOS::In
#define XOut	SEGMENTPOS::X | SEGMENTPOS::Out
#define	YIn		SEGMENTPOS::Y | SEGMENTPOS::In
#define YOut	SEGMENTPOS::Y | SEGMENTPOS::Out

class Segment {
public:
	Point &start, &end, &point;
	String word;
	Line &line;
	int pos;
	COLORREF color;
	int offset;
	UINT ta;
	DRAW &Draw;
	Segment(String word, Point &start, Point &end, Line &line, int offset, int pos, COLORREF color, Point &point, DRAW &draw) :
		start(start),
		end(end),
		word(word),
		line(line),
		pos(pos),
		color(color),
		offset(offset),
		point(point),
		Draw(draw)
	{ }
	void DrawOut() {
		Point startP = start;
		Point endP = end;
		bool isX = pos & SEGMENTPOS::X;
		bool isIn = pos & SEGMENTPOS::In;
		UINT textAlign = TextAlign.Right;
		String string = word;
		Draw.SetLineStyle(LineStyle.Solid);
		Draw.SetLineWidth(3);
		if (isX) {
			Point offsetP = Point(0, 15 * offset);
			textAlign = TextAlign.Center;
			if (point.y >= 0) {
				offsetP.y *= -1;
				textAlign |= (isIn ? TextAlign.Bottom : TextAlign.Top);
			} else {
				textAlign |= (isIn ? TextAlign.Top : TextAlign.Bottom);
			}
			startP += offsetP;
			endP += offsetP;
		} else {
			Point offsetP = Point(15 * offset, 0);
			if (point.x >= 0) {
				offsetP.x *= -1;
				textAlign = (isIn ? TextAlign.Left : TextAlign.Right);
				string = (isIn ? String(" ") + string : string + String(" "));
			} else {
				textAlign = (isIn ? TextAlign.Right : TextAlign.Left);
				string = (isIn ? string + String(" ") : String(" ") + string);
			}
			startP += offsetP;
			endP += offsetP;
		}
		Draw.SetTextAlign(textAlign);
		Draw.SetColor(color);
		Draw.Line(startP, endP);
		Draw.Text(string, startP.MidPointFrom(endP));

		Draw.SetLineStyle(LineStyle.Dot);
		Draw.SetLineWidth(1);
		if (isX) {
			Draw.Line(startP, line.GetPointAtX(startP.x));
			Draw.Line(endP, line.GetPointAtX(endP.x));
		} else {
			Draw.Line(startP, line.GetPointAtY(startP.y));
			Draw.Line(endP, line.GetPointAtY(endP.y));
		}
	}
};