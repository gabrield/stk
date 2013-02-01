#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <stk_widget.h>

#define FOUND 42
#define NOT_FOUND 404


typedef struct widget_ptr
{
	void *this;
	struct widget_ptr *prev, *next;
} widget_list;

int stk_init();
int stk_widget_insert(void *);
int stk_widget_delete(void *);
int stk_widget_search(void *);
void stk_run();

#endif /* COMMON_H */