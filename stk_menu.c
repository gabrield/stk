#include <stk_menu.h>

stk_widget *stk_menu_new(stk_widget *parent_win, int x, int y, uint w, uint h,
                                                                  char *title)
{
    stk_widget *new_menu  = (stk_widget*) malloc(sizeof(stk_widget));
    
    memset(new_menu, 0, sizeof(stk_widget));
    
    new_menu->dsp = display;

    if(new_menu->dsp)
    {
        new_menu->win = XCreateSimpleWindow(new_menu->dsp, parent_win->win,
                                                x, y, w, h, 1, 0, 0);
        
        new_menu->mask = ExposureMask | ButtonPressMask | ButtonReleaseMask |
                  PointerMotionMask | KeyPressMask | StructureNotifyMask;
                
        XSelectInput(new_menu->dsp, new_menu->win, new_menu->mask);
        XSetWindowBackground(new_menu->dsp, new_menu->win, 0xd3d3d3);
        stk_menu_show(new_menu);
        
        new_menu->handler = &stk_menu_handle;
        
        new_menu->x = x;
        new_menu->y = y;
        new_menu->w = w;
        new_menu->h = h;
        
        
        if(title)
            stk_menu_set_title(new_menu, title);
        
        new_menu->gc = XCreateGC(display, new_menu->win, 0, 0);
        
        stk_widget_insert((void*)new_menu); 
        
        return new_menu;
    }
    else
      return NULL;
}

/*
void stk_menu_set_pos(stk_widget *menu, uint x, uint y)
{
  stk_widget_set_pos(win, x, y);
}    

void stk_menu_set_color(stk_widget *menu, int color)
{
    stk_widget_set_color(win, color);
}
*/

void stk_menu_handle(STKEvent *event, void *warg)
{
  stk_widget *wg = (stk_widget*)warg;
  stk_widget *wroot = stk_widget_root();

  switch(event->type)
  {
      case Expose:
          break;
      
      case ButtonPress:
          XResizeWindow(wg->dsp, wg->win, wg->w, wg->h+30);
         
          break;
      
      case ButtonRelease:
          XResizeWindow(wg->dsp, wg->win, wg->w, wg->h-30);
         /*if(wg->func)
             wg->func(wg->args);*/
          break;

      case ClientMessage:
          if(wg == wroot)
          {
              XDestroyWindow(wg->dsp, wg->win);
              /* close connection to server */
              XCloseDisplay(wg->dsp);
              exit(0);
          }
          else
          {
              XUnmapWindow(wg->dsp, wg->win);
              XFlush(wg->dsp);
          }

          break;
  }
}

void stk_menu_show(stk_widget *menu)
{
    XMapWindow(menu->dsp, menu->win);
    XFlush(menu->dsp);
}


void stk_menu_set_title(stk_widget *menu, const char *title)
{
    /* This variable will store the newly created property. */
    XTextProperty window_title_property;

    /* translate the given string into an X property. */
    XStringListToTextProperty((char**)&title,
                                       1,
                                       &window_title_property);
    XSetWMName(menu->dsp, menu->win, &window_title_property);
}
