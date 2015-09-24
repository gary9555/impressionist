//
// LineBrush.h
//
// The header file for Line Brush. 
//

#ifndef FILTERBRUSH_H
#define FILTERBRUSH_H

#include "ImpBrush.h"

class FilterBrush : public ImpBrush
{
public:
	FilterBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
	void Blur(const Point source, double opacity);
	void Sharpen(const Point source, double opacity);
	static bool isBlur;
};

#endif