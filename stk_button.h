#ifndef STK_BUTTON_H
#define STK_BUTTON_H

#include <common.h>

/* STKButton Events */
#define STK_BUTTON_EXPOSE   10
#define STK_BUTTON_PRESS    20
#define STK_BUTTON_RELEASE  30
#define STK_BUTTON_ENTER    40
#define STK_BUTTON_LEAVE    50

stk_widget *stk_button_new(stk_widget *, int, int, uint, uint, const char *,
                                                            void *, void *);
void        stk_button_handle(STKEvent *, void *);

#endif /* STK_BUTTON_H */
