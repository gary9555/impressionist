//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

extern bool isDimEvent = false;
extern bool isAuto = false;
extern bool isEdge = false;
/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save }.
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}

void ImpressionistUI::cb_load_edge_image(Fl_Menu_* o, void* v){
	
	
}

void ImpressionistUI::cb_load_another_image(Fl_Menu_* o, void* v){
	
	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadAnotherImage(newfile);
	}
}

void ImpressionistUI::cb_load_dissolve_image(Fl_Menu_* o, void* v){

	ImpressionistDoc *pDoc = whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName());
	if (newfile != NULL) {
		pDoc->loadDissolveImage(newfile);
	}
}

//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Adds an undo effect to retore to the last move
// Called by the UI when the undo menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_undo(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc = whoami(o)->getDocument();
	if (pDoc->m_ucUndo){
		
	unsigned char* temp = pDoc->m_ucPainting;
		pDoc->m_ucPainting = pDoc->m_ucUndo;
		pDoc->m_ucUndo = temp;
		whoami(o)->m_paintView->refresh();
		delete[] pDoc->m_ucUndo;
		pDoc->m_ucUndo = NULL;
		//pDoc->m_pUI->m_paintView->SaveCurrentContent();

	//	delete [] temp;
	}
	//glFlush();
}









//------------------------------------------------------------
// Tunes the colors
// Called by the UI when the colors menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_colors(Fl_Menu_* o, void* v)
{
	whoami(o)->m_colorsDialog->show();
}















void ImpressionistUI::cb_originalImage(Fl_Menu_* o, void* v){

}

void ImpressionistUI::cb_edge_image(Fl_Menu_* o, void* v){

}

void ImpressionistUI::cb_another_image(Fl_Menu_* o, void* v){

}

void ImpressionistUI::cb_faster(Fl_Menu_* o, void* v){

}

void ImpressionistUI::cb_safer(Fl_Menu_* o, void* v){

}

void ImpressionistUI::cb_strokeDirChoice(Fl_Widget* o, void* v){

}

void ImpressionistUI::cb_colorSpaceChoice(Fl_Widget* o, void* v){
	
}






//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();
}









// Brushes Dialog 
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	switch (type){
	case BRUSH_POINTS:		
	case BRUSH_CIRCLES:
	case BRUSH_SCATTERED_POINTS:
	case BRUSH_SCATTERED_CIRCLES:
	case BRUSH_LOVE:
	case BRUSH_FILTER:
		pUI->m_StrokeDirChoice->deactivate();
		pUI->m_LineWidthSlider->deactivate();
		pUI->m_LineAngleSlider->deactivate();
		pUI->m_EdgeClippingButton->deactivate();
		pUI->m_AnotherGradientButton->deactivate();
		break;
	case BRUSH_LINES:
	case BRUSH_SCATTERED_LINES:
		pUI->m_StrokeDirChoice->activate();
		pUI->m_LineWidthSlider->activate();
		pUI->m_LineAngleSlider->activate();
		pUI->m_EdgeClippingButton->activate();
		pUI->m_AnotherGradientButton->activate();
		break;
	default:
		break;

	}

	pDoc->setBrushType(type);
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();

	pDoc->clearCanvas();
}


//-----------------------------------------------------------
// Updates the brush size to use from the value of the size
// slider
// Called by the UI when the size slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}


//-----------------------------------------------------------
// Updates the line width to use from the value of the line width
// slider
// Called by the UI when the line width slider is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = int(((Fl_Slider *)o)->value());
}


void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle = int(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_alphaSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlpha = double(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_EdgeClippingButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->m_bEdgeClipping == TRUE) pUI->m_bEdgeClipping = FALSE;
	else pUI->m_bEdgeClipping = TRUE;
}

void ImpressionistUI::cb_AnotherGradientButton(Fl_Widget* o, void* v){
	
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->m_bAnotherGrad == TRUE) pUI->m_bAnotherGrad = FALSE;
	else pUI->m_bAnotherGrad = TRUE;
}

void ImpressionistUI::cb_spacingSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nSpacing = int(((Fl_Slider *)o)->value());

}

void ImpressionistUI::cb_SizeRandButton(Fl_Widget* o, void* v){

	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));

	if (pUI->m_bSizeRand == TRUE) pUI->m_bSizeRand = FALSE;
	else pUI->m_bSizeRand = TRUE;
}

void ImpressionistUI::cb_PaintButton(Fl_Widget* o, void* v){
	
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc *pDoc = pUI->getDocument();

	isAuto = true;
	pUI->m_origView->refresh();

	pUI->m_paintView->refresh();

}

