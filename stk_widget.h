#ifndef STK_WIDGET_H
#define STK_WIDGET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h> 

typedef XEvent STKEvent;

Display *display;

typedef struct widget_ptr
{
    void *this;
    struct widget_ptr *prev, *next;
} widget_list;


typedef struct
{
    uint w, h;
    int     x, y;
    Window  win;
    Display *dsp;
    void    (*func)(void *), *args;
    void    (*handler)(STKEvent *, void *);
    int     mask;
    GC gc, gc2;
    XFontStruct *font_info;
    char *fontname;
    const char *label;
    void *ext_struct; /* if need a place to store a reference to other struct, if it's not a basic widget, etc. */

} stk_widget;


stk_widget *stk_widget_search(void *);
int         stk_widget_insert(void *);
int         stk_widget_delete(void *);
void        stk_init();
void        stk_run();
void        stk_widget_set_size(stk_widget *);
void        stk_widget_set_pos(stk_widget *, uint, uint);
void        stk_widget_set_color(stk_widget *, int color);


#endif /* STK_WIDGET_H */
