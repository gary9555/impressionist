//
// ScatteredLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of ImpBrush. 
//
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"

extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	int width = pDoc->getWidth();

	//glPointSize((float)size);
	glLineWidth((float)width);


	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int angle = pDoc->getAngle();
	double opacity = pDoc->getOpac();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	srand(time(0));
	glMatrixMode(GL_MODELVIEW);
	for (int i = 0; i < 4; i++){
		float length = fRand(1, size/2)*2.5;
		float dist = fRand(-size*0.3,size*0.3)*2.5;
		float displacement = fRand(-size*0.75, size*0.75);
		float x1 = source.x+displacement;
		float y1 = source.y+dist;
		glPushMatrix();
			glTranslatef(x1, y1, 0.0);
			glRotatef(angle, 0.0, 0.0, 1.0);
			glTranslatef(-x1, -y1, 0.0);
			glBegin(GL_LINE_STRIP);
			SetColorOpac(Point(x1,y1),opacity);
			glVertex2d(x1 - length*0.75, y1);
			glVertex2d(x1 + length*0.75, y1);
			glEnd();
		glPopMatrix();
	}


	/*

	*/
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* ScatteredLineBrush::BrushName(void){

	return ImpBrush::BrushName();
}

