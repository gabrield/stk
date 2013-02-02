#ifndef STK_WINDOW_H
#define STK_WINDOW_H

#include <common.h>

stk_widget *stk_window_new(int, int, uint, uint, void *, void *);
void        stk_window_show(stk_widget *);
//void        stk_window_add(stk_widget *, stk_widget *);
void        stk_window_handle(STKEvent *, void *);

#endif /* STK_WINDOW_H */
