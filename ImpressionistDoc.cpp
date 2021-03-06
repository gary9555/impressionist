// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "LineBrush.h"
#include "CircleBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredPointBrush.h"
#include "LoveBrush.h"
#include "FilterBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucUndo		= NULL;
	m_ucDissolve = NULL;
	m_ucDimmed = NULL;



	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush(this, "Scattered Points");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush(this, "Scattered Lines");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush(this, "Scattered Circles");
	ImpBrush::c_pBrushes[BRUSH_LOVE]
		= new LoveBrush(this, "Love");
	ImpBrush::c_pBrushes[BRUSH_FILTER]
		= new FilterBrush(this, "Filter");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}



//---------------------------------------------------------
// Called by the UI when the user changes the painting style.
// style: one of the defined painting styles.
//---------------------------------------------------------
void ImpressionistDoc::setPaintStyle(int style)
{
	
}



//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Returns the edge threshold of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getEdgeThres()
{
	return m_pUI->getEdgeThres();
}

//---------------------------------------------------------
// Returns the width of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getWidth()
{
	return m_pUI->getWidth();
}

//---------------------------------------------------------
// Returns the angle of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getAngle()
{
	return m_pUI->getAngle();
}

//---------------------------------------------------------
// Returns the alpha value of the brush.
//---------------------------------------------------------
double ImpressionistDoc::getOpac()
{
	return m_pUI->getAlpha();
}

//---------------------------------------------------------
// Returns the alpha value of the brush.
//---------------------------------------------------------
double ImpressionistDoc::getDimmedAlpha()
{
	return m_pUI->getDimmedAlpha();
}

//---------------------------------------------------------
// Returns the alpha value of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSpacing()
{
	return m_pUI->getSpacing();
}

//---------------------------------------------------------
// sets the size of the brush in the UI, thus read back by the pDOC
//---------------------------------------------------------
void ImpressionistDoc::setBrushSize(int size){
	m_pUI->setSize(size);
}

//---------------------------------------------------------
// sets the angle of the brush in the UI, thus read back by the pDOC
//---------------------------------------------------------
void ImpressionistDoc::setBrushAngle(int angle){
	m_pUI->setAngle(angle);
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------

int ImpressionistDoc::loadImage(char *iname)
{
	// try to open the image to read
	unsigned char*	data;
	int				width,
		height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth = width;
	m_nPaintWidth = width;
	m_nHeight = height;
	m_nPaintHeight = height;

	// release old storage
	if (m_ucBitmap) { delete[] m_ucBitmap; m_ucBitmap = NULL; }
	if (m_ucPainting) {delete[] m_ucPainting; m_ucPainting = NULL;}
	if (m_ucUndo) { delete[] m_ucUndo; m_ucUndo = NULL; }
	if (m_ucDimmed){ delete[] m_ucDimmed; m_ucDimmed = NULL; }
	if (m_ucDissolve){ delete[] m_ucDissolve; m_ucDissolve = NULL; }
	
	
	m_ucBitmap = new unsigned char[3 * width*height];
	m_ucBitmap		= data;
	//memcpy(m_ucBitmap, data, 3 * width*height);
	
	
	m_ucDimmed = new unsigned char[width*height * 3];
	memcpy(m_ucDimmed, m_ucBitmap, width*height * 3);
	

	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);
	

	double dimAlpha = getDimmedAlpha();


	for(int i = 0; i < width*height * 3; i++){
		m_ucPainting[i] = m_ucPainting[i] * (1 - dimAlpha * 1) + m_ucDimmed[i] * dimAlpha * 1; // alpha mask set to all 1
	}
	
	m_ucUndo = new unsigned char[width*height * 3];
	memset(m_ucUndo, 0, width*height * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}



//---------------------------------------------------------
// Load Another image
// This is called by the UI when the load another image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadAnotherImage(char *iname)
{
	// try to open the image to read
	unsigned char*	data;
	int				width,
					height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load another bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nNewWidth = width;
	m_nNewHeight = height;

	if (m_nNewWidth != m_nWidth || m_nNewHeight != m_nHeight){
		fl_alert("Different Dimensions!");
		return 0;
	}
	m_nNewPaintWidth = width;
	m_nNewPaintHeight = height;
	/*
	// release old storage
	
	//if (m_ucPainting) delete[] m_ucPainting;
	//if (m_ucUndo) delete[] m_ucUndo;
	m_ucBitmap = new unsigned char[m_nNewPaintWidth*m_nNewPaintHeight * 3];
	memcpy(m_ucBitmap, data, m_nNewPaintWidth*m_nNewPaintHeight * 3);
	*/
	
	m_ucBitmap = data;
	

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		width * 2,
		height + 25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();


	return 1;
}

//---------------------------------------------------------
// to dissolve anther image into the current image, 
// dimensions must meet
//---------------------------------------------------------
int ImpressionistDoc::loadDissolveImage(char *iname){
	// try to open the image to read
	unsigned char*	data;
	int				width,
					height;

	if ((data = readBMP(iname, width, height)) == NULL)
	{
		fl_alert("Can't load dissolve bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nDisWidth = width;
	m_nDisHeight = height;

	if (m_nDisWidth != m_nWidth || m_nDisHeight != m_nHeight){
		fl_alert("Different Dimensions!");
		return 0;
	}
	m_nDisPaintWidth = width;
	m_nDisPaintHeight = height;

	double alpha = 0.5;
		//getOpac();

	// release old storage
	//if (m_ucBitmap) delete[] m_ucBitmap;
	//if (m_ucPainting) delete[] m_ucPainting;
	//if (m_ucUndo) delete[] m_ucUndo;
	//m_ucDissolve = data;
	m_ucDissolve = new unsigned char[3 * m_nDisPaintWidth*m_nDisPaintWidth];
	memcpy(m_ucDissolve, data, 3 * m_nDisPaintWidth*m_nDisPaintWidth);
	//m_ucDissolve = data;
	// calculate alpha blending value at each pixel
	for (int i = 0; i < 3 * m_nDisPaintWidth*m_nDisPaintWidth; i++){
		m_ucBitmap[i] = m_ucBitmap[i] * (1 - alpha * 1) + m_ucDissolve[i] * alpha * 1; // alpha mask set to all 1
	}
	

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
		m_pUI->m_mainWindow->y(),
		width * 2,
		height + 25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);
	m_pUI->m_paintView->refresh();


	return 1;
}

//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

