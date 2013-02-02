#ifndef STK_WIDGET_H
#define STK_WIDGET_H

#include <common.h>

typedef unsigned int uint;

typedef struct
{
    unsigned int w, h;
    int     x, y;
    Window  win;
    Display *dsp;
    void    (*func)(void *), *args;
    void    (*handler)(XEvent *, void *);
    int     mask;
    GC gc, gc2;
    XFontStruct *font_info;
    char* fontname;
    const char *label;
} stk_widget;


#endif /* STK_WIDGET_H */
