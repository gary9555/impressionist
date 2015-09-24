//
// LoveBrush.cpp
//
// The implementation of Love Brush. It is a kind of ImpBrush. 
//
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LoveBrush.h"

extern float frand();

LoveBrush::LoveBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LoveBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void LoveBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LoveBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int angle = pDoc->getAngle();
	double opacity = pDoc->getOpac();
	int x1 = target.x;
	int y1 = target.y;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(target.x, target.y, 0.0);
		glRotatef(angle, 0.0, 0.0, 1.0);
		glTranslatef(-target.x, -target.y, 0.0);
	
		glBegin(GL_TRIANGLE_FAN);
			SetColorOpac(source, opacity);
			glVertex2f(x1-size/2, y1+size/2);
			for (float ang = -135.0f; ang<45.2f; ang += 0.2)
			{
				float x2 = x1-size/2 + sin(ang/57.3)*size*0.707;
				float y2 = y1+size/2 + cos(ang/57.3)*size*0.707;
				glVertex2f(x2, y2);
			}
		glEnd();

		glBegin(GL_TRIANGLE_FAN);
			SetColorOpac(source, opacity);
			glVertex2f(x1 + size / 2, y1 + size / 2);
			for (float ang = -45.0f; ang<135.2f; ang += 0.2)
			{
				float x2 = x1 + size / 2 + sin(ang / 57.3)*size*0.707;
				float y2 = y1 + size / 2 + cos(ang / 57.3)*size*0.707;
				glVertex2f(x2, y2);
			}
		glEnd();
	
		glBegin(GL_POLYGON);
			SetColorOpac(source, opacity);
			glVertex2d(target.x, target.y+size);
			glVertex2d(target.x-size, target.y);
			glVertex2d(target.x, target.y-size);
			glVertex2d(target.x+size, target.y);
		glEnd();

	glPopMatrix();
	

}

void LoveBrush::BrushEnd(const Point source, const Point target)
{

}

char* LoveBrush::BrushName(void){

	return ImpBrush::BrushName();
}

