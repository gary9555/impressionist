//
// FilterBrush.cpp
//
// The implementation of Filter Brush. It is a kind of ImpBrush. 
//
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "FilterBrush.h"

extern float frand();

bool FilterBrush::isBlur = true;

FilterBrush::FilterBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void FilterBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void FilterBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("FilterBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	double opacity = pDoc->getOpac();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (isBlur){
		glPointSize(2);
		glBegin(GL_POINTS);
		Blur(source, opacity);
		glVertex2d(target.x, target.y);
		glEnd();
	}
	else{
		glPointSize(2);
		glBegin(GL_POINTS);
		Sharpen(source, opacity);
		glVertex2d(target.x, target.y);
		glEnd();
	}
}

void FilterBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing
}

char* FilterBrush::BrushName(void){

	return ImpBrush::BrushName();
}

void FilterBrush::Blur(const Point source, double opacity){
	
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[3][3][3];
	GLubyte filteredColor[4];
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2;j++)
			memcpy(color[i+1][j+1], pDoc->GetOriginalPixel(Point(source.x+i,source.y+j)), 3);

	for (int k = 0; k < 3; k++){
		filteredColor[k] =  (1 * (color[0][0][k] + color[0][2][k] + color[2][0][k] + color[2][2][k]) \
			+ 2 * (color[0][1][k] + color[1][0][k] + color[1][2][k] + color[2][1][k]) + 4 * color[1][1][k])/16;
	}	
	filteredColor[3] = opacity * 255;
	glColor4ubv(filteredColor);
}

void FilterBrush::Sharpen(const Point source, double opacity){
	
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[3][3][3];
	GLubyte filteredColor[4] = { 0, 0, 0, 0 };
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			memcpy(color[i + 1][j + 1], pDoc->GetOriginalPixel(Point(source.x + i, source.y + j)), 3);
	
	//for (int k = 0; k < 3; k++){
	//	filteredColor[k] =(-1 * (color[0][1][k] + color[1][0][k] + color[1][2][k] + color[2][1][k]) + 4 * color[1][1][k]);
	//}
	
	int kernel[3][3] = { -1, -1, -1, -1, 8, -1, -1, -1, -1 };

	int kCenterX = 1;
	int kCenterY = 1;
	int ii, jj, mm, nn;

	for (int k = 0; k < 3; k++){
		for (int m = 0; m < 3; m++)     // kernel rows
		{
			mm = 2 - m;      // row index of flipped kernel

			for (int n = 0; n < 3; n++) // kernel columns
			{
				nn = 2 - n;  // column index of flipped kernel
				// index of input signal, used for checking boundary
				ii = m;
				jj = n;				
				filteredColor[k] = filteredColor[k] + (color[ii][jj][k] * kernel[mm][nn]);
			}
		}
	}
	filteredColor[3] = opacity * 255;
	glColor4ubv(filteredColor);




}