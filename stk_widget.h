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



/* STK_WIDGET Events */
#define STK_WIDGET_EXPOSE   0x10
#define STK_WIDGET_PRESS    0x20
#define STK_WIDGET_RELEASE  0x30
#define STK_WIDGET_ENTER    0x40
#define STK_WIDGET_LEAVE    0x50
#define STK_WIDGET_MOVE     0x60



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
    STKEvent *ev;
    char *fontname;
    char *label;
    void *ext_struct; /* if need a place to store a reference to other struct, if it's not a basic widget, etc. */
    void (*movefunc)(void *),  *margs;
    void (*clickfunc)(void *), *cargs;

} stk_widget;

/* Font Sizes */
#define STK_FONT_SIZE_6x9   "6x9"
#define STK_FONT_SIZE_7x13  "7x13"
#define STK_FONT_SIZE_9x15  "9x15"

stk_widget *stk_widget_search(void *);
int         stk_widget_insert(void *);
int         stk_widget_delete(void *);
void        stk_init();
void        stk_run();
void        stk_widget_set_size(stk_widget *);
void        stk_widget_set_pos(stk_widget *, uint, uint);
void        stk_widget_set_color(stk_widget *, int color);
void        stk_widget_set_font_size(stk_widget *, char *);
stk_widget *stk_widget_root();
void        stk_widget_event_listen(stk_widget *, int, void *,void *);


#endif /* STK_WIDGET_H */
