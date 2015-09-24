//
// LoveBrush.h
//
// The header file for Line Brush. 
//

#ifndef LOVEBRUSH_H
#define LOVEBRUSH_H

#include "ImpBrush.h"

class LoveBrush : public ImpBrush
{
public:
	LoveBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

	static bool isRightMouse;    // false: left mouse event ;  true: right mouse event 

};

#endif