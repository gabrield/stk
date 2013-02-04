#include <common.h>

widget_list *list;


void stk_init()
{
    list = NULL;
    display =  XOpenDisplay(0);
}


int stk_widget_insert(void *widget)
{
    widget_list *new_widget = (widget_list *)malloc(sizeof(widget_list));
    new_widget->this = widget;
    new_widget->prev = NULL;
    new_widget->next = list;

    if(list != NULL)
        list->prev = new_widget;

    list = new_widget;

    return 0;
}


int stk_widget_delete(void *widget)
{
    return 0;
}


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
