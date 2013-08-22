#ifndef STK_CANVAS_H
#define STK_CANVAS_H

#include <stk_widget.h>

/* STKCanvas Events */
#define STK_CANVAS_EXPOSE   0x10
#define STK_CANVAS_PRESS    0x20
#define STK_CANVAS_RELEASE  0x30
#define STK_CANVAS_ENTER    0x40
#define STK_CANVAS_LEAVE    0x50
#define STK_CANVAS_MOVE     0x60


typedef struct
{
    Pixmap pmap;
} stk_plotter;



stk_widget *stk_plotter_new(stk_widget *, int, int, uint, uint);
void        stk_plotter_draw_line(stk_widget *, uint, uint, uint, uint);
void        stk_plotter_draw_point(stk_widget *, uint, uint);
void        stk_plotter_draw_arc(stk_widget *, uint, uint, uint, uint, uint, uint);
void        stk_plotter_draw_rectangle(stk_widget *, int, int);
void        stk_plotter_draw_string(stk_widget *pl, uint x, uint y, char *str);
void        stk_plotter_set_string_font_size(stk_widget *, char *);
void        stk_plotter_set_string_font(stk_widget *, char *);
void        stk_plotter_handle(STKEvent *, void *);


/* TODO */
void stk_plotter_area_rotate(stk_widget *pl, uint x0, uint y0, uint x1, uint y1, uint angle);
void stk_plotter_area_move(stk_widget *pl, uint x0, uint y0, uint x1, uint y1, uint x, uint y);
void stk_plotter_line_color(stk_widget *pl, int color);


#endif /* STK_CANVAS_H */
