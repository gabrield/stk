#include <stk_widget.h>

void hello()
{
  printf("Hello\n");
}


int main()
{
  stk_init();
  stk_widget *w = stk_window_new(500, 500, 640, 480, &hello, NULL);
  stk_window_show(w);

  stk_run();
  
  return 0;
}