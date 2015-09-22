//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. 
//
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"


extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	//int width = pDoc->getWidth();

	//glPointSize((float)size);
	//glLineWidth((float)width);


	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	float size = pDoc->getSize()/2;
	//int angle = pDoc->getAngle();
	int x1 = target.x;
	int y1 = target.y;
	double opacity = pDoc->getOpac();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_TRIANGLE_FAN);
		SetColorOpac(source,opacity);
		glVertex2f(x1, y1);

		for (float angle = 1.0f; angle<361.0f; angle += 0.2)
		{
			float x2 = x1 + sin(angle)*size;
			float y2= y1 + cos(angle)*size;
			glVertex2f(x2, y2);
		}
	glEnd();
	


	/*

	*/
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* CircleBrush::BrushName(void){

	return ImpBrush::BrushName();
}

