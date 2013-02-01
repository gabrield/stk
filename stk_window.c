#include <stk_window.h>

stk_window *stk_window_new(int x, int y, uint w, uint h, void *func, void *args)
{
    stk_window *new_win  = (stk_window*) malloc(sizeof(stk_window));
    new_win->dsp = XOpenDisplay(0);

    if(new_win->dsp)
    {
      new_win->win = XCreateWindow(new_win->dsp, DefaultRootWindow(new_win->dsp), x, y, w, h,
                                           0, CopyFromParent, CopyFromParent, CopyFromParent,
    	                                                                               0, 0);
      new_win->func = func;
      new_win->args = args; 
      return new_win;
    }
}


void stk_window_show(stk_window *win)
{
    XMapWindow(win->dsp, win->win);
    XFlush(win->dsp);
}
