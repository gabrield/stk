#ifndef STK_CANVAS_H
#define STK_CANVAS_H

#include <stk_widget.h>

/* STKCanvas Events */
#define STK_CANVAS_EXPOSE   0x10
#define STK_CANVAS_PRESS    0x20
#define STK_CANVAS_RELEASE  0x30
#define STK_CANVAS_ENTER    0x40
#define STK_CANVAS_LEAVE    0x50


typedef struct
{
    Pixmap pmap;
} stk_canvas;



stk_widget *stk_canvas_new(stk_widget *, int, int, uint, uint);
void        stk_canvas_draw_line(stk_widget *, uint, uint, uint, uint);
void        stk_canvas_draw_point(stk_widget *, uint, uint);
void        stk_canvas_draw_arc(stk_widget *, uint, uint, uint, uint, uint, uint);
void        stk_canvas_draw_rectangle(stk_widget *, int, int);
void        stk_canvas_handle(STKEvent *, void *);

#endif /* STK_CANVAS_H */
