//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "PointBrush.h"

extern float frand();

PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void PointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize( (float)size );

	BrushMove( source, target );
}

void PointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}
	
	double opacity = pDoc->getOpac();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin( GL_POINTS );
	glColor4f(0.5, 0.5, 0.5, opacity);
		SetColorOpac(source, opacity);
		glVertex2d( target.x, target.y );
	glEnd();
}

void PointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

char* PointBrush::BrushName(void){
	
	return ImpBrush::BrushName();
}

