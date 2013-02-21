#ifndef STK_BUTTON_H
#define STK_BUTTON_H

#include <stk_widget.h>

/* STKButton Events */
#define STK_BUTTON_EXPOSE   0x10
#define STK_BUTTON_PRESS    0x20
#define STK_BUTTON_RELEASE  0x30
#define STK_BUTTON_ENTER    0x40
#define STK_BUTTON_LEAVE    0x50

stk_widget *stk_button_new(stk_widget *, int, int, uint, uint, const char *,
                                                            void *, void *);
void        stk_canvas_line(stk_widget *, int, int);
void        stk_canvas_point(stk_widget *, int, int);
void        stk_canvas_circle(stk_widget *, int, int, int);
void        stk_canvas_rectangle(stk_widget *, int, int);
void        stk_button_handle(STKEvent *, void *);

#endif /* STK_BUTTON_H */
