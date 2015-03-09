#include <stk_canvas.h>


stk_widget *stk_canvas_new(stk_widget *parent_win, int x, int y, uint w, uint h)
{
    stk_widget *new_pl  = (stk_widget*) malloc(sizeof(stk_widget));
    stk_canvas *pl  = (stk_canvas*) malloc(sizeof(stk_canvas));
    int screen, depth;

    XGCValues gplal;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    memset(new_pl, 0, sizeof(stk_widget));
    
    
    new_pl->dsp = display;
    new_pl->fontname = STK_FONT_SIZE_6x9;

    screen = DefaultScreen(new_pl->dsp);
    depth = DefaultDepth(new_pl->dsp, screen);
    fg = BlackPixel(new_pl->dsp, screen);
    bg = WhitePixel(new_pl->dsp, screen);
    
    gplal.foreground = fg;
    gplal.background = bg;
    gplal.line_width = 1;
    gplal.line_style = LineSolid;
    

    new_pl->gc2 = XCreateGC(new_pl->dsp, parent_win->win, GCForeground |
                          GCBackground|GCLineWidth|GCLineStyle, &gplal);

  
    gplal.foreground = bg;
    gplal.background = fg;

    new_pl->gc = XCreateGC(new_pl->dsp, parent_win->win, GCForeground |
                          GCBackground|GCLineWidth|GCLineStyle, &gplal);

    setwinattr.backing_store = Always;

    if(new_pl->dsp)
    {
        new_pl->win = XCreateSimpleWindow(new_pl->dsp, parent_win->win, x, y, w,
                                                                  h, 1, fg, bg);
        new_pl->mask = ExposureMask | EnterWindowMask | LeaveWindowMask |
                       PointerMotionMask | ButtonPressMask | ButtonReleaseMask;

        XChangeWindowAttributes(new_pl->dsp, new_pl->win, CWBackingStore,
                                                            &setwinattr);
        XSelectInput(new_pl->dsp, new_pl->win, new_pl->mask);
        XMapWindow(new_pl->dsp, new_pl->win);

        pl->pmap = XCreatePixmap(new_pl->dsp, new_pl->win, w, h, depth);
        XSetForeground(new_pl->dsp, new_pl->gc, 
                       WhitePixelOfScreen(DefaultScreenOfDisplay(new_pl->dsp)));
        XFillRectangle(new_pl->dsp, pl->pmap, new_pl->gc, 0, 0, w, h);
        
        stk_canvas_set_string_font(new_pl, new_pl->fontname);

        new_pl->x = x;
        new_pl->y = y;
        new_pl->w = w;
        new_pl->h = h;

        new_pl->handler = &stk_canvas_handle;
        new_pl->ext_struct = (void*)pl;

        stk_widget_insert((void*)new_pl); 

        return new_pl;
    }
    else
        return NULL;
}


void stk_canvas_expose(stk_widget *pl)
{
    stk_canvas *spl = (stk_canvas*)pl->ext_struct;

    XCopyArea(pl->dsp, spl->pmap, pl->win, pl->gc2, 0, 0, pl->w, pl->h, 0, 0);
    XFlush(pl->dsp);
}


void stk_canvas_draw_arc(stk_widget *pl, uint x, uint y, uint w, uint h,
                                               uint angle0, uint angle1)
{
    stk_canvas *spl = (stk_canvas*)pl->ext_struct;
    XDrawArc(pl->dsp, spl->pmap, pl->gc2, x, y, w, h, angle0, angle1);
    stk_canvas_expose(pl);
} 


void stk_canvas_draw_string(stk_widget *pl, uint x, uint y, char *str)
{
	stk_canvas *spl = (stk_canvas*)pl->ext_struct;
	XDrawString(pl->dsp, spl->pmap, pl->gc2, x, y, str, strlen(str));
	stk_canvas_expose(pl);
}


void stk_canvas_draw_line(stk_widget *pl, uint x0, uint y0, uint x1, uint y1)
{
    stk_canvas *spl = (stk_canvas*)pl->ext_struct;
    XDrawLine(pl->dsp, spl->pmap, pl->gc2, x0, y0, x1, y1);
    stk_canvas_expose(pl);
}


void stk_canvas_draw_point(stk_widget *pl, uint x, uint y)
{
    stk_canvas *spl = (stk_canvas*)pl->ext_struct;
    XDrawPoint(pl->dsp, spl->pmap, pl->gc2, x, y);
    stk_canvas_expose(pl);
}


void stk_canvas_area_rotate(stk_widget *pl, uint x0 , uint y0, uint x1, uint y1,
                                                                     uint angle)
{
}             


void stk_canvas_set_string_font_size(stk_widget *pl, char *size)
{
	stk_widget_set_font_size(pl, size);
}


void stk_canvas_set_string_font(stk_widget *pl, char *font)
{
	stk_widget_set_font_size(pl, font);
}


void stk_canvas_redraw(int dtype, stk_widget *pl)
{ 
    switch(dtype)
    {
        case STK_CANVAS_EXPOSE:
            stk_canvas_expose(pl);
            break;

        case STK_CANVAS_PRESS:
             break;

        case STK_CANVAS_RELEASE:
             break;

        case STK_CANVAS_ENTER:
        case STK_CANVAS_LEAVE:
        case STK_CANVAS_MOVE:
        default:
            break;
    }
}



void stk_canvas_handle(STKEvent *event, void *warg)
{
    stk_widget *wg = (stk_widget*)warg;
    
    wg->ev  = event;
    
    switch(event->type)
    {
    case Expose:
        if(wg->exposefunc)
            wg->exposefunc(wg->exargs);
        stk_canvas_redraw(STK_CANVAS_EXPOSE, wg);
        break;
    
    case EnterNotify:
        if(wg->enterfunc)
            wg->enterfunc(wg->eargs);
        break;
        
    case LeaveNotify:
        if(wg->leavefunc)
            wg->leavefunc(wg->largs);
        break;
        
    case ButtonPress:
        if(wg->pressfunc)
            wg->pressfunc(wg->pargs);
        break;
        
    case ButtonRelease:
        if(wg->releasefunc)
            wg->releasefunc(wg->rargs);
        break;
        
    case MotionNotify:
        if(wg->movefunc)
            wg->movefunc(wg->margs);
        break;
    }
}
