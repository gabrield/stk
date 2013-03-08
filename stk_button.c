#include <stk_button.h>


stk_widget *stk_button_new(stk_widget *parent_win, int x, int y, uint w, uint h,
                                            char *label, void *func, void *args)
{
    stk_widget *new_bt  = (stk_widget*) malloc(sizeof(stk_widget));
    int screen;

    XGCValues gcval;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    
    memset(new_bt, 0, sizeof(stk_widget));
    
    
    new_bt->dsp = display;
    new_bt->fontname = STK_FONT_SIZE_7x13;

    screen = DefaultScreen(new_bt->dsp);
    fg = BlackPixel(new_bt->dsp, screen);
    bg = WhitePixel(new_bt->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    new_bt->gc2 = XCreateGC(new_bt->dsp, parent_win->win, GCForeground |
                                                  GCBackground, &gcval);

    setwinattr.backing_store = Always;

    new_bt->font_info = XLoadQueryFont(new_bt->dsp, new_bt->fontname);

    if(new_bt->fontname != NULL)
        XSetFont(display, new_bt->gc2, new_bt->font_info->fid);
    else
        perror("XLoadQueryFont");

    if(new_bt->dsp)
    {
        new_bt->win = XCreateSimpleWindow(new_bt->dsp, parent_win->win, x, y, w,
                                                                  h, 1, fg, bg);
        new_bt->mask =  ExposureMask | EnterWindowMask | LeaveWindowMask |
                                      ButtonPressMask | ButtonReleaseMask;

        XChangeWindowAttributes(new_bt->dsp, new_bt->win, CWBackingStore,
                                                            &setwinattr);
        XSetWindowBackground(new_bt->dsp, new_bt->win, 0xEDD8E0);
        XSelectInput( new_bt->dsp, new_bt->win, new_bt->mask);
        XMapWindow(new_bt->dsp, new_bt->win);


        new_bt->x = x;
        new_bt->y = y;
        new_bt->w = w;
        new_bt->h = h;

        new_bt->handler = &stk_button_handle;

        if(func)
            new_bt->pressfunc = func;

        if(args)
            new_bt->pargs = args;

        if(label)
            new_bt->label = label;

        stk_widget_insert((void*)new_bt); 

        return new_bt;
    }
    else
        return NULL;
}


void stk_button_expose(stk_widget *bt)
{
    int   width, wcenter, hcenter;
    XClearWindow(bt->dsp, bt->win);

    if(bt->label)
    {

        width = XTextWidth(bt->font_info, bt->label, strlen(bt->label));
        wcenter = (bt->w - width) / 2;
        hcenter = ((bt->font_info->descent + bt->font_info->ascent)/2) + (bt->h / 2);

        XDrawString(bt->dsp, bt->win, bt->gc2, wcenter, hcenter,
                                  bt->label, strlen(bt->label));
    }
    XFlush(bt->dsp);
}


void stk_button_redraw(int dtype, stk_widget *bt)
{ 

    switch(dtype)
    {
        case STK_BUTTON_EXPOSE:
            stk_button_expose(bt);
            break;

        case STK_BUTTON_PRESS:
            XSetInputFocus(bt->dsp, bt->win, RevertToNone, CurrentTime);
            XDrawRectangle(bt->dsp, bt->win, bt->gc2, 0, 0, bt->w - 1,
                                                            bt->h - 1);
             break;

        case STK_BUTTON_RELEASE:
             stk_button_expose(bt);
             break;

        case STK_BUTTON_ENTER:
        case STK_BUTTON_LEAVE:
        default:
            break;
    }
}



void stk_button_handle(STKEvent *event, void *warg)
{
    stk_widget *wg = (stk_widget*)warg;
    
    wg->ev  = event;
    
    switch(event->type)
    {
    case Expose:
        if(wg->exposefunc)
            wg->exposefunc(wg->exargs);
        stk_button_redraw(STK_BUTTON_EXPOSE, wg);
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
        if(event->xbutton.button == Button1)
            stk_button_redraw(STK_BUTTON_PRESS, wg);
        break;

    case ButtonRelease:
        if(event->xbutton.button == Button1)
        {
            if(wg->pressfunc)
                wg->pressfunc(wg->pargs);
        }
        stk_button_redraw(STK_BUTTON_RELEASE, wg);

        break;
        
    case MotionNotify:
        if(wg->movefunc)
            wg->movefunc(wg->margs);
        break;
    }
}
