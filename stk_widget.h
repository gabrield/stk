#ifndef STK_WIDGET_H
#define STK_WIDGET_H

#include <common.h>

typedef unsigned int uint;

typedef struct
{
    unsigned int w, h;
    int x, y;
    Window win;
    Display *dsp;
    void *func, *args;
    void (*handler)();
    int mask;
} stk_widget;

stk_widget *stk_window_new(int, int, uint, uint, void *, void *);
void stk_window_show(stk_widget *);

#endif /* STK_WIDGET_H */