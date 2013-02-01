#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <X11/Xlib.h>

#define FOUND 42
#define NOT_FOUND 404


typedef struct widget_ptr
{
	void *this;
	struct widget_ptr *prev, *next;
} widget_list;

int init();
int insert(void *);
int delete(void *);
int search(void *);

#endif /* COMMON_H */