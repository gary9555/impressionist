//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Box.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

enum{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX

};


class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

	// for brush dialog
	Fl_Window*			m_brushDialog;
		Fl_Choice*			m_BrushTypeChoice;
		Fl_Button*          m_ClearCanvasButton;
		Fl_Choice*			m_StrokeDirChoice;
		Fl_Slider*			m_BrushSizeSlider;
		Fl_Slider*			m_LineWidthSlider;
		Fl_Slider*			m_LineAngleSlider;
		Fl_Slider*			m_AlphaSlider;
		Fl_Light_Button*	m_EdgeClippingButton;
		Fl_Light_Button*	m_AnotherGradientButton;
		
		Fl_Box*				m_SpacingBox;
		Fl_Slider*			m_SpacingSlider;
		Fl_Light_Button*	m_SizeRandButton;
		Fl_Button*          m_PaintButton;

		Fl_Box*				m_EdgeThresBox;
		Fl_Slider*			m_EdgeThresSlider;
		Fl_Button*          m_DoItButton;


	// for colors dialog
	Fl_Window*			m_colorsDialog;
	Fl_Choice*			m_colorSpaceChoice;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	void				setSize(int size);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	double  m_nAlpha;
	int		m_nSpacing;
	int		m_nEdgeThres;

	bool	m_bEdgeClipping;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	static Fl_Menu_Item		colorSpaceMenu[];
	static Fl_Menu_Item		strokeDirMenu[];


	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static

	// File menu
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
		static void	cb_brushChoice(Fl_Widget* o, void* v);
		static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
		static void	cb_strokeDirChoice(Fl_Widget* o, void* v);			///////////////
		static void	cb_sizeSlides(Fl_Widget* o, void* v);
		static void	cb_lineWidthSlides(Fl_Widget* o, void* v);			//////////////
		static void	cb_lineAngleSlides(Fl_Widget* o, void* v);			//////////////
		static void	cb_alphaSlides(Fl_Widget* o, void* v);				//////////////
		static void cb_EdgeClippingButton(Fl_Widget* o, void* v);		/////////////
		static void cb_AnotherGradientButton(Fl_Widget* o, void* v);	/////////////
		static void	cb_spacingSlides(Fl_Widget* o, void* v);			//////////////
		static void cb_SizeRandButton(Fl_Widget* o, void* v);			/////////////
		static void cb_PaintButton(Fl_Widget* o, void* v);			/////////////
		static void cb_edgeThresSlides(Fl_Widget* o, void* v);			/////////////
		static void cb_DoItButton(Fl_Widget* o, void* v);			/////////////

	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_colors(Fl_Menu_* o, void* v);					//////////////
		static void	cb_colorSpaceChoice(Fl_Widget* o, void* v);		//////////////
	static void cb_paintly(Fl_Menu_* o, void* v);					/////////////
	static void cb_load_edge_image(Fl_Menu_* o, void* v);			//////////////
	static void cb_load_another_image(Fl_Menu_* o, void* v);		//////////////
	static void	cb_exit(Fl_Menu_* o, void* v);

	// Display menu
	static void	cb_originalImage(Fl_Menu_* o, void* v);				//////////////
	static void	cb_edge_image(Fl_Menu_* o, void* v);				//////////////
	static void	cb_another_image(Fl_Menu_* o, void* v);				//////////////
	
	// Options menu
	static void	cb_faster(Fl_Menu_* o, void* v);					//////////////
	static void	cb_safer(Fl_Menu_* o, void* v);						//////////////

	// About menu
	static void	cb_about(Fl_Menu_* o, void* v);
	
	

	
	Fl_Group* group;

	


};

#endif
