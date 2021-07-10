/* motif_example_2.c
 * 
 * Written by: M.Emmanuel
 * Written for: ad us. propr.
 * Date: 10/JUL/2021
 *
 * Description: Sample Motif Empty Window with a Drawing Canvas. Draws a line in the Canvas
 * 
 * Rev.	Date		Author		Description
 * -----------------------------------------------------------------------------------------------------------
 * 1	10/JUL/2021	M.Emmanuel	Initial coding
 */
 
#include <stdlib.h>
#include <stdio.h>
 
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
 
void draw_area(Widget widget, XtPointer client_data, XtPointer call_data);
 
int main(int argc, char *argv[]) {

	/* WIDGETS */
	XtAppContext	app;			/* Application Context */
	Widget		toplevel;		/* Top Level Button */
	Widget		drawing_area;		/* Drawing Area Widget */
	
	/* DRAWING AREA RELATED */
	XGCValues	gcv;
	GC		gc;
	
	/* RESOURCE VALUE ARRAYS/COUNT */
	Arg al[10];
	int ac;
	
	/* INITIALIZE TOP LEVEL WINDOW */
	XtSetLanguageProc(NULL, NULL, NULL);
	toplevel = XtVaOpenApplication( 
		&app, argv[0], NULL, 0, &argc, argv, NULL, sessionShellWidgetClass,
		XmNwidth, 400, XmNheight, 300, NULL
	);

	/* CREATE AND MANAGE DRAWING CANVAS WIDGET */
	ac=0; 
	drawing_area = XmCreateDrawingArea(toplevel, "drawing_area", al, ac);
		
	/* CREATE GRAPHICS CONTEXT */
	gcv.foreground = WhitePixelOfScreen(XtScreen(drawing_area));
	gcv.background = BlackPixelOfScreen(XtScreen(drawing_area));	
	gc = XCreateGC (
		XtDisplay(drawing_area),
		RootWindowOfScreen(XtScreen(drawing_area)), 
		(GCForeground | GCBackground), 
		&gcv);

	/* ASSIGN GRAPHICS CONTEXT */	
	XtVaSetValues(drawing_area, XmNuserData, gc, NULL);
	
	/* ASSIGN CALLBACKS AND MANAGE WIDGET */
	XtAddCallback(drawing_area, XmNexposeCallback, draw_area, NULL);
	XtManageChild(drawing_area);
		
	/* REALIZE TOPLEVEL WINDOW AND LAUNCH APPLICATION LOOP */
	XtRealizeWidget(toplevel);
	XtAppMainLoop(app);
	
	return 0;

}

void draw_area(Widget widget, XtPointer client_data, XtPointer call_data) {

	XmDrawingAreaCallbackStruct *cbs = (XmDrawingAreaCallbackStruct *) call_data;
	XEvent *event = cbs->event;
	Display *dpy = event->xany.display;
	GC gc;
	
	/* DRAW LINE */
	if(cbs->reason == XmCR_EXPOSE || cbs->reason == XmCR_ACTIVATE) {

		XtVaGetValues(widget, XmNuserData, &gc, NULL);
		XDrawLine(dpy, cbs->window, gc, 10, 10, 390, 290);

	}
}