void ImpressionistUI::cb_edgeThresSlides(Fl_Widget* o, void* v){
	
	((ImpressionistUI*)(o->user_data()))->m_nEdgeThres = int(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_DoItButton(Fl_Widget* o, void* v){

	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc *pDoc = pUI->getDocument();
	isEdge = true;
	pUI->m_origView->refresh();

}

void ImpressionistUI::cb_SwapContentButton(Fl_Widget* o, void* v){
	
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc *pDoc = pUI->getDocument();
	
	unsigned char*	temp = pDoc->m_ucBitmap;
	pDoc->m_ucBitmap = pDoc->m_ucPainting;
	pDoc->m_ucPainting = temp;
	
	pUI->m_origView->refresh();
	pUI->m_paintView->refresh();


}

void ImpressionistUI::cb_DimmedAlphaSlides(Fl_Widget* o, void* v){
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc *pDoc = pUI->getDocument();
	pUI->m_nDimmedAlpha = double(((Fl_Slider *)o)->value());
	isDimEvent = true;
	pUI->m_paintView->refresh();
}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------





// Paintly dialog
//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------

void ImpressionistUI::cb_paintly(Fl_Menu_* o, void* v){
	
	whoami(o)->m_paintlyDialog->show();
}

void ImpressionistUI::cb_styleChoice(Fl_Widget* o, void* v){

	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	int style = (int)v;

	switch (style){
	case IMPRESSIONIST:
		pUI->m_ThresSlider->value(100);
		pUI->m_CurveSlider->value(1.00);
		pUI->m_BlurSlider->value(0.50);
		pUI->m_GridSizeSlider->value(1.00);
		pUI->m_MinStrokeSlider->value(4);
		pUI->m_MaxStrokeSlider->value(16);
		pUI->m_Alpha2Slider->value(1.00);
		pUI->m_LayersSlider->value(3);
		pUI->m_R0LevelSlider->value(3);
		pUI->m_JrSlider->value(0.00);
		pUI->m_JgSlider->value(0.00);
		pUI->m_JbSlider->value(0.00);
		pUI->m_JhSlider->value(0.00);
		pUI->m_JsSlider->value(0.00);
		pUI->m_JvSlider->value(0.00);

		pUI->m_ThresSlider->deactivate();
		pUI->m_CurveSlider->deactivate();
		pUI->m_BlurSlider->deactivate();
		pUI->m_GridSizeSlider->deactivate();
		pUI->m_MinStrokeSlider->deactivate();
		pUI->m_MaxStrokeSlider->deactivate();
		pUI->m_Alpha2Slider->deactivate();
		pUI->m_LayersSlider->deactivate();
		pUI->m_R0LevelSlider->deactivate();
		pUI->m_JrSlider->deactivate();
		pUI->m_JgSlider->deactivate();
		pUI->m_JbSlider->deactivate();
		pUI->m_JhSlider->deactivate();
		pUI->m_JsSlider->deactivate();
		pUI->m_JvSlider->deactivate();
		break;
	case EXPRESSIONIST:
		pUI->m_ThresSlider->value(50);
		pUI->m_CurveSlider->value(0.25);
		pUI->m_BlurSlider->value(0.50);
		pUI->m_GridSizeSlider->value(1.00);
		pUI->m_MinStrokeSlider->value(10);
		pUI->m_MaxStrokeSlider->value(16);
		pUI->m_Alpha2Slider->value(0.70);
		pUI->m_LayersSlider->value(3);
		pUI->m_R0LevelSlider->value(3);
		pUI->m_JrSlider->value(0.00);
		pUI->m_JgSlider->value(0.00);
		pUI->m_JbSlider->value(0.00);
		pUI->m_JhSlider->value(0.00);
		pUI->m_JsSlider->value(0.00);
		pUI->m_JvSlider->value(0.50);

		pUI->m_ThresSlider->deactivate();
		pUI->m_CurveSlider->deactivate();
		pUI->m_BlurSlider->deactivate();
		pUI->m_GridSizeSlider->deactivate();
		pUI->m_MinStrokeSlider->deactivate();
		pUI->m_MaxStrokeSlider->deactivate();
		pUI->m_Alpha2Slider->deactivate();
		pUI->m_LayersSlider->deactivate();
		pUI->m_R0LevelSlider->deactivate();
		pUI->m_JrSlider->deactivate();
		pUI->m_JgSlider->deactivate();
		pUI->m_JbSlider->deactivate();
		pUI->m_JhSlider->deactivate();
		pUI->m_JsSlider->deactivate();
		pUI->m_JvSlider->deactivate();
		break;
	case COLOR_WASH:
		pUI->m_ThresSlider->value(200);
		pUI->m_CurveSlider->value(1.00);
		pUI->m_BlurSlider->value(0.50);
		pUI->m_GridSizeSlider->value(1.00);
		pUI->m_MinStrokeSlider->value(4);
		pUI->m_MaxStrokeSlider->value(16);
		pUI->m_Alpha2Slider->value(0.50);
		pUI->m_LayersSlider->value(3);
		pUI->m_R0LevelSlider->value(3);
		pUI->m_JrSlider->value(0.30);
		pUI->m_JgSlider->value(0.30);
		pUI->m_JbSlider->value(0.30);
		pUI->m_JhSlider->value(0.00);
		pUI->m_JsSlider->value(0.00);
		pUI->m_JvSlider->value(0.00);

		pUI->m_ThresSlider->deactivate();
		pUI->m_CurveSlider->deactivate();
		pUI->m_BlurSlider->deactivate();
		pUI->m_GridSizeSlider->deactivate();
		pUI->m_MinStrokeSlider->deactivate();
		pUI->m_MaxStrokeSlider->deactivate();
		pUI->m_Alpha2Slider->deactivate();
		pUI->m_LayersSlider->deactivate();
		pUI->m_R0LevelSlider->deactivate();
		pUI->m_JrSlider->deactivate();
		pUI->m_JgSlider->deactivate();
		pUI->m_JbSlider->deactivate();
		pUI->m_JhSlider->deactivate();
		pUI->m_JsSlider->deactivate();
		pUI->m_JvSlider->deactivate();
		break;
	case POINTILLIST:
		pUI->m_ThresSlider->value(100);
		pUI->m_CurveSlider->value(1.00);
		pUI->m_BlurSlider->value(0.50);
		pUI->m_GridSizeSlider->value(1.00);
		pUI->m_MinStrokeSlider->value(0);
		pUI->m_MaxStrokeSlider->value(0);
		pUI->m_Alpha2Slider->value(1.00);
		pUI->m_LayersSlider->value(2);
		pUI->m_R0LevelSlider->value(2);
		pUI->m_JrSlider->value(0.00);
		pUI->m_JgSlider->value(0.00);
		pUI->m_JbSlider->value(0.00);
		pUI->m_JhSlider->value(0.30);
		pUI->m_JsSlider->value(0.00);
		pUI->m_JvSlider->value(1.00);

		pUI->m_ThresSlider->deactivate();
		pUI->m_CurveSlider->deactivate();
		pUI->m_BlurSlider->deactivate();
		pUI->m_GridSizeSlider->deactivate();
		pUI->m_MinStrokeSlider->deactivate();
		pUI->m_MaxStrokeSlider->deactivate();
		pUI->m_Alpha2Slider->deactivate();
		pUI->m_LayersSlider->deactivate();
		pUI->m_R0LevelSlider->deactivate();
		pUI->m_JrSlider->deactivate();
		pUI->m_JgSlider->deactivate();
		pUI->m_JbSlider->deactivate();
		pUI->m_JhSlider->deactivate();
		pUI->m_JsSlider->deactivate();
		pUI->m_JvSlider->deactivate();
		break;
	case CUSTOMIZE:
		pUI->m_ThresSlider->activate();
		pUI->m_CurveSlider->activate();
		pUI->m_BlurSlider->activate();
		pUI->m_GridSizeSlider->activate();
		pUI->m_MinStrokeSlider->activate();
		pUI->m_MaxStrokeSlider->activate();
		pUI->m_Alpha2Slider->activate();
		pUI->m_LayersSlider->activate();
		pUI->m_R0LevelSlider->activate();
		pUI->m_JrSlider->activate();
		pUI->m_JgSlider->activate();
		pUI->m_JbSlider->activate();
		pUI->m_JhSlider->activate();
		pUI->m_JsSlider->activate();
		pUI->m_JvSlider->activate();
		break;
	default:
		break;

	}

	pDoc->setPaintStyle(style);
}

void ImpressionistUI::cb_strokeChoice(Fl_Widget* o, void* v){

}

void ImpressionistUI::cb_RunButton(Fl_Widget* o, void* v){

}

void	ImpressionistUI::cb_thresSlides(Fl_Widget* o, void* v){
	
	((ImpressionistUI*)(o->user_data()))->m_nThres = int(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_curveSlides(Fl_Widget* o, void* v){
	
	((ImpressionistUI*)(o->user_data()))->m_nCurve = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_blurSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nBlur = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_gridSizeSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nGridSize = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_minStrokeSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nMinStroke = int(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_maxStrokeSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nMaxStroke = int(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_alpha2Slides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nAlpha2 = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_layersSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nLayers = int(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_r0LevelSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nR0Level = int(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_jrSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nJr = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_jgSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nJg = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_jbSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nJb = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_jhSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nJh = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_jsSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nJs = double(((Fl_Slider *)o)->value());

}

void	ImpressionistUI::cb_jvSlides(Fl_Widget* o, void* v){

	((ImpressionistUI*)(o->user_data()))->m_nJv = double(((Fl_Slider *)o)->value());

}

//----------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------------------




//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist for COMP4411, Fall 2015\n Authored by Gary Wen");
}



//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush size
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

//------------------------------------------------
// Return the brush width
//------------------------------------------------
int ImpressionistUI::getWidth()
{
	return m_nLineWidth;
}


//------------------------------------------------
// Return the brush angle
//------------------------------------------------
int ImpressionistUI::getAngle()
{
	return m_nLineAngle;
}

//------------------------------------------------
// Return the brush alpha value
//------------------------------------------------
double ImpressionistUI::getAlpha()
{
	return m_nAlpha;
}

//------------------------------------------------
// Return the edge threshold value
//------------------------------------------------
int ImpressionistUI::getEdgeThres()
{
	return m_nEdgeThres;
}

//------------------------------------------------
// Return the dissolved image alpha value
//------------------------------------------------
double ImpressionistUI::getDimmedAlpha()
{
	return m_nDimmedAlpha;
}

//-------------------------------------------------
// Set the brush size
//-------------------------------------------------
void ImpressionistUI::setSize( int size )
{
	m_nSize=size;

	if (size<=40) 
		m_BrushSizeSlider->value(m_nSize);
	else
		m_BrushSizeSlider->value(40);

}

//---------------------------------------------------------
// Returns the alpha value of the brush.
//---------------------------------------------------------
int ImpressionistUI::getSpacing()
{
	return m_nSpacing;
}

//-------------------------------------------------
// Set the brush angle
//-------------------------------------------------
void ImpressionistUI::setAngle(int angle)
{
	m_nLineAngle = angle;
	if (m_nLineAngle < 0)
		m_nLineAngle += 360;

	m_LineAngleSlider->value(m_nLineAngle);
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas",	FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas },
		{ "&Undo",		    FL_ALT + 'u', (Fl_Callback *)ImpressionistUI::cb_undo, 0, FL_MENU_DIVIDER },
		
		{ "&Colors...",		FL_ALT + 'k', (Fl_Callback *)ImpressionistUI::cb_colors}, 
		{ "&Paintly...",	FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_paintly, 0, FL_MENU_DIVIDER },

		{ "Load Edge Image...",		FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_load_edge_image },
		{ "Load Another Image...",  FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_load_another_image },
		{ "Load Dissolve Image...",	FL_ALT + 'd', (Fl_Callback *)ImpressionistUI::cb_load_dissolve_image, 0, FL_MENU_DIVIDER },
		{ "&Quit",			 FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },

	{ "&Display", 0, 0, 0, FL_SUBMENU },
		{ "&Original Image", FL_ALT + 'o', (Fl_Callback *)ImpressionistUI::cb_originalImage },
		{ "&Edge Image",	 FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_edge_image },
		{ "&Another Image",  FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_another_image },
		{ 0 },

	{ "&Options", 0, 0, 0, FL_SUBMENU },
		{ "&Faster", FL_ALT + 'f', (Fl_Callback *)ImpressionistUI::cb_faster },
		{ "&Safer",  FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_safer },
		{ 0 },

	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  { "Love",				FL_ALT+'o', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LOVE },
  { "Filter",			FL_ALT+'f', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_FILTER },
  {0}
};


// Stroke Direction menu definition
Fl_Menu_Item ImpressionistUI::strokeDirMenu[] = {
	{ "Slider/Right Mouse", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_strokeDirChoice, (void *)ONE },
	{ "Gradient", FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirChoice, (void *)TWO },
	{ "Brush Direction", FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirChoice, (void *)THREE },
	{ 0 }
};



/*
// Color Space choice menu definition
Fl_Menu_Item ImpressionistUI::colorSpaceMenu[] = {
	{ "rgb", NULL, (Fl_Callback *)ImpressionistUI::cb_colorSpaceChoice, (void *)ONE},
	{ "byte", NULL, (Fl_Callback *)ImpressionistUI::cb_colorSpaceChoice, (void *)TWO },
	{ "hex", NULL, (Fl_Callback *)ImpressionistUI::cb_colorSpaceChoice, (void *)THREE },
	{ "hsv", NULL, (Fl_Callback *)ImpressionistUI::cb_colorSpaceChoice, (void *)FOUR },
	{ 0 }
};
*/

// style menu definition
Fl_Menu_Item ImpressionistUI::styleMenu[] = {
	{ "Impressionist", FL_ALT + 'i', (Fl_Callback *)ImpressionistUI::cb_styleChoice, (void *)IMPRESSIONIST },
	{ "Expressionist", FL_ALT + 'e', (Fl_Callback *)ImpressionistUI::cb_styleChoice, (void *)EXPRESSIONIST },
	{ "Color Wash", FL_ALT + 'w', (Fl_Callback *)ImpressionistUI::cb_styleChoice, (void *)COLOR_WASH },
	{ "Pointillist", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_styleChoice, (void *)POINTILLIST },
	{ "Customize", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_styleChoice, (void *)CUSTOMIZE },
	{ 0 }
};

// stroke menu definition
Fl_Menu_Item ImpressionistUI::strokeMenu[] = {
	{ "Curve Brush", FL_ALT + 'r', (Fl_Callback *)ImpressionistUI::cb_strokeChoice, (void *)ONE },
	{ "BSpline Brush", FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeChoice, (void *)TWO },
	{ "Circle Brush", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_strokeChoice, (void *)THREE },
	{ "Clip Line Brush", FL_ALT + 'p', (Fl_Callback *)ImpressionistUI::cb_strokeChoice, (void *)FOUR },
	{ "Line Brush", FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_strokeChoice, (void *)FIVE },
	{ 0 }
};







//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(610, 310, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 610, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 610, 285);

			// install paint view window
			m_paintView = new PaintView(300, 25, 305, 285, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 305, 285, "This is the origin view");//305jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values
	// Brushes
	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlpha = 1.00;
	m_bEdgeClipping = TRUE;
	m_bAnotherGrad = FALSE;
	m_nSpacing = 4;
	m_bSizeRand = TRUE;
	m_nEdgeThres = 200;
	m_nDimmedAlpha = 0.00;
	//Paintly
	 

	// brush dialog definition
	m_brushDialog = new Fl_Window(415, 370, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(50,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->labelfont();
		m_BrushTypeChoice->callback(cb_brushChoice);

		//Stroke direction
		m_StrokeDirChoice = new Fl_Choice(110, 45, 160, 25, "&Stroke Direction");
		m_StrokeDirChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_StrokeDirChoice->menu(strokeDirMenu);
		m_StrokeDirChoice->deactivate();
		m_StrokeDirChoice->callback(cb_strokeDirChoice);

		//clear canvas button
		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);


		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(0);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);


		// Add line width slider to the dialog 
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->deactivate();
		m_LineWidthSlider->callback(cb_lineWidthSlides);


		// Add line angle slider to the dialog 
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Angle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_LineAngleSlider->labelfont(FL_COURIER);
		m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->deactivate();
		m_LineAngleSlider->callback(cb_lineAngleSlides);


		// alpha slider 
		m_AlphaSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha");
		m_AlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaSlider->labelfont(FL_COURIER);
		m_AlphaSlider->labelsize(12);
		m_AlphaSlider->minimum(0.00);
		m_AlphaSlider->maximum(1.00);
		m_AlphaSlider->step(0.01);
		m_AlphaSlider->value(m_nAlpha);
		m_AlphaSlider->align(FL_ALIGN_RIGHT);
		m_AlphaSlider->callback(cb_alphaSlides);

		// edge-clipping light button
		m_EdgeClippingButton = new Fl_Light_Button(10, 200, 140, 25, "&Edge Clipping");
		m_EdgeClippingButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_EdgeClippingButton->value(m_bEdgeClipping);
		m_EdgeClippingButton->deactivate();
		m_EdgeClippingButton->callback(cb_EdgeClippingButton);

		// another gradient light button
		m_AnotherGradientButton = new Fl_Light_Button(200, 200, 160, 25, "&Another Gradient");
		m_AnotherGradientButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_AnotherGradientButton->deactivate();
		m_AnotherGradientButton->callback(cb_AnotherGradientButton);

		// Box 1
		m_SpacingBox = new Fl_Box(FL_THIN_UP_BOX, 10, 235, 385, 40,NULL);
		// Spacing slider 
		m_SpacingSlider = new Fl_Value_Slider(20, 245, 145, 20, "Spacing");
		m_SpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_SpacingSlider->type(FL_HOR_NICE_SLIDER);
		m_SpacingSlider->labelfont(FL_COURIER);
		m_SpacingSlider->labelsize(12);
		m_SpacingSlider->minimum(1);
		m_SpacingSlider->maximum(16);
		m_SpacingSlider->step(1);
		m_SpacingSlider->value(m_nSpacing);
		m_SpacingSlider->align(FL_ALIGN_RIGHT);
		m_SpacingSlider->callback(cb_spacingSlides);
		// Size Rand light button
		m_SizeRandButton = new Fl_Light_Button(225, 243, 95, 25, "&Size Rand.");
		m_SizeRandButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_SizeRandButton->value(m_bSizeRand);
		m_SizeRandButton->callback(cb_SizeRandButton);
		// Paint button
		m_PaintButton = new Fl_Button(330, 243, 45, 25, "&Paint");
		m_PaintButton->user_data((void*)(this));
		m_PaintButton->callback(cb_PaintButton);
		
		// Box 2
		m_EdgeThresBox = new Fl_Box(FL_THIN_UP_BOX, 10, 280, 385, 40, NULL);
		// Spacing slider 
		m_EdgeThresSlider = new Fl_Value_Slider(20, 290, 200, 20, "Edge Threshold");
		m_EdgeThresSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_EdgeThresSlider->type(FL_HOR_NICE_SLIDER);
		m_EdgeThresSlider->labelfont(FL_COURIER);
		m_EdgeThresSlider->labelsize(12);
		m_EdgeThresSlider->minimum(0);
		m_EdgeThresSlider->maximum(500);
		m_EdgeThresSlider->step(1);
		m_EdgeThresSlider->value(m_nEdgeThres);
		m_EdgeThresSlider->align(FL_ALIGN_RIGHT);
		m_EdgeThresSlider->callback(cb_edgeThresSlides);
		// Do it button
		m_DoItButton = new Fl_Button(330, 288, 45, 25, "&Do it");
		m_DoItButton->user_data((void*)(this));
		m_DoItButton->callback(cb_DoItButton);

		// swap content button
		m_PaintButton = new Fl_Button(285, 45, 45, 25, "&Swap");
		m_PaintButton->user_data((void*)(this));
		m_PaintButton->callback(cb_SwapContentButton);

		// Dimmed alpha slider for the original image to stay in the background
		m_DimmedAlphaSlider = new Fl_Value_Slider(20, 325, 200, 25, "DimAlpha");
		m_DimmedAlphaSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_DimmedAlphaSlider->type(FL_HOR_NICE_SLIDER);
		m_DimmedAlphaSlider->labelfont(FL_COURIER);
		m_DimmedAlphaSlider->labelsize(12);
		m_DimmedAlphaSlider->minimum(0.00);
		m_DimmedAlphaSlider->maximum(1.00);
		m_DimmedAlphaSlider->step(0.01);
		m_DimmedAlphaSlider->value(m_nDimmedAlpha);
		m_DimmedAlphaSlider->align(FL_ALIGN_RIGHT);
		m_DimmedAlphaSlider->callback(cb_DimmedAlphaSlides);

    m_brushDialog->end();	





	// colors dialog definition
	m_colorsDialog = new Fl_Window(240, 245, "Colors Selection");
		// Color chooser
		m_colorChooser = new Fl_Color_Chooser(10, 20, 210, 200, "Color Blending");
		m_colorChooser->rgb(1.000, 1.000, 1.000);
	m_colorsDialog->end();



	// Paintly dialog definition
	m_paintlyDialog = new Fl_Window(415, 280, "Paintly Dialog");

		// style choice 
		m_styleChoice = new Fl_Choice(50, 10, 130, 20, "&Style");
		m_styleChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_styleChoice->menu(styleMenu);
		m_styleChoice->callback(cb_styleChoice);
		
		// Stroke choice 
		m_strokeChoice = new Fl_Choice(230, 10, 120, 20, "&Stroke");
		m_strokeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_strokeChoice->menu(strokeMenu);
		m_strokeChoice->callback(cb_strokeChoice); 

		// Run Button
		m_RunButton = new Fl_Button(360, 10, 40, 20, "&Run");
		m_RunButton->user_data((void*)(this));
		m_RunButton->callback(cb_RunButton);

		// Fl Box
		m_PaintlyBox = new Fl_Box(FL_THIN_UP_BOX, 5, 35, 395, 230, NULL);

		// Threshold slider
		m_ThresSlider = new Fl_Value_Slider(15, 40, 200, 20, "Threshold");
		m_ThresSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_ThresSlider->type(FL_HOR_NICE_SLIDER);
		m_ThresSlider->labelfont(FL_COURIER);
		m_ThresSlider->labelsize(12);
		m_ThresSlider->minimum(0);
		m_ThresSlider->maximum(250);
		m_ThresSlider->step(1);
		m_ThresSlider->value(100);
		m_ThresSlider->align(FL_ALIGN_RIGHT);
		m_ThresSlider->deactivate();
		m_ThresSlider->callback(cb_thresSlides);

		// Curvature slider
		m_CurveSlider = new Fl_Value_Slider(15, 65, 200, 20, "Curvature");
		m_CurveSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_CurveSlider->type(FL_HOR_NICE_SLIDER);
		m_CurveSlider->labelfont(FL_COURIER);
		m_CurveSlider->labelsize(12);
		m_CurveSlider->minimum(0.00);
		m_CurveSlider->maximum(1.00);
		m_CurveSlider->step(0.01);
		m_CurveSlider->value(1.00);
		m_CurveSlider->align(FL_ALIGN_RIGHT);
		m_CurveSlider->deactivate();
		m_CurveSlider->callback(cb_curveSlides);

		// Blur slider
		m_BlurSlider = new Fl_Value_Slider(15, 90, 200, 20, "Blur");
		m_BlurSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BlurSlider->type(FL_HOR_NICE_SLIDER);
		m_BlurSlider->labelfont(FL_COURIER);
		m_BlurSlider->labelsize(12);
		m_BlurSlider->minimum(0.00);
		m_BlurSlider->maximum(1.00);
		m_BlurSlider->step(0.01);
		m_BlurSlider->value(0.50);
		m_BlurSlider->align(FL_ALIGN_RIGHT);
		m_BlurSlider->deactivate();
		m_BlurSlider->callback(cb_blurSlides);

		// Grid Size slider
		m_GridSizeSlider = new Fl_Value_Slider(15, 115, 200, 20, "Grid Size");
		m_GridSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_GridSizeSlider->type(FL_HOR_NICE_SLIDER);
		m_GridSizeSlider->labelfont(FL_COURIER);
		m_GridSizeSlider->labelsize(12);
		m_GridSizeSlider->minimum(0.00);
		m_GridSizeSlider->maximum(1.00);
		m_GridSizeSlider->step(0.01);
		m_GridSizeSlider->value(1.00);
		m_GridSizeSlider->align(FL_ALIGN_RIGHT);
		m_GridSizeSlider->deactivate();
		m_GridSizeSlider->callback(cb_gridSizeSlides);

		// Min Stroke L slider
		m_MinStrokeSlider = new Fl_Value_Slider(15, 140, 200, 20, "MinStrokeL");
		m_MinStrokeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_MinStrokeSlider->type(FL_HOR_NICE_SLIDER);
		m_MinStrokeSlider->labelfont(FL_COURIER);
		m_MinStrokeSlider->labelsize(12);
		m_MinStrokeSlider->minimum(0);
		m_MinStrokeSlider->maximum(30);
		m_MinStrokeSlider->step(1);
		m_MinStrokeSlider->value(4);
		m_MinStrokeSlider->align(FL_ALIGN_RIGHT);
		m_MinStrokeSlider->deactivate();
		m_MinStrokeSlider->callback(cb_minStrokeSlides);

		// Max Stroke L slider
		m_MaxStrokeSlider = new Fl_Value_Slider(15, 165, 200, 20, "MaxStrokeL");
		m_MaxStrokeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_MaxStrokeSlider->type(FL_HOR_NICE_SLIDER);
		m_MaxStrokeSlider->labelfont(FL_COURIER);
		m_MaxStrokeSlider->labelsize(12);
		m_MaxStrokeSlider->minimum(0);
		m_MaxStrokeSlider->maximum(30);
		m_MaxStrokeSlider->step(1);
		m_MaxStrokeSlider->value(16);
		m_MaxStrokeSlider->align(FL_ALIGN_RIGHT);
		m_MaxStrokeSlider->deactivate();
		m_MaxStrokeSlider->callback(cb_maxStrokeSlides);

		// Alpha slider
		m_Alpha2Slider = new Fl_Value_Slider(15, 190, 200, 20, "Alpha");
		m_Alpha2Slider->user_data((void*)(this));	// record self to be used by static callback functions
		m_Alpha2Slider->type(FL_HOR_NICE_SLIDER);
		m_Alpha2Slider->labelfont(FL_COURIER);
		m_Alpha2Slider->labelsize(12);
		m_Alpha2Slider->minimum(0.00);
		m_Alpha2Slider->maximum(1.00);
		m_Alpha2Slider->step(0.01);
		m_Alpha2Slider->value(1.00);
		m_Alpha2Slider->align(FL_ALIGN_RIGHT);
		m_Alpha2Slider->deactivate();
		m_Alpha2Slider->callback(cb_alpha2Slides);

		// Layers slider
		m_LayersSlider = new Fl_Value_Slider(15, 215, 200, 20, "Layers");
		m_LayersSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LayersSlider->type(FL_HOR_NICE_SLIDER);
		m_LayersSlider->labelfont(FL_COURIER);
		m_LayersSlider->labelsize(12);
		m_LayersSlider->minimum(1);
		m_LayersSlider->maximum(5);
		m_LayersSlider->step(1);
		m_LayersSlider->value(3);
		m_LayersSlider->align(FL_ALIGN_RIGHT);
		m_LayersSlider->deactivate();
		m_LayersSlider->callback(cb_layersSlides);

		// R0 Level slider
		m_R0LevelSlider = new Fl_Value_Slider(15, 240, 200, 20, "R0 Level");
		m_R0LevelSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_R0LevelSlider->type(FL_HOR_NICE_SLIDER);
		m_R0LevelSlider->labelfont(FL_COURIER);
		m_R0LevelSlider->labelsize(12);
		m_R0LevelSlider->minimum(0);
		m_R0LevelSlider->maximum(5);
		m_R0LevelSlider->step(1);
		m_R0LevelSlider->value(3);
		m_R0LevelSlider->align(FL_ALIGN_RIGHT);
		m_R0LevelSlider->deactivate();
		m_R0LevelSlider->callback(cb_r0LevelSlides);

		// Jr slider
		m_JrSlider = new Fl_Value_Slider(300, 40, 25, 90, "Jr");
		m_JrSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_JrSlider->type(FL_VERT_NICE_SLIDER);
		m_JrSlider->labelfont(FL_COURIER);
		m_JrSlider->labelsize(12);
		m_JrSlider->minimum(0.00);
		m_JrSlider->maximum(1.00);
		m_JrSlider->step(0.01);
		m_JrSlider->value(0.00);
		m_JrSlider->align(FL_ALIGN_BOTTOM);
		m_JrSlider->deactivate();
		m_JrSlider->callback(cb_jrSlides);

		// Jg slider
		m_JgSlider = new Fl_Value_Slider(330, 40, 25, 90, "Jg");
		m_JgSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_JgSlider->type(FL_VERT_NICE_SLIDER);
		m_JgSlider->labelfont(FL_COURIER);
		m_JgSlider->labelsize(12);
		m_JgSlider->minimum(0.00);
		m_JgSlider->maximum(1.00);
		m_JgSlider->step(0.01);
		m_JgSlider->value(0.00);
		m_JgSlider->align(FL_ALIGN_BOTTOM);
		m_JgSlider->deactivate();
		m_JgSlider->callback(cb_jgSlides);

		// Jb slider
		m_JbSlider = new Fl_Value_Slider(360, 40, 25, 90, "Jb");
		m_JbSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_JbSlider->type(FL_VERT_NICE_SLIDER);
		m_JbSlider->labelfont(FL_COURIER);
		m_JbSlider->labelsize(12);
		m_JbSlider->minimum(0.00);
		m_JbSlider->maximum(1.00);
		m_JbSlider->step(0.01);
		m_JbSlider->value(0.00);
		m_JbSlider->align(FL_ALIGN_BOTTOM);
		m_JbSlider->deactivate();
		m_JbSlider->callback(cb_jbSlides);

		// Jh slider
		m_JhSlider = new Fl_Value_Slider(300, 150, 25, 90, "Jh");
		m_JhSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_JhSlider->type(FL_VERT_NICE_SLIDER);
		m_JhSlider->labelfont(FL_COURIER);
		m_JhSlider->labelsize(12);
		m_JhSlider->minimum(0.00);
		m_JhSlider->maximum(1.00);
		m_JhSlider->step(0.01);
		m_JhSlider->value(0.00);
		m_JhSlider->align(FL_ALIGN_BOTTOM);
		m_JhSlider->deactivate();
		m_JhSlider->callback(cb_jhSlides);

		// Js slider
		m_JsSlider = new Fl_Value_Slider(330, 150, 25, 90, "Js");
		m_JsSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_JsSlider->type(FL_VERT_NICE_SLIDER);
		m_JsSlider->labelfont(FL_COURIER);
		m_JsSlider->labelsize(12);
		m_JsSlider->minimum(0.00);
		m_JsSlider->maximum(1.00);
		m_JsSlider->step(0.01);
		m_JsSlider->value(0.00);
		m_JsSlider->align(FL_ALIGN_BOTTOM);
		m_JsSlider->deactivate();
		m_JsSlider->callback(cb_jsSlides);

		// Jv slider
		m_JvSlider = new Fl_Value_Slider(360, 150, 25, 90, "Jv");
		m_JvSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_JvSlider->type(FL_VERT_NICE_SLIDER);
		m_JvSlider->labelfont(FL_COURIER);
		m_JvSlider->labelsize(12);
		m_JvSlider->minimum(0.00);
		m_JvSlider->maximum(1.00);
		m_JvSlider->step(0.01);
		m_JvSlider->value(0.00);
		m_JvSlider->align(FL_ALIGN_BOTTOM);
		m_JvSlider->deactivate();
		m_JvSlider->callback(cb_jvSlides);

	m_paintlyDialog->end();


}
