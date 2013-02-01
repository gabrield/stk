#include <common.h>

widget_list *list;


int init()
{
    list = NULL;
}


int insert(void *widget)
{
	widget_list *new_widget = (widget_list *)malloc(sizeof(widget_list));
    new_widget->this = widget;
    new_widget->prev = NULL;
    new_widget->next = list;

    if(list != NULL)
        list->prev = new_widget;

    list = new_widget;
}


int delete(void *widget)
{

}


int search(void *widget)
{
    widget_list *node = list;
    if(node ==  NULL)
        printf("Empty list\n");
    else
        while(node)
        {
                if (node->this == widget)
                {
                    printf("Widget %p found!\n", widget);
                    return FOUND;
                }
                else
                    node = node->next;
        }
        printf("Widget %p not found :(\n", widget);
        return NOT_FOUND;
}

void print()
{
    widget_list *node = list;
    if(node ==  NULL)
        printf("Empty list\n");
    else
        //while(1)
        //{
        //    node = list;
            while(node)
            {
                printf("%p\n", node->this);
                node = node->next;
            }
        //}
}

void handle()
{}

