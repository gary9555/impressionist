// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image
	int		loadAnotherImage(char *iname);			// called by the UI to load another image
	int		loadDissolveImage(char *iname);			// called by the UI to load a dissolved image




	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType

	void	setPaintStyle(int style);		// called by the UI to set the painting style		//////////////////////

	int		getSize();						// get the UI size
	int		getWidth();						// get the UI width
	int		getAngle();						// get the UI angle
	double	getOpac();						// get the UI alpha

	void	setBrushSize(int size);			// set the UI size
	void	setBrushAngle(int angle);		// set the UI angle
	char*	getImageName();					// get the current image name
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight,
					m_nNewWidth,
					m_nNewHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, m_nNewPaintWidth,
					m_nPaintHeight, m_nNewPaintHeight;
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;
	
	unsigned char*  m_ucUndo;	// to store the undo function bitmap


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	

	// The current active color space


	// Size of the brush.
	int m_nSize;	
	int m_nWdith;
	int m_nAngle;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  


private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
