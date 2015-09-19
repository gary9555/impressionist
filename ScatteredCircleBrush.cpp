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


	int width = pDoc->getWidth();

	//glPointSize((float)size);
	glLineWidth((float)width);


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

	int size = pDoc->getSize();
	int angle = pDoc->getAngle();


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(source.x, source.y, 0.0);
	glRotatef(angle, 0.0, 0.0, 1.0);
	glTranslatef(-source.x, -source.y, 0.0);
	glBegin(GL_LINE_STRIP);
	SetColor(source);
	glVertex2d(source.x - size / 2, source.y);
	glVertex2d(source.x + size / 2, source.y);
	glEnd();
	glPopMatrix();


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

