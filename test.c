#include <stk_window.h>
#include <stk_button.h>
#include <stk_text.h>
#include <stk_progress_bar.h>
#include <stk_canvas.h>
#include <stk_menu.h>

typedef struct 
{
    void *d1;
    int c, x, y;
} ptr;


void draw(void *c)
{
    int i = 0;
    
    stk_widget *p = (stk_widget*)c;
    stk_canvas_draw_arc(p, 80, 70, 300, 100, 100, 360*64);
    stk_canvas_draw_line(p, 10, 10, 100, 100);
    /*stk_canvas_set_string_font_size(p, STK_FONT_SIZE_9x15);*/
    stk_canvas_draw_string(p, 50, 50, "50x50");

    for(i = 350; i > 200; i--)
        stk_canvas_draw_point(p, 100+i, i-150);        
}

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

void add(void *c)
{
    int val = 0;
    char buffer[10] = {0};
    stk_widget *p = (stk_widget*)c;

    val = stk_progress_bar_get_value(p);
    
    if(val < 100)
    {
        val += 1;
        sprintf(buffer, "%d%%", val);
        stk_progress_bar_set_value(p, val);
        stk_progress_bar_set_label(p, buffer);
    }
}

void listen(void *c)
{
    stk_widget *p = (stk_widget*)c;
    char coords[10] = {0};
    sprintf(coords, "%dx%d", p->ev->xbutton.x, p->ev->xbutton.y);
    printf("%dx%d\n", p->ev->xbutton.x, p->ev->xbutton.y);
    stk_canvas_draw_string(p, p->ev->xbutton.x, p->ev->xbutton.y, coords);
}

void sub(void *c)
{
    int val;
    char buffer[10];
    stk_widget *p = (stk_widget*)c;

    val = stk_progress_bar_get_value(p);
    
    if(val > 0)
    {
        val -= 1;
        sprintf(buffer, "%d%%", val);
        stk_progress_bar_set_value(p, val);
        stk_progress_bar_set_label(p, buffer);
    }
}


int main()
{
    stk_widget *bt, *bt1, *bt2, *bt3,
               *bt4, *bt5, *bt6, *cv,
               *bt7, *txt, *pb, *win,
               *mn;

    ptr wc, wc1, wc2, wc3;

    stk_init();
    
    win = stk_window_new(500, 500, 800, 600, "STK Demo");
    mn  = stk_menu_new(win, 600, 70, 60, 20, NULL);
    bt  = stk_button_new(win, 100, 100, 60, 20, "Hello", &hello, "to STKButton");
    bt1 = stk_button_new(win, 200, 100, 60, 20, "MoveWin", &move,  (void*)&wc2);
    bt2 = stk_button_new(win, 300, 100, 60, 20, "Color1", &color, (void*)&wc1);
    bt3 = stk_button_new(win, 400, 100, 60, 20, "Color2", &color, (void*)&wc);
    bt4 = stk_button_new(win, 400, 150, 60, 20, "MoveBt1", &move, (void*)&wc3);
    txt = stk_text_new(win, 100, 150, 200, 20, "TxtArea", STK_TEXT_INPUT);
    pb  = stk_progress_bar_new(win, 100, 200, 200, 20, "0%");
    bt5 = stk_button_new(win, 300, 200, 20, 20, "+", &add, (void*)pb);
    bt6 = stk_button_new(win, 80, 200, 20, 20, "-", &sub, (void*)pb);
    cv  = stk_canvas_new(win, 80, 230, 700, 350);
    bt7 = stk_button_new(win, 400, 200, 60, 20, "CanvasBt", &draw, (void*)cv);
    
    /*stk_widget_event_listen_add(cv, STK_WIDGET_MOVE, listen, (void*)cv);*/
    stk_widget_event_listen_add(cv, STK_WIDGET_PRESS, listen, (void*)cv);

    stk_text_set_text(txt, "Oba!!!");
    stk_canvas_draw_arc(cv, 50, 70, 150, 150, 10, 360*64);
    
    wc.d1  = win;
    wc.c   = 0xd3d3d3;

    wc1.d1 = win;
    wc1.c  = 0xdda0dd;

    wc2.d1 = win;
    wc2.x  = 600;
    wc2.y  = 200;

    wc3.d1 = bt4;
    wc3.x  = 10;
    wc3.y  = 10;

    stk_window_show(win);

    stk_run();
    
    return 0;
}
