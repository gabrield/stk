#include <stk_window.h>

stk_widget *stk_window_new(int x, int y, uint w, uint h, void *func, void *args)
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

      stk_widget_insert((void*)new_win); 

      return new_win;
    }
}



void stk_window_handle(STKEvent *event, void *arg)
{
  switch(event->type)
  {
    case ButtonPress:
      printf("ButtonPress\n");
      break;
    case ButtonRelease:
       printf("ButtonRelease\n");
      break;
  }
}

void stk_window_show(stk_widget *win)
{
    XMapWindow(win->dsp, win->win);
    XFlush(win->dsp);
}
