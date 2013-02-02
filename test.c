#include <stk_window.h>
#include <stk_button.h>

void hello(void *string)
{
  char *str = (char*)string;

  printf("Hello %s\n", str);
}

void hello_bt(void *string)
{
  char *str = (char*)string;

  printf("Hello %s\n", str);
}


int main()
{
  stk_init();
  
  stk_widget *win = NULL;
  stk_widget *bt = NULL;
  
  win = stk_window_new(500, 500, 640, 480, &hello, "to STK");
  bt  = stk_button_new(win, 100, 100, 40, 20, &hello_bt, "to STKButton");

  stk_window_show(win);

  stk_run();
  
  return 0;
}