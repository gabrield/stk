#include <stk_button.h>

stk_widget *stk_button_new(stk_widget *parent_win, int x, int y, uint w, uint h, void *func, void *args)
{
    stk_widget *new_bt  = (stk_widget*) malloc(sizeof(stk_widget));
    int                   screen;
    GC                    gc, gc2;
    XGCValues             gcval;
    long                  fg, bg;
    XFontStruct*          font_info;
    char* fontname =      "9x15";
    XSetWindowAttributes  setwinattr;
    new_bt->dsp = display;


    screen = DefaultScreen(new_bt->dsp );
    fg = BlackPixel(new_bt->dsp, screen);
    bg = WhitePixel(new_bt->dsp, screen);
    
    gcval.foreground = fg;
    gcval.background = bg;
    gc2 = XCreateGC(new_bt->dsp, parent_win->win, GCForeground | GCBackground, &gcval);

    gcval.foreground = bg;
    gcval.background = fg;  
    gc = XCreateGC(new_bt->dsp, parent_win->win, GCForeground | GCBackground, &gcval);

    setwinattr.backing_store = Always;


    if( (font_info = XLoadQueryFont(display, fontname)) != NULL)
        XSetFont(display, gc, font_info->fid);
    else
      perror("XLoadQueryFont");

    if(new_bt->dsp)
    {
      new_bt->win = XCreateSimpleWindow(new_bt->dsp, parent_win->win, x, y, w, h, 2, fg, bg);
      new_bt->mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask | StructureNotifyMask;
      XChangeWindowAttributes(new_bt->dsp, new_bt->win, CWBackingStore, &setwinattr);
      XSelectInput( new_bt->dsp, new_bt->win, new_bt->mask);
      XMapWindow(new_bt->dsp, new_bt->win);


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


void stk_button_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;

  switch(event->type)
  {
    case ButtonPress:
      break;
    case ButtonRelease:
       if(wg->func)
           wg->func(wg->args);
      break;
  }
}
