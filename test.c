#include <stk_window.h>
#include <stk_button.h>
#include <stk_text.h>
#include <stk_progress_bar.h>



typedef struct 
{
    void *d1;
    int c, x, y;
} ptr;

void hello(void *string)
{
    char *str = (char*)string;
    printf("Hello %s\n", str);
}


void color(void *c)
{
    ptr *w = (ptr*)c;
    printf("Win = %p, Color %x\n", w->d1, w->c);

    stk_window_set_color((stk_widget*)w->d1, w->c);
}


void move(void *c)
{
    ptr *w = (ptr*)c;
    printf("Win = %p, pos %dx%d\n", w->d1, w->x, w->y);
    stk_widget_set_pos((stk_widget*)w->d1, w->x, w->y);
}

int main()
{
    stk_widget *win = NULL;
    stk_widget *bt, *bt1, *bt2, *bt3,
                     *bt4, *txt, *pb;

    ptr wc, wc1, wc2, wc3;

    stk_init();
    
    win = stk_window_new(500, 500, 640, 480, "STK Demo", &hello, "to STK");
    bt  = stk_button_new(win, 100, 100, 60, 20, "Hello", &hello, "to STKButton");
    bt1 = stk_button_new(win, 200, 100, 60, 20, "MoveWin", &move,  (void*)&wc2);
    bt2 = stk_button_new(win, 300, 100, 60, 20, "Color1", &color, (void*)&wc1);
    bt3 = stk_button_new(win, 400, 100, 60, 20, "Color2", &color, (void*)&wc);
    bt4 = stk_button_new(win, 400, 300, 60, 20, "MoveBt1", &move, (void*)&wc3);
    txt = stk_text_new(win, 100, 300, 200, 20, "TxtArea", STK_TEXT_LABEL);
    pb  = stk_progress_bar_new(win, 400, 400, 200, 20, "ProgressBar 10%");

    wc.d1  = win;
    wc.c   = 0xd3d3d3;

    wc1.d1 = win;
    wc1.c  = 0xdda0dd;

    wc2.d1 = win;
    wc2.x  = 600;
    wc2.y  = 200;

    wc3.d1 = bt4;
    wc3.x  = 200;
    wc3.y  = 260;

    stk_window_show(win);
    stk_run();
    
    return 0;
}
