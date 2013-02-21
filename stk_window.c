#include <stk_window.h>

stk_widget *stk_window_new(int x, int y, uint w, uint h, const char *title, void *func, void *args)
{
    stk_widget *new_win  = (stk_widget*) malloc(sizeof(stk_widget));
    new_win->dsp = display;

    if(new_win->dsp)
    {
      new_win->win = XCreateWindow(new_win->dsp, DefaultRootWindow(new_win->dsp), x, y, w, h,
                                           0, CopyFromParent, CopyFromParent, CopyFromParent,
    	                                                                               0, 0);

      new_win->mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask | StructureNotifyMask;
      XSelectInput(new_win->dsp, new_win->win, new_win->mask);
      XSetWindowBackground(new_win->dsp, new_win->win, 0xF2E6EB);
      new_win->func = func;
      new_win->args = args;
      new_win->handler = &stk_window_handle;

      if(title)
        stk_window_set_title(new_win, title);

      if(func)
        new_win->func = func;

      if(args)
        new_win->args = args;


      new_win->gc = XCreateGC(display, new_win->win, 0, 0);

      stk_widget_insert((void*)new_win); 

      return new_win;
    }
    else
      return NULL;
}


void stk_window_set_pos(stk_widget *win, uint x, uint y)
{
  stk_widget_set_pos(win, x, y);
}    

void stk_window_set_color(stk_widget *win, int color)
{
    stk_widget_set_color(win, color);
}

void stk_window_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;

  switch(event->type)
  {
    case Expose:
        break;
    case ButtonPress:
        XSetInputFocus(wg->dsp, wg->win, RevertToNone, CurrentTime);
        break;
    case ButtonRelease:
       /*if(wg->func)
           wg->func(wg->args);*/
      break;
  }
}

void stk_window_show(stk_widget *win)
{
    XMapWindow(win->dsp, win->win);
    XFlush(win->dsp);
}


void stk_window_set_title(stk_widget *win, const char *title)
{
    int rc = 0;
    /* This variable will store the newly created property. */
    XTextProperty window_title_property;

    /* translate the given string into an X property. */
    rc = XStringListToTextProperty((char**)&title,
                                       1,
                                       &window_title_property);
    XSetWMName(win->dsp, win->win, &window_title_property);
}
