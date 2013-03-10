#ifndef STK_TEXT_H
#define STK_TEXT_H

#include <stk_widget.h>

/* STKText Events */
#define STK_TEXT_EXPOSE      0x10
#define STK_TEXT_PRESS       0x20
#define STK_TEXT_RELEASE     0x30
#define STK_TEXT_ENTER       0x40
#define STK_TEXT_LEAVE       0x50
#define STK_TEXT_KEYPRESS    0x60
#define STK_TEXT_KEYRELEASE  0x70
#define STK_TEXT_BUFFER_SIZE 4096



/* STKText Properties */
enum {
    STK_TEXT_INPUT = 0,
    STK_TEXT_OUTPUT = 1
 };



typedef struct
{
    char text[STK_TEXT_BUFFER_SIZE];
} stk_text;

stk_widget *stk_text_new(stk_widget *, int, int, uint, uint, char *, int);
void        stk_text_handle(STKEvent *, void *);
void        stk_text_redraw(int, stk_widget *, void *);
char       *stk_text_get_text(stk_widget *);

#endif /* STK_TEXT_H */
