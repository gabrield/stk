#include <stk_canvas.h>


stk_widget *stk_canvas_new(stk_widget *parent_win, int x, int y, uint w, uint h)
{
    stk_widget *new_cv  = (stk_widget*) malloc(sizeof(stk_widget));
    int screen;

    XGCValues gcval;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    new_cv->dsp = display;
    new_cv->fontname = "7x13";

    screen = DefaultScreen(new_cv->dsp);
    fg = BlackPixel(new_cv->dsp, screen);
    bg = WhitePixel(new_cv->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    gcval.line_width = 1;
    gcval.line_style = LineSolid;


    new_cv->gc2 = XCreateGC(new_cv->dsp, parent_win->win, GCForeground |
                          GCBackground|GCLineWidth|GCLineStyle, &gcval);


    setwinattr.backing_store = Always;

    if(new_cv->dsp)
    {
        new_cv->win = XCreateSimpleWindow(new_cv->dsp, parent_win->win, x, y, w,
                                                                  h, 2, fg, bg);
        new_cv->mask = ExposureMask | EnterWindowMask | LeaveWindowMask | ButtonPressMask | ButtonReleaseMask;

        XChangeWindowAttributes(new_cv->dsp, new_cv->win, CWBackingStore,
                                                            &setwinattr);
        //XSetWindowBackground(new_cv->dsp, new_cv->win, 0xEDD8E0);
        XSelectInput( new_cv->dsp, new_cv->win, new_cv->mask);
        XMapWindow(new_cv->dsp, new_cv->win);


        new_cv->x = x;
        new_cv->y = y;
        new_cv->w = w;
        new_cv->h = h;

        new_cv->handler = &stk_canvas_handle;

        stk_widget_insert((void*)new_cv); 

        return new_cv;
    }
    else
        return NULL;
}



void stk_canvas_draw_line(stk_widget *cv, uint x0, uint y0, uint x1, uint y1)
{
    XDrawLine(cv->dsp, cv->win, cv->gc2, x0, y0, x1, y1);
}


void stk_canvas_expose(stk_widget *cv)
{
    stk_canvas_line(cv, 10, 10, 100, 100);
    
    /*
    int   width, wcenter, hcenter;
    XClearWindow(cv->dsp, cv->win);
    XDrawArc(display, cv->win, cv->gc2, 50, 70, 150, 150, 0, 360*64);

    if(cv->label)
    {

        width = XTextWidth(cv->font_info, cv->label, strlen(cv->label));
        wcenter = (cv->w - width) / 2;
        hcenter = ((cv->font_info->descent + cv->font_info->ascent)/2) + (cv->h / 2);

        XDrawString(cv->dsp, cv->win, cv->gc2, wcenter, hcenter,
                                  cv->label, strlen(cv->label));
    }
    XFlush(cv->dsp);
    */
}


void stk_canvas_redraw(int dtype, stk_widget *cv)
{ 
    switch(dtype)
    {
        case STK_CANVAS_EXPOSE:
            stk_canvas_expose(cv);
            break;

        case STK_CANVAS_PRESS:
              XDrawArc(display, cv->win, cv->gc2, 50, 70, 150, 150, 0, 360*64);
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
        stk_canvas_redraw(STK_CANVAS_PRESS, wg);
        break;
    case ButtonRelease:
        stk_canvas_redraw(STK_CANVAS_RELEASE, wg);
        break;
  }
}
