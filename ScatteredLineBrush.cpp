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
static Point prev(-1, -1);
static Point current(-1, -1);
bool ScatteredLineBrush::isRightMouse = false;


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
	int strokeDirChoice = dlg->m_StrokeDirChoice->value();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	srand(time(0));
	glMatrixMode(GL_MODELVIEW);
	
	switch (strokeDirChoice){
	// Slider/Right mouse 
	case 0:
		// don't have to change size and angle value
		for (int i = 0; i < 4; i++){
			float length = fRand(1, size / 2)*2.5;
			float dist = fRand(-size*0.3, size*0.3)*2.5;
			float displacement = fRand(-size*0.75, size*0.75);
			float x1 = target.x + displacement;
			float y1 = target.y + dist;

			glPushMatrix();
				glTranslatef(x1, y1, 0.0);
				glRotatef(angle, 0.0, 0.0, 1.0);
				glTranslatef(-x1, -y1, 0.0);
				glBegin(GL_LINE_STRIP);
					SetColorOpac(Point(source.x + displacement, source.y + dist), opacity);
					glVertex2d(x1 - length*0.75, y1);
					glVertex2d(x1 + length*0.75, y1);
				glEnd();
			glPopMatrix();
		}
		break;

	// Gradient
	case 1:
		// change angle value according to 
		// the gradient at this point
		for (int i = 0; i < 4; i++){
			float length = fRand(1, size / 2)*2.5;
			float dist = fRand(-size*0.3, size*0.3)*2.5;
			float displacement = fRand(-size*0.75, size*0.75);
			float x1 = target.x + displacement;
			float y1 = target.y + dist;
			double Gx;
			double Gy;
			GLubyte color[3][3][3];
			double intensity[3][3];
			for (int i = -1; i < 2; i++){
				for (int j = -1; j < 2; j++){
					memcpy(color[i + 1][j + 1], pDoc->GetOriginalPixel(Point(source.x + displacement + i, source.y + dist + j)), 3);
					intensity[i + 1][j + 1] = 0.299*color[i + 1][j + 1][0] + 0.587*color[i + 1][j + 1][1] + 0.144*color[i + 1][j + 1][2];
				}
			}
			Gx = intensity[0][0] * (-1) + intensity[0][1] * (-2) + intensity[0][2] * (-1)\
				+ intensity[2][0] * (1) + intensity[2][1] * (2) + intensity[2][2] * (1);
			Gy = intensity[0][0] * (-1) + intensity[1][0] * (-2) + intensity[2][0] * (-1)\
				+ intensity[0][2] * (1) + intensity[1][2] * (2) + intensity[2][2] * (1);
			angle = -(int)(atan2(Gy, Gx)*57.32) % 360;

			glPushMatrix();
				glTranslatef(x1, y1, 0.0);
				glRotatef(angle, 0.0, 0.0, 1.0);
				glTranslatef(-x1, -y1, 0.0);
				glBegin(GL_LINE_STRIP);
					SetColorOpac(Point(source.x + displacement, source.y + dist), opacity);
					glVertex2d(x1 - length*0.75, y1);
					glVertex2d(x1 + length*0.75, y1);
				glEnd();
			glPopMatrix();
		}
		break;

	// Brush direction
	case 2:
		current.x = target.x;
		current.y = target.y;
		if (prev.x!=-1&&current.x!=-1&&(current.x != prev.x || current.y != prev.y)){
			int dx = current.x - prev.x;
			int dy = current.y - prev.y;
			angle = (int)(atan2(dy, dx)*57.32) % 360;

			
			
			for (int i = 0; i < 4; i++){
				float length = size;
				float dist = fRand(-size*0.3, size*0.3)*2.5;
				float displacement = fRand(-size*0.75, size*0.75);
				float x1 = target.x + displacement;
				float y1 = target.y + dist;

				glPushMatrix();
				glTranslatef(x1, y1, 0.0);
				glRotatef(angle, 0.0, 0.0, 1.0);
				glTranslatef(-x1, -y1, 0.0);
				glBegin(GL_LINE_STRIP);
				SetColorOpac(Point(source.x + displacement, source.y + dist), opacity);
				glVertex2d(x1 - length*0.75, y1);
				glVertex2d(x1 + length*0.75, y1);
				glEnd();
				glPopMatrix();
			}
		}
		prev.x = current.x;
		prev.y = current.y;
		break;

	default:
		break;

	}
	
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int strokeDirChoice = dlg->m_StrokeDirChoice->value();

	// values useful for the right mouse drag
	int dx = target.x - source.x;
	int dy = target.y - source.y;
	int size = sqrt(dx*dx + dy*dy);
	int angle = -(int)(atan2(dy, dx)*57.32) % 360;

	switch (strokeDirChoice){
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

char* ScatteredLineBrush::BrushName(void){

	return ImpBrush::BrushName();
}

