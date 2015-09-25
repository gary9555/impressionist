//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "LineBrush.h"
#include "ScatteredLineBrush.h"
#include "FilterBrush.h"



#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6
#define MOUSE_MOVE			7
#define DIM					8
#define AUTO				9

#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;
static Point	astarting;  // for the angle calculation
static Point	ending;
static Point	lstarting;   // for displaying the red line

extern bool isDimEvent;
extern bool isAuto;


PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;
	
	

}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );
	//drawWidth = min(m_nWindowWidth, m_pDoc->m_nWidth);
	//drawHeight = min(m_nWindowHeight, m_pDoc->m_nHeight);
	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;


	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{	
		
		RestoreContent();

	}
	
	if (isDimEvent){
		isAnEvent = 1;
		eventToDo = DIM;
		isDimEvent = false;
	}
	if (isAuto){
		isAnEvent = 1;
		eventToDo = AUTO;
	}

	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	
		

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			//delete[] m_pDoc->m_ucUndo;
			if (!m_pDoc->m_ucUndo)
				m_pDoc->m_ucUndo = new unsigned char[m_pDoc->m_nPaintHeight*m_pDoc->m_nPaintWidth * 3];
		//	SaveCurrentContent();
			
			
				memcpy(m_pDoc->m_ucUndo, m_pDoc->m_ucPainting, m_pDoc->m_nPaintHeight*m_pDoc->m_nPaintWidth * 3);
				if (coord.x < m_nEndCol&&coord.y < m_nEndRow)
					m_pDoc->m_pCurrentBrush->BrushBegin(source, target);
			break; 
		case LEFT_MOUSE_DRAG:
			if (coord.x < m_nEndCol&&coord.y<m_nEndRow)
				m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			break;
		case LEFT_MOUSE_UP:
			LineBrush::isRightMouse = false;
			ScatteredLineBrush::isRightMouse = false;
													
			m_pDoc->m_pCurrentBrush->BrushEnd(source, target);
			
			SaveCurrentContent();
			RestoreContent();
		//	memcpy(m_pDoc->m_ucUndo, m_pDoc->m_ucPainting, sizeof(m_pDoc->m_ucPainting));
			break;
		case RIGHT_MOUSE_DOWN:
			FilterBrush::isBlur = !FilterBrush::isBlur;
			astarting.x = coord.x; 
			astarting.y = coord.y;
			lstarting.x = target.x;
			lstarting.y = target.y;

			SaveCurrentContent();
			break;
		case RIGHT_MOUSE_DRAG:
			RestoreContent();
			
			glLineWidth(2);
			glBegin(GL_LINE_STRIP);
				glColor3f(1, 0, 0);
				glVertex2d(lstarting.x, lstarting.y);
				glVertex2d(target.x, target.y);
			glEnd();
			
			break;
		case RIGHT_MOUSE_UP:
			LineBrush::isRightMouse = true;
			ScatteredLineBrush::isRightMouse = true;
			ending.x = coord.x;
			ending.y = coord.y;
			m_pDoc->m_pCurrentBrush->BrushEnd(astarting, ending);
			RestoreContent();
																// pass the starting and ending position of the mouse 
			break;												// finished with right dragging
	
		case DIM:
			break;
			/*
			currentAlpha=m_pDoc->getDimmedAlpha();
			for (int i = 0;i< m_nDrawWidth*m_nDrawHeight * 3; i++){
				m_pDoc->m_ucBitmap[i] = m_pDoc->m_ucBitmap[i] * (1 - currentAlpha * 1) + m_pDoc->m_ucDissolve[i] * currentAlpha * 1;
			}
			m_pDoc->m_ucDimmed
			prevAlpha = currentAlpha;
			isDimEvent = false;
			break;
			*/
		
		case AUTO:
			m_pDoc->m_pCurrentBrush->Auto(m_nStartCol, m_nEndCol, m_nStartRow, m_nEndRow, m_nWindowHeight);
			SaveCurrentContent(); 
			//RestoreContent();
			isAuto = false;
			break;
		
		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		m_pDoc->m_pUI->m_origView->cursor(coord);
		isAnEvent=1;
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		
		m_pDoc->m_pUI->m_origView->cursor(coord);
		//isAnEvent = 1;
		//eventToDo = MOUSE_MOVE;
		//redraw();
		break;
	default:
		return 0;
		break;

	}



	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);
	//glReadBuffer(GL_BACK);
	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

	//glDrawBuffer(GL_FRONT);
}
