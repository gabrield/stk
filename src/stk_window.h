#ifndef STK_WINDOW_H
#define STK_WINDOW_H

#include <stk_widget.h>

stk_widget *stk_window_new(int, int, uint, uint, const char *);
void        stk_window_show(stk_widget *);
void        stk_window_set_title(stk_widget *, const char *);
void        stk_window_handle(STKEvent *, void *);
void        stk_window_set_size(stk_widget *);
void        stk_window_set_pos(stk_widget *, uint, uint);
void        stk_window_set_color(stk_widget *, int color);

#endif /* STK_WINDOW_H */
