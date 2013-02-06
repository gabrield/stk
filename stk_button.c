#include <stk_button.h>


stk_widget *stk_button_new(stk_widget *parent_win, int x, int y, uint w, uint h,
                                      const char *label, void *func, void *args)
{
    stk_widget *new_bt  = (stk_widget*) malloc(sizeof(stk_widget));
    int screen;

    XGCValues gcval;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    new_bt->dsp = display;
    new_bt->fontname = "7x13";

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
                                                                  h, 2, fg, bg);
        new_bt->mask =  ExposureMask | EnterWindowMask | LeaveWindowMask | ButtonPressMask | ButtonReleaseMask;

        XChangeWindowAttributes(new_bt->dsp, new_bt->win, CWBackingStore,
                                                            &setwinattr);
        XSetWindowBackground(new_bt->dsp, new_bt->win, 0x778899);
        XSelectInput( new_bt->dsp, new_bt->win, new_bt->mask);
        XMapWindow(new_bt->dsp, new_bt->win);


        new_bt->x = x;
        new_bt->y = y;
        new_bt->w = w;
        new_bt->h = h;

        new_bt->handler = &stk_button_handle;

        if(func)
            new_bt->func = func;

        if(args)
            new_bt->args = args;

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
        hcenter = (bt->font_info->descent) + (bt->h / 2);

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

  switch(event->type)
  {
    case Expose:
        stk_button_redraw(STK_BUTTON_EXPOSE, wg);
        break;
    case LeaveNotify:
        break;
    case ButtonPress:
        if(event->xbutton.button == Button1)
            stk_button_redraw(STK_BUTTON_PRESS, wg);
        break;
    case ButtonRelease:
        if(event->xbutton.button == Button1)
        {
            if(wg->func)
                wg->func(wg->args);
        }
        stk_button_redraw(STK_BUTTON_RELEASE, wg);
        break;
  }
}
