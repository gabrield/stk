#include <stk_progress_bar.h>


stk_widget *stk_progress_bar_new(stk_widget *parent_win, int x, int y, uint w, uint h, const char *label)
{
    stk_widget *new_pb  = (stk_widget*) malloc(sizeof(stk_widget));
    stk_progress_bar *pb  = (stk_progress_bar*) malloc(sizeof(stk_progress_bar));
    int screen;

    XGCValues gcval;
    long fg, bg;
    new_pb->dsp = display;
    new_pb->fontname = "7x13";

    screen = DefaultScreen(new_pb->dsp);
    fg = BlackPixel(new_pb->dsp, screen);
    bg = WhitePixel(new_pb->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;

    new_pb->gc2 = XCreateGC(new_pb->dsp, parent_win->win, GCForeground |
                                                  GCBackground, &gcval);


    if(new_pb->dsp)
    {
        new_pb->win = XCreateSimpleWindow(new_pb->dsp, parent_win->win, x, y, w,
                                                                  h, 2, fg, bg);

        new_pb->gc = XCreateGC(new_pb->dsp, new_pb->win, 0, 0);


        new_pb->font_info = XLoadQueryFont(new_pb->dsp, new_pb->fontname);

        if(new_pb->fontname != NULL)
            XSetFont(display, new_pb->gc2, new_pb->font_info->fid);
        else
            perror("XLoadQueryFont");

        new_pb->mask =  ExposureMask | EnterWindowMask | LeaveWindowMask | ButtonPressMask | ButtonReleaseMask;

        XSelectInput(new_pb->dsp, new_pb->win, new_pb->mask);
        


        if(DisplayPlanes(new_pb->dsp, screen) != 1)
        {
            pb->cmap = DefaultColormap(new_pb->dsp, screen);
            if(XAllocNamedColor(new_pb->dsp, pb->cmap, "red", &pb->color, &pb->colorrgb))
                    XSetForeground(new_pb->dsp, new_pb->gc, pb->color.pixel);
        }

        XMapWindow(new_pb->dsp, new_pb->win);
  //XFillRectangle(new_pb->dsp, new_pb->win, new_pb->gc, 0, 0, new_pb->w, new_pb->h);


        new_pb->x = x;
        new_pb->y = y;
        new_pb->w = w;
        new_pb->h = h;

        new_pb->handler = &stk_progress_bar_handle;
        new_pb->func = NULL;
        new_pb->ext_struct = (void*)pb;

        if(label)
            new_pb->label = label;
        else
            new_pb->label = NULL;

        stk_widget_insert((void*)new_pb); 

        return new_pb;
    }
    else
        return NULL;
}




void stk_progress_bar_expose(stk_widget *pb)
{
    int   width, wcenter, hcenter;
    stk_progress_bar *spb = (stk_progress_bar*)pb->ext_struct;

    XClearWindow(pb->dsp, pb->win);
    XFillRectangle(pb->dsp, pb->win, pb->gc, 0, 0, (pb->w * spb->pct)/100, pb->h);
    

    if(pb->label)
    {

        width = XTextWidth(pb->font_info, pb->label, strlen(pb->label));
        wcenter = (pb->w - width) / 2;
        hcenter = ((pb->font_info->descent + pb->font_info->ascent)/2) + (pb->h / 2);

        XDrawString(pb->dsp, pb->win, pb->gc2, wcenter, hcenter,
                                  pb->label, strlen(pb->label));
    }
    XFlush(pb->dsp);
}

void set(stk_widget *pb, uint pct)
{
    stk_progress_bar *spb = (stk_progress_bar*)pb->ext_struct;
    spb->pct = pct;
    stk_progress_bar_expose(pb);
}




void stk_progress_bar_redraw(int dtype, stk_widget *pb)
{ 

    switch(dtype)
    {
        case STK_PROGRESS_BAR_EXPOSE:
            stk_progress_bar_expose(pb);
            break;

        case STK_PROGRESS_BAR_PRESS:
        /*
            XSetInputFocus(pb->dsp, pb->win, RevertToNone, CurrentTime);
            XDrawRectangle(pb->dsp, pb->win, pb->gc2, 0, 0, pb->w - 1,
                                                            pb->h - 1);
        */
             break;

        case STK_PROGRESS_BAR_RELEASE:
             stk_progress_bar_expose(pb);
             printf("STK_PROGRESS_BAR_RELEASE\n");
             break;

        case STK_PROGRESS_BAR_ENTER:
        case STK_PROGRESS_BAR_LEAVE:
        default:
            break;
    }
}



void stk_progress_bar_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;

  switch(event->type)
  {
    case Expose:
        stk_progress_bar_redraw(STK_PROGRESS_BAR_EXPOSE, wg);
        break;
    case LeaveNotify:
        break;
    case ButtonPress:
        if(event->xbutton.button == Button1)
            stk_progress_bar_redraw(STK_PROGRESS_BAR_PRESS, wg);
        break;
    case ButtonRelease:
        if(event->xbutton.button == Button1)
        {
            if(wg->func)
                printf("FUNC\n");
        }
        stk_progress_bar_redraw(STK_PROGRESS_BAR_RELEASE, wg);
        break;
  }
}
