#include <stk_text.h>


stk_widget *stk_text_new(stk_widget *parent_win, int x, int y, uint w, uint h,
                                                  const char *label, int type)
{
    stk_widget *new_txt  = (stk_widget*) malloc(sizeof(stk_widget));
    int screen;

    XGCValues gcval;
    long fg, bg;
    XSetWindowAttributes setwinattr;
    new_txt->dsp = display;
    new_txt->fontname = "7x13";

    screen = DefaultScreen(new_txt->dsp);
    fg = BlackPixel(new_txt->dsp, screen);
    bg = WhitePixel(new_txt->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    new_txt->gc2 = XCreateGC(new_txt->dsp, parent_win->win, GCForeground |
                                                  GCBackground, &gcval);

    setwinattr.backing_store = Always;

    new_txt->font_info = XLoadQueryFont(new_txt->dsp, new_txt->fontname);

    if(new_txt->fontname != NULL)
        XSetFont(display, new_txt->gc2, new_txt->font_info->fid);
    else
      perror("XLoadQueryFont");

    if(new_txt->dsp)
    {
        new_txt->win = XCreateSimpleWindow(new_txt->dsp, parent_win->win, x, y, w,
                                                                  h, 2, fg, bg);
        new_txt->mask =  ExposureMask | EnterWindowMask | LeaveWindowMask | ButtonPressMask | ButtonReleaseMask;

        XChangeWindowAttributes(new_txt->dsp, new_txt->win, CWBackingStore,
                                                            &setwinattr);
        
        XSelectInput( new_txt->dsp, new_txt->win, new_txt->mask);
        XMapWindow(new_txt->dsp, new_txt->win);


        new_txt->x = x;
        new_txt->y = y;
        new_txt->w = w;
        new_txt->h = h;


        new_txt->handler = &stk_text_handle;

        if(label)
            new_txt->label = label;
        else
            new_txt->label = NULL;

        stk_widget_insert((void*)new_txt); 

        return new_txt;
    }
    else
        return NULL;
}


void stk_text_expose(stk_widget *txt)
{
    int   width, wcenter, hcenter;
    XClearWindow(txt->dsp, txt->win);

    if(txt->label)
    {
        width = XTextWidth(txt->font_info, txt->label, strlen(txt->label));
        wcenter = (txt->w - width) / 2;
        hcenter = (txt->font_info->descent) + (txt->h / 2);

        XDrawString(txt->dsp, txt->win, txt->gc2, wcenter, hcenter,
                                  txt->label, strlen(txt->label));
    }
    XFlush(txt->dsp);
}


void stk_text_redraw(int dtype, stk_widget *txt)
{ 

    switch(dtype)
    {
        case STK_TEXT_EXPOSE:
            stk_text_expose(txt);
            break;

        case STK_TEXT_PRESS:
            break;

        case STK_TEXT_RELEASE:
            stk_text_expose(txt);
            break;

        case STK_TEXT_KEYPRESS:
            printf("STK_TEXT_KEYPRESS\n");
            break;

        case STK_TEXT_KEYRELEASE:
            printf("STK_TEXT_KEYRELEASE\n");
            stk_text_expose(txt);
            break;


        case STK_TEXT_ENTER:
        case STK_TEXT_LEAVE:
        default:
            break;
    }
}



void stk_text_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;

    switch(event->type)
    {
        case Expose:
            stk_text_redraw(STK_TEXT_EXPOSE, wg);
            break;
        case LeaveNotify:
            break;

        case ButtonPress:
            stk_text_redraw(STK_TEXT_PRESS, wg);
            break;

        case ButtonRelease:
            stk_text_redraw(STK_TEXT_RELEASE, wg);
            break;

        case KeyPress:
            stk_text_redraw(STK_TEXT_KEYPRESS, wg);
            break;

        case KeyRelease:
            stk_text_redraw(STK_TEXT_KEYRELEASE, wg);
            break;
    }
}
