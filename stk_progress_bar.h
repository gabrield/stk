#ifndef STK_PROGRESS_BAR_H
#define STK_PROGRESS_BAR_H

#include <stk_widget.h>

/* STKButton Events */
#define STK_PROGRESS_BAR_EXPOSE   0x10
#define STK_PROGRESS_BAR_PRESS    0x20
#define STK_PROGRESS_BAR_RELEASE  0x30
#define STK_PROGRESS_BAR_ENTER    0x40
#define STK_PROGRESS_BAR_LEAVE    0x50


typedef struct
{
    Colormap cmap;
    XColor color, colorrgb;
    uint pct;
    char *label;
} stk_progress_bar;


stk_widget *stk_progress_bar_new(stk_widget *, int, int, uint, uint, const char *);
void        stk_progress_bar_handle(STKEvent *, void *);
void        stk_progress_bar_set(stk_widget *, uint);
void        stk_progress_bar_set_value(stk_widget *, uint);
void        stk_progress_bar_set_label(stk_widget *, char *);
uint        stk_progress_bar_get_value(stk_widget *);

#endif /* STK_PROGRESS_BAR_H */
