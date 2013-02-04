#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
#include <stk_widget.h>

typedef XEvent STKEvent;

Display *display;

typedef struct widget_ptr
{
	void *this;
	struct widget_ptr *prev, *next;
} widget_list;


stk_widget *stk_widget_search(void *);
int         stk_widget_insert(void *);
int         stk_widget_delete(void *);
void        stk_init();
void        stk_run();


#endif /* COMMON_H */
