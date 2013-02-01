#include <stk_window.h>

stk_widget *stk_window_new(int x, int y, uint w, uint h, void (*func), void *args)
{
    stk_widget *new_win  = (stk_widget*) malloc(sizeof(stk_widget));
    new_win->dsp = XOpenDisplay(0);

    if(new_win->dsp)
    {
      new_win->win = XCreateWindow(new_win->dsp, DefaultRootWindow(new_win->dsp), x, y, w, h,
                                           0, CopyFromParent, CopyFromParent, CopyFromParent,
    	                                                                               0, 0);

      new_win->mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask | StructureNotifyMask;
      XSelectInput( new_win->dsp, new_win->win, new_win->mask);
      new_win->func = func;
      new_win->args = args;
      new_win->handler = &stk_window_handle;

      if(func)
        new_win->func = func;

      if(args)
        new_win->args = args;

      stk_widget_insert((void*)new_win); 

      return new_win;
    }
    else
      return NULL;
}

void stk_window_add(stk_widget *win, stk_widget *widget)
{
  widget->dsp = win->dsp;
}

void stk_window_handle(STKEvent *event, void *warg)
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

void stk_window_show(stk_widget *win)
{
    XMapWindow(win->dsp, win->win);
    XFlush(win->dsp);
}
