#include <stk_widget.h>

#include <common.h>

widget_list *list;

/* stk_init()
Initialize the Display connection to X and the widget list
@return: void
@comments: Must be called before any STK functions
*/
void stk_init()
{
    list = NULL;
    display =  XOpenDisplay(0);
}


/* stk_widget_insert():
Alloc and insert a widget in the widget list.
@return: 0 if success or -1 if unsuccessful.
@comments: Every widget must call it to be
           registered and have its events
           handled
*/
int stk_widget_insert(void *widget)
{
    widget_list *new_widget = (widget_list *)malloc(sizeof(widget_list));
    if(new_widget)
    {
        new_widget->this = widget;
        new_widget->prev = NULL;
        new_widget->next = list;

        if(list != NULL)
            list->prev = new_widget;

        list = new_widget;

        return 0;
    }
    return -1;
}


int stk_widget_delete(void *widget)
{
    return 0;
}


/* stk_widget_search():
Search for a widget in the widget list.
@return:and return a pointer to stk_widget or NULL
@comments: return a pointer to stk_widget if the widget exists.
*/
stk_widget *stk_widget_search(void *widget)
{
    widget_list *node = list;
    stk_widget *wnode = NULL;


    if(node ==  NULL)
        printf("Empty widget list\n");
    else
    {
        while(node)
        {
            wnode = (stk_widget*)node->this;
            if(wnode->win == (Window)widget)
            {
                /*printf("Widget %p found!\n", widget);*/
                return wnode;
            }
            else
                node = node->next;
        }
    }   
    printf("Widget %p not found :(\n", widget);
    return NULL;
}


/* stk_run():
Search for a widget in the widget list.
@return: void
@comments: Must be called after all STK functions.
           It's the event loop that handles the all
           the event callings of the widgets.
*/
void stk_run()
{
    STKEvent  event;
    widget_list *node = list;
    stk_widget *wnode = NULL;

    if(node ==  NULL)
        printf("Empty list\n");
    else
    {       
        while(1)
        {
            XNextEvent(display, &event);
            wnode = stk_widget_search((void*)event.xany.window);
            if(wnode)
            {
                /*printf("Event %d happened to %p == %p\n", event.type, wnode->win, event.xany.window);*/
                wnode->handler(&event, wnode);
            }
        }
    }
}



void stk_widget_set_size(stk_widget *);


void stk_widget_set_pos(stk_widget *win, uint x, uint y)
{
    XMoveWindow(win->dsp, win->win, x, y);   
}


void stk_widget_set_color(stk_widget *win, int color)
{
    XSetWindowBackground(win->dsp, win->win, color);
    XClearWindow(win->dsp, win->win);
    XFlush(win->dsp);
}