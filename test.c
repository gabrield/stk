#include <stk_widget.h>

int main()
{


  stk_init();
  stk_widget *w = stk_window_new(500, 500, 640, 480, NULL, NULL);
  stk_window_show(w);


  stk_run();
  
  return 0;
}