//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source)
{
	ImpressionistDoc* pDoc = GetDocument();


	GLubyte color[3];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
 
	glColor3ubv( color );

}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColorOpac(const Point source, double opacity)
{
	ImpressionistDoc* pDoc = GetDocument();
	float r = pDoc->m_pUI->m_colorChooser->r();
	float g = pDoc->m_pUI->m_colorChooser->g();
	float b = pDoc->m_pUI->m_colorChooser->b();

	GLubyte color[4];

	memcpy(color, pDoc->GetOriginalPixel(source), 3);
	color[0] *= r;
	color[1] *= g;
	color[2] *= b;
	color[3] = opacity * 255;
	//glColor3ubv(color);
	glColor4ubv(color);

}

