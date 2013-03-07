#include <stk_canvas.h>


stk_widget *stk_canvas_new(stk_widget *parent_win, int x, int y, uint w, uint h)
{
    stk_widget *new_cv  = (stk_widget*) malloc(sizeof(stk_widget));
    stk_canvas *cv  = (stk_canvas*) malloc(sizeof(stk_canvas));
    int screen, depth;

    XGCValues gcval;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    new_cv->dsp = display;
    new_cv->fontname = STK_FONT_SIZE_6x9;

    screen = DefaultScreen(new_cv->dsp);
    depth = DefaultDepth(new_cv->dsp, screen);
    fg = BlackPixel(new_cv->dsp, screen);
    bg = WhitePixel(new_cv->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    gcval.line_width = 1;
    gcval.line_style = LineSolid;


    new_cv->gc2 = XCreateGC(new_cv->dsp, parent_win->win, GCForeground |
                          GCBackground|GCLineWidth|GCLineStyle, &gcval);

  
    gcval.foreground = bg;
    gcval.background = fg;

    new_cv->gc = XCreateGC(new_cv->dsp, parent_win->win, GCForeground |
                          GCBackground|GCLineWidth|GCLineStyle, &gcval);

    setwinattr.backing_store = Always;

    if(new_cv->dsp)
    {
        new_cv->win = XCreateSimpleWindow(new_cv->dsp, parent_win->win, x, y, w,
                                                                  h, 2, fg, bg);
        new_cv->mask = ExposureMask | EnterWindowMask | LeaveWindowMask |
                                     ButtonPressMask | ButtonReleaseMask;

        XChangeWindowAttributes(new_cv->dsp, new_cv->win, CWBackingStore,
                                                            &setwinattr);
        XSelectInput(new_cv->dsp, new_cv->win, new_cv->mask);
        XMapWindow(new_cv->dsp, new_cv->win);

        cv->pmap = XCreatePixmap(new_cv->dsp, new_cv->win, w, h, depth);
        XSetForeground(new_cv->dsp, new_cv->gc, 
                       WhitePixelOfScreen(DefaultScreenOfDisplay(new_cv->dsp)));
        XFillRectangle(new_cv->dsp, cv->pmap, new_cv->gc, 0, 0, w, h);
        
        stk_canvas_set_string_font(new_cv, new_cv->fontname);

        new_cv->x = x;
        new_cv->y = y;
        new_cv->w = w;
        new_cv->h = h;

        new_cv->handler = &stk_canvas_handle;
        new_cv->ext_struct = (void*)cv;

        stk_widget_insert((void*)new_cv); 

        return new_cv;
    }
    else
        return NULL;
}


void stk_canvas_expose(stk_widget *cv)
{
    stk_canvas *scv = (stk_canvas*)cv->ext_struct;

    XCopyArea(cv->dsp, scv->pmap, cv->win, cv->gc2, 0, 0, cv->w, cv->h, 0, 0);
    XFlush(cv->dsp);
}


void stk_canvas_draw_arc(stk_widget *cv, uint x, uint y, uint w, uint h,
                                               uint angle0, uint angle1)
{
    stk_canvas *scv = (stk_canvas*)cv->ext_struct;
    XDrawArc(cv->dsp, scv->pmap, cv->gc2, x, y, w, h, angle0, angle1);
    stk_canvas_expose(cv);
} 


void stk_canvas_draw_string(stk_widget *cv, uint x, uint y, char *str)
{
	stk_canvas *scv = (stk_canvas*)cv->ext_struct;
	XDrawString(cv->dsp, scv->pmap, cv->gc2, x, y, str, strlen(str));
	stk_canvas_expose(cv);
}


void stk_canvas_draw_line(stk_widget *cv, uint x0, uint y0, uint x1, uint y1)
{
    stk_canvas *scv = (stk_canvas*)cv->ext_struct;
    XDrawLine(cv->dsp, scv->pmap, cv->gc2, x0, y0, x1, y1);
    stk_canvas_expose(cv);
}


void stk_canvas_draw_point(stk_widget *cv, uint x, uint y)
{
    stk_canvas *scv = (stk_canvas*)cv->ext_struct;
    XDrawPoint(cv->dsp, scv->pmap, cv->gc2, x, y);
    stk_canvas_expose(cv);
}


void stk_canvas_set_string_font_size(stk_widget *cv, char *size)
{
	stk_widget_set_font_size(cv, size);
}


void stk_canvas_set_string_font(stk_widget *cv, char *font)
{
	stk_widget_set_font_size(cv, font);
}


void stk_canvas_redraw(int dtype, stk_widget *cv)
{ 
    switch(dtype)
    {
        case STK_CANVAS_EXPOSE:
            stk_canvas_expose(cv);
            break;

        case STK_CANVAS_PRESS:

              /*stk_canvas_draw_arc(cv, 50, 70, 150, 150, 10, 360*64);*/
             break;

        case STK_CANVAS_RELEASE:
             break;

        case STK_CANVAS_ENTER:
        case STK_CANVAS_LEAVE:
        default:
            break;
    }
}



void stk_canvas_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;

  switch(event->type)
  {
    case Expose:
        stk_canvas_redraw(STK_CANVAS_EXPOSE, wg);
        break;
    case LeaveNotify:
        break;
    case ButtonPress:
        //stk_canvas_redraw(STK_CANVAS_PRESS, wg);
        break;
    case ButtonRelease:
        //stk_canvas_redraw(STK_CANVAS_RELEASE, wg);
        break;
  }
}
