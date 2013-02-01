#ifndef WINDOW_H
#define WINDOW_H

#include <common.h>

typedef unsigned int uint;

typedef struct
{
    unsigned int w, h;
    int x, y;
    Window win;
    Display *dsp;
    void *func, *args;
} stk_window;

stk_window *stk_window_new(int, int, uint, uint, void *, void *);
void stk_window_show(stk_window *);

#endif /* WINDOW_H */