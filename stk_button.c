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
    new_bt->fontname = "9x15bold";
    new_bt->label = label;

    screen = DefaultScreen(new_bt->dsp);
    fg = BlackPixel(new_bt->dsp, screen);
    bg = WhitePixel(new_bt->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    new_bt->gc2 = XCreateGC(new_bt->dsp, parent_win->win, GCForeground |
                                                  GCBackground, &gcval);

    gcval.foreground = bg;
    gcval.background = fg;  
    new_bt->gc = XCreateGC(new_bt->dsp, parent_win->win, GCForeground |
                                                 GCBackground, &gcval);

    setwinattr.backing_store = Always;

    new_bt->font_info = XLoadQueryFont(new_bt->dsp, new_bt->fontname);

    if(new_bt->fontname != NULL)
        XSetFont(display, new_bt->gc, new_bt->font_info->fid);
    else
      perror("XLoadQueryFont");

    if(new_bt->dsp)
    {
        new_bt->win = XCreateSimpleWindow(new_bt->dsp, parent_win->win, x, y, w,
                                                                  h, 2, fg, bg);
        new_bt->mask =  ExposureMask | EnterWindowMask | LeaveWindowMask | ButtonPressMask | ButtonReleaseMask;

        XChangeWindowAttributes(new_bt->dsp, new_bt->win, CWBackingStore,
                                                            &setwinattr);
        XSelectInput( new_bt->dsp, new_bt->win, new_bt->mask);
        XMapWindow(new_bt->dsp, new_bt->win);


        new_bt->x = x;
        new_bt->y = y;
        new_bt->w = w;
        new_bt->h = h;

        new_bt->func = func;
        new_bt->args = args;
        new_bt->handler = &stk_button_handle;

        if(func)
            new_bt->func = func;

        if(args)
           new_bt->args = args;

        stk_widget_insert((void*)new_bt); 

        return new_bt;
    }
    else
        return NULL;
}


void stk_button_expose(stk_widget *bt)
{
    int   width, center;
    XClearWindow(bt->dsp, bt->win);

    width = XTextWidth(bt->font_info, bt->label, strlen(bt->label));
    center = (bt->w - width) / 2;

    XDrawString(bt->dsp, bt->win, bt->gc2, center, bt->font_info->ascent,
                                           bt->label, strlen(bt->label));
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
        printf("Expose\n");
        stk_button_redraw(STK_BUTTON_EXPOSE, wg);
        break;
    case LeaveNotify:
        printf("LeaveNotify\n");
        break;
    case ButtonPress:
        printf("ButtonPress\n");
        stk_button_redraw(STK_BUTTON_PRESS, wg);
        break;
    case ButtonRelease:
        if(wg->func)
            wg->func(wg->args);
         stk_button_redraw(STK_BUTTON_RELEASE, wg);
        break;
  }
}
