//
// ScatteredPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of ImpBrush. 
//
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize()/2;
	//int angle = pDoc->getAngle();
	double opacity = pDoc->getOpac();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize(0.1);
	srand(time(0));
	glBegin(GL_POINTS);
		for (float i = target.x - size; i < target.x + size; i++){
			for (float j = target.y - size; j < target.y + size; j++){
				float  rnd = fRand(0,1);
				if (rnd<0.2){
					SetColorOpac(Point(i - target.x + source.x, j-target.y+source.y), opacity);
					glVertex2d(i, j);
				}
			}
		}
	glEnd();


	/*

	*/
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

char* ScatteredPointBrush::BrushName(void){

	return ImpBrush::BrushName();
}

