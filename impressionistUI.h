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
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Color_Chooser.H>


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

enum{
	IMPRESSIONIST = 0,
	EXPRESSIONIST,
	COLOR_WASH,
	POINTILLIST,
	CUSTOMIZE,
	NUM_STYLE
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
	Fl_Button*          m_SwapContent;
		
	Fl_Box*				m_SpacingBox;
	Fl_Slider*			m_SpacingSlider;
	Fl_Light_Button*	m_SizeRandButton;
	Fl_Button*          m_PaintButton;

	Fl_Box*				m_EdgeThresBox;
	Fl_Slider*			m_EdgeThresSlider;
	Fl_Button*          m_DoItButton;



	// Colors dialog
	Fl_Window*			m_colorsDialog;
	Fl_Choice*			m_colorSpaceChoice;
	Fl_Color_Chooser*	m_colorChooser;


	
	// Paintly Dialog
	Fl_Window*			m_paintlyDialog;
	Fl_Choice*			m_styleChoice;
	Fl_Choice*			m_strokeChoice;
	Fl_Button*          m_RunButton;

	Fl_Box*				m_PaintlyBox;
	Fl_Slider*			m_ThresSlider;
	Fl_Slider*			m_CurveSlider;
	Fl_Slider*			m_BlurSlider;
	Fl_Slider*			m_GridSizeSlider;
	Fl_Slider*			m_MinStrokeSlider;
	Fl_Slider*			m_MaxStrokeSlider;
	Fl_Slider*			m_Alpha2Slider;
	Fl_Slider*			m_LayersSlider;
	Fl_Slider*			m_R0LevelSlider;
	Fl_Slider*			m_JrSlider;
	Fl_Slider*			m_JgSlider;
	Fl_Slider*			m_JbSlider;
	Fl_Slider*			m_JhSlider;
	Fl_Slider*			m_JsSlider;
	Fl_Slider*			m_JvSlider;


	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	int					getWidth();
	int					getAngle();
	double				getAlpha();
	void				setSize(int size);
	void				setAngle(int angle);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	//brushes
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	double  m_nAlpha;
	int		m_nSpacing;
	int		m_nEdgeThres;

	bool	m_bEdgeClipping;
	bool	m_bAnotherGrad;
	bool	m_bSizeRand;
	
	//color
	double	m_rInputValue;
	double	m_gInputValue;
	double	m_bInputValue;

	//paintly
	int		m_nThres;
	double	m_nCurve;
	double	m_nBlur;
	double	m_nGridSize;
	int		m_nMinStroke;
	int		m_nMaxStroke;
	double	m_nAlpha2;
	int		m_nLayers;
	int		m_nR0Level;
	double	m_nJr;
	double	m_nJg;
	double	m_nJb;
	double	m_nJh;
	double	m_nJs;
	double	m_nJv;




	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE+1];
	//static Fl_Menu_Item		colorSpaceMenu[];
	static Fl_Menu_Item		strokeDirMenu[];
	static Fl_Menu_Item		styleMenu[];
	static Fl_Menu_Item		strokeMenu[];


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
		static void cb_PaintButton(Fl_Widget* o, void* v);				/////////////
		static void cb_edgeThresSlides(Fl_Widget* o, void* v);			/////////////
		static void cb_DoItButton(Fl_Widget* o, void* v);				/////////////
		static void cb_SwapContentButton(Fl_Widget* o, void* v);		/////////////
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_undo(Fl_Menu_* o, void* v);							//////////////
	static void	cb_colors(Fl_Menu_* o, void* v);						//////////////
		static void	cb_colorSpaceChoice(Fl_Widget* o, void* v);			//////////////
		static void	cb_rInput(Fl_Widget* o, void* v);					//////////////
		static void	cb_gInput(Fl_Widget* o, void* v);					//////////////
		static void	cb_bInput(Fl_Widget* o, void* v);					//////////////

	static void cb_paintly(Fl_Menu_* o, void* v);						/////////////
		static void	cb_styleChoice(Fl_Widget* o, void* v);				//////////////
		static void	cb_strokeChoice(Fl_Widget* o, void* v);				//////////////
		static void	cb_RunButton(Fl_Widget* o, void* v);				//////////////
		static void	cb_thresSlides(Fl_Widget* o, void* v);				//////////////
		static void	cb_curveSlides(Fl_Widget* o, void* v);				//////////////
		static void	cb_blurSlides(Fl_Widget* o, void* v);				//////////////
		static void	cb_gridSizeSlides(Fl_Widget* o, void* v);			//////////////
		static void	cb_minStrokeSlides(Fl_Widget* o, void* v);			//////////////
		static void	cb_maxStrokeSlides(Fl_Widget* o, void* v);			//////////////
		static void	cb_alpha2Slides(Fl_Widget* o, void* v);				//////////////
		static void	cb_layersSlides(Fl_Widget* o, void* v);				//////////////
		static void	cb_r0LevelSlides(Fl_Widget* o, void* v);			//////////////
		static void	cb_jrSlides(Fl_Widget* o, void* v);					//////////////
		static void	cb_jgSlides(Fl_Widget* o, void* v);					//////////////
		static void	cb_jbSlides(Fl_Widget* o, void* v);					//////////////
		static void	cb_jhSlides(Fl_Widget* o, void* v);					//////////////
		static void	cb_jsSlides(Fl_Widget* o, void* v);					//////////////
		static void	cb_jvSlides(Fl_Widget* o, void* v);					//////////////
	static void cb_load_edge_image(Fl_Menu_* o, void* v);				//////////////
	static void cb_load_another_image(Fl_Menu_* o, void* v);			//////////////
	static void	cb_exit(Fl_Menu_* o, void* v);

	// Display menu
	static void	cb_originalImage(Fl_Menu_* o, void* v);					//////////////
	static void	cb_edge_image(Fl_Menu_* o, void* v);					//////////////
	static void	cb_another_image(Fl_Menu_* o, void* v);					//////////////
	
	// Options menu
	static void	cb_faster(Fl_Menu_* o, void* v);						//////////////
	static void	cb_safer(Fl_Menu_* o, void* v);							//////////////

	// About menu
	static void	cb_about(Fl_Menu_* o, void* v);
	
	

	
	Fl_Group* group;

	


};

#endif
