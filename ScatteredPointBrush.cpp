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

void ScatteredPointBrush::Auto(int startx, int endx, int starty, int endy, int w){

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


char* ScatteredPointBrush::BrushName(void){

	return ImpBrush::BrushName();
}

