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
} stk_progress_bar;

stk_widget *stk_progress_bar_new(stk_widget *, int, int, uint, uint, const char *);
void        stk_progress_bar_handle(STKEvent *, void *);

#endif /* STK_PROGRESS_BAR_H */
