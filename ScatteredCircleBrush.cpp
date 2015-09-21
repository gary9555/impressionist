//
// ScatteredCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush. 
//
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	//int width = pDoc->getWidth();

	//glPointSize((float)size);
	//glLineWidth((float)width);


	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize() / 2;
	//int angle = pDoc->getAngle();

	
	
	srand(time(0));
	for (int i = 0; i < 4; i++){	
		glBegin(GL_TRIANGLE_FAN);			
				double dist = fRand(0,size);
				double ang = fRand(0, 359);
				float x1 = source.x + sin(ang)*size;
				float y1 = source.y + cos(ang)*size;
				SetColor(Point(x1,y1));
				glVertex2f(x1, y1);
				for (float angle = 1.0f; angle < 361.0f; angle += 0.2)
				{
					float x2 = x1 + sin(angle)*size;
					float y2 = y1 + cos(angle)*size;
					glVertex2f(x2, y2);
				}	
		glEnd();
	}

	/*

	*/
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* ScatteredCircleBrush::BrushName(void){

	return ImpBrush::BrushName();
}

