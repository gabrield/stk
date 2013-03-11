#ifndef STK_MENU_H
#define STK_MENU_H

#include <stk_widget.h>

stk_widget *stk_menu_new(stk_widget *, int, int, uint, uint, char*);
void        stk_menu_show(stk_widget *);
void        stk_menu_set_title(stk_widget *, const char *);
void        stk_menu_handle(STKEvent *, void *);
void        stk_menu_set_size(stk_widget *);
void        stk_menu_set_pos(stk_widget *, uint, uint);
void        stk_menu_set_color(stk_widget *, int color);

#endif /* STK_MENU_H */
