#ifndef STK_CANVAS_H
#define STK_CANVAS_H

#include <stk_widget.h>

/* STKCanvas Events */
#define STK_CANVAS_EXPOSE   0x10
#define STK_CANVAS_PRESS    0x20
#define STK_CANVAS_RELEASE  0x30
#define STK_CANVAS_ENTER    0x40
#define STK_CANVAS_LEAVE    0x50

stk_widget *stk_canvas_new(stk_widget *, int, int, uint, uint);
void        stk_canvas_line(stk_widget *, int, int);
void        stk_canvas_point(stk_widget *, int, int);
void        stk_canvas_circle(stk_widget *, int, int, int);
void        stk_canvas_rectangle(stk_widget *, int, int);
void        stk_canvas_handle(STKEvent *, void *);

#endif /* STK_CANVAS_H */
