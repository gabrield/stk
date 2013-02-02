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
} stk_widget;


#endif /* STK_WIDGET_H */
