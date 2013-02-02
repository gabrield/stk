#ifndef STK_BUTTON_H
#define STK_BUTTON_H

#include <common.h>

stk_widget *stk_button_new(stk_widget *, int, int, uint, uint, void *, void *);
void        stk_button_handle(STKEvent *, void *);

#endif /* STK_BUTTON_H */