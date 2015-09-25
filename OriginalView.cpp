//
// originalview.cpp
//
// The code maintaining the original view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "OriginalView.h"
#include <cmath>


#include "PointBrush.h"

extern bool isEdge;

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#endif

OriginalView::OriginalView(int			x, 
						   int			y, 
						   int			w, 
						   int			h, 
						   const char*	l)
							: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;

}

void OriginalView::draw()
{
	if(!valid())
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		// Tell openGL to read from the front buffer when capturing
		// out paint strokes 
		glReadBuffer( GL_FRONT );
		ortho();

	}

	




	glClear( GL_COLOR_BUFFER_BIT );

	if ( m_pDoc->m_ucBitmap ) 
	{
		// note that both OpenGL pixel storage and the Windows BMP format
		// store pixels left-to-right, BOTTOM-to-TOP!!  thus all the fiddling
		// around with startrow.

		m_nWindowWidth=w();
		m_nWindowHeight=h();

		int drawWidth, drawHeight;
		GLvoid* bitstart;

		// we are not using a scrollable window, so ignore it
		Point scrollpos;	// = GetScrollPosition();
		scrollpos.x=scrollpos.y=0;

		drawWidth	= min( m_nWindowWidth, m_pDoc->m_nWidth );
		drawHeight	= min( m_nWindowHeight, m_pDoc->m_nHeight );

		int	startrow	= m_pDoc->m_nHeight - (scrollpos.y + drawHeight);
		if ( startrow < 0 ) 
			startrow = 0;
		int startcol = 0;
			int endcol = startcol + drawWidth;
		int endrow = startrow + drawHeight;


		bitstart = m_pDoc->m_ucBitmap + 3 * ((m_pDoc->m_nWidth * startrow) + scrollpos.x);

		// just copy image to GLwindow conceptually
		glRasterPos2i( 0, m_nWindowHeight - drawHeight );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nWidth );
		glDrawBuffer( GL_BACK );
		glDrawPixels( drawWidth, drawHeight, GL_RGB, GL_UNSIGNED_BYTE, bitstart );
			
		glPointSize(5);
		glBegin(GL_POINTS);
		glColor3f(1, 0, 0);
		glVertex2d(cursorPoint.x-9, m_nWindowHeight-cursorPoint.y-1);
		glEnd();

		if (isEdge){
			isEdge = false;
			doEdgeThres(startcol, endcol, startrow, endrow, drawWidth);
			
		}
		
	}
			
	

	glFlush();
}


void OriginalView::cursor(Point& coord){
	cursorPoint.x=coord.x;
	cursorPoint.y = coord.y;
	redraw();
}

void OriginalView::refresh()
{
	redraw();
}

void OriginalView::resizeWindow(int	width, 
								int	height)
{
	resize(x(), y(), width, height);
}

void OriginalView::doEdgeThres(int startx, int endx, int starty, int endy,int w){
	
	int thres = m_pDoc->getEdgeThres();
	glPointSize(0);
	for (int i = startx; i < endx + 1; i++){
		for (int j = starty; j < endy + 1; j++){
			glBegin(GL_POINTS);
			if (calIntensity(Point(i, j)) < thres){

				(m_pDoc->m_ucBitmap + 3 * (j*w + i))[0]=0;
				(m_pDoc->m_ucBitmap + 3 * (j*w + i))[1] = 0;
				(m_pDoc->m_ucBitmap + 3 * (j*w + i))[2] = 0;
			}
			else{
				(m_pDoc->m_ucBitmap + 3 * (j*w + i))[0] = 255;
				(m_pDoc->m_ucBitmap + 3 * (j*w + i))[1] = 255;
				(m_pDoc->m_ucBitmap + 3 * (j*w + i))[2] = 255;
			}
			glEnd();
		}
	}
	redraw();
	/*
	int thres = m_pDoc->getEdgeThres();
	unsigned char* orig = m_pDoc->m_ucBitmap;
	for (int i = ; i < ; i++){
		for (int j = ; j < ; j++){
			if (calIntensity(Point(i, j)) < thres){
				//set the pixel to white 

			}
			else{
				// set the pixel to black

			}
		}
	}
	redraw();
	*/
}

int OriginalView::calIntensity(const Point source){
	
	int value;
	double Gx;
	double Gy;
	GLubyte color[3][3][3];
	double intensity[3][3];
	for (int i = -1; i < 2; i++){
		for (int j = -1; j < 2; j++){
			memcpy(color[i + 1][j + 1], m_pDoc->GetOriginalPixel(Point(source.x + i, source.y + j)), 3);
			intensity[i + 1][j + 1] = 0.299*color[i + 1][j + 1][0] + 0.587*color[i + 1][j + 1][1] + 0.144*color[i + 1][j + 1][2];
		}
	}
	Gx = intensity[0][0] * (-1) + intensity[0][1] * (-2) + intensity[0][2] * (-1)\
		+ intensity[2][0] * (1) + intensity[2][1] * (2) + intensity[2][2] * (1);
	Gy = intensity[0][0] * (-1) + intensity[1][0] * (-2) + intensity[2][0] * (-1)\
		+ intensity[0][2] * (1) + intensity[1][2] * (2) + intensity[2][2] * (1);
	
	value = sqrt(Gx*Gx + Gy*Gy);
	return value;
}

void OriginalView::SaveCurrentContent()
{/*
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);
	//glReadBuffer(GL_BACK);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);

	glReadPixels(0,
		m_nWindowHeight - m_nDrawHeight,
		m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pPaintBitstart);*/
}


void OriginalView::RestoreContent()
{/*
	glDrawBuffer(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2i(0, m_nWindowHeight - m_nDrawHeight);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);
	glDrawPixels(m_nDrawWidth,
		m_nDrawHeight,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		m_pPaintBitstart);

	//glDrawBuffer(GL_FRONT);*/
}
