#include <stk_widget.h>
#include <stk_window.h>

void hello(void *string)
{
  char *str = (char*)string;

  printf("Hello %s\n", str);
}


int main()
{
  stk_init();
  stk_widget *w = NULL;
  w = stk_window_new(500, 500, 640, 480, &hello, "to STK");
  stk_window_show(w);

  stk_run();
  
  return 0;
}