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

static Point prev(-1, -1);
static Point current(-1, -1);
bool LineBrush::isRightMouse = false;

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	
	int width = pDoc->getWidth();

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
	int strokeDirChoice = dlg->m_StrokeDirChoice->value();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	
		
	switch (strokeDirChoice){
	
	// Slider/Right mouse 
	case 0:
		// don't have to change size and angle value
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glTranslatef(target.x, target.y, 0.0);
			glRotatef(angle, 0.0, 0.0, 1.0);
			glTranslatef(-target.x, -target.y, 0.0);
			glBegin(GL_LINE_STRIP);
				SetColorOpac(source, opacity);
				glVertex2d(target.x - size / 2, target.y);
				glVertex2d(target.x + size / 2, target.y);
			glEnd();
		glPopMatrix();
		break;
	
	// Gradient
	case 1:
		// change angle value according to 
		// the gradient at this point
		double Gx;
		double Gy;
		GLubyte color[3][3][3];
		double intensity[3][3];
		for (int i = -1; i < 2; i++){
			for (int j = -1; j < 2; j++){
				memcpy(color[i+1][j+1], pDoc->GetOriginalPixel(Point(source.x + i, source.y + j)), 3);
				intensity[i + 1][j + 1] = 0.299*color[i + 1][j + 1][0] + 0.587*color[i + 1][j + 1][1] + 0.144*color[i + 1][j + 1][2];
			}
		}
		Gx = intensity[0][0] * (-1) + intensity[0][1] * (-2) + intensity[0][2] * (-1)\
				  + intensity[2][0] * (1) + intensity[2][1] * (2) + intensity[2][2] * (1);
		Gy = intensity[0][0] * (-1) + intensity[1][0] * (-2) + intensity[2][0] * (-1)\
			+ intensity[0][2] * (1) + intensity[1][2] * (2) + intensity[2][2] * (1);
		angle = -(int)(atan2(Gy, Gx)*57.32) % 360;
		
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glTranslatef(target.x, target.y, 0.0);
			glRotatef(angle, 0.0, 0.0, 1.0);
			glTranslatef(-target.x, -target.y, 0.0);
			glBegin(GL_LINE_STRIP);
				SetColorOpac(source, opacity);
				glVertex2d(target.x - size / 2, target.y);
				glVertex2d(target.x + size / 2, target.y);
			glEnd();
		glPopMatrix();
		break;
	
	// Brush direction
	case 2:
		current.x = target.x;
		current.y = target.y;
		if (prev.x!=-1&&current.x!=-1&&(current.x != prev.x || current.y != prev.y)){
			int dx = current.x - prev.x;
			int dy = current.y - prev.y;
			angle = (int)(atan2(dy, dx)*57.32) % 360;

			
		
			glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				glTranslatef(target.x, target.y, 0.0);
				glRotatef(angle, 0.0, 0.0, 1.0);
				glTranslatef(-target.x, -target.y, 0.0);
				glBegin(GL_LINE_STRIP);
					SetColorOpac(source, opacity);
					glVertex2d(target.x - size / 2, target.y);
					glVertex2d(target.x + size / 2, target.y);
				glEnd();
			glPopMatrix();
		}
		prev.x = current.x;
		prev.y = current.y;
		break;

	default:
		break;

	}

	
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int strokeDirChoice = dlg->m_StrokeDirChoice->value();
	
	// values useful for the right mouse drag
	int dx = target.x - source.x;
	int dy = target.y - source.y;
	int size = sqrt(dx*dx + dy*dy);
	int angle = -(int)(atan2(dy, dx)*57.32) % 360;
	
	switch(strokeDirChoice){  
	//  slider/right mouse mode
	case 0: 	
		if (isRightMouse){
			dlg->setAngle(angle);
			dlg->setSize(size);
		}
		break;
	
	// gradient mode: do nothing
	case 1:   
		if (isRightMouse){
			dlg->setSize(size);
		}
		break;
	
	// brush direction mode
	case 2:  
		if (!isRightMouse){
			prev.x = -1;
			prev.y = -1;
			current.x = -1;
			current.y = -1;
		}
		break;
		
	default:
		break;		
		
	}
	
	
	

}

void LineBrush::Auto(int startx, int endx, int starty, int endy, int w){
	
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	//int size = pDoc->getSize();
	int spacing = pDoc->getSpacing();
	//double alpha = pDoc->getOpac();


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	for (int i = startx; i < endx + 1; i += spacing){
		for (int j = starty; j < endy + 1; j += spacing){
			BrushMove(Point(startx + i, endy - j), Point(i, w - j));
		}
	}



}

char* LineBrush::BrushName(void){

	return ImpBrush::BrushName();
}

