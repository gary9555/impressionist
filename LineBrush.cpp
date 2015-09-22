//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. 
//
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	
	int width = pDoc->getWidth();

	//glPointSize((float)size);
	glLineWidth((float)width);
	
	
	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
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
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glTranslatef(target.x, target.y, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glTranslatef(-target.x, -target.y, 0.0);
		glBegin(GL_LINE_STRIP);
			SetColorOpac(source,opacity);	
			glVertex2d(target.x - size / 2, target.y);
			glVertex2d(target.x + size / 2, target.y);
		glEnd();
	glPopMatrix();
		
	
	/*
	
	*/
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* LineBrush::BrushName(void){

	return ImpBrush::BrushName();
}

