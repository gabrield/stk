#include <stk_window.h>
#include <stk_button.h>

void hello(void *string)
{
  char *str = (char*)string;
  printf("Hello %s\n", str);
}

int main()
{
  stk_widget *win = NULL;
  stk_widget *bt = NULL;
  stk_widget *bt1 = NULL;
  stk_widget *bt2 = NULL;
  stk_widget *bt3 = NULL;

  stk_init();
  
  win = stk_window_new(500, 500, 640, 480, "STK Demo", &hello, "to STK");
  bt  = stk_button_new(win, 100, 100, 60, 20, "Button", &hello, "to STKButton");
  bt1  = stk_button_new(win, 200, 100, 60, 20, "Button1", &hello, "to STKButton1");
  bt2  = stk_button_new(win, 300, 100, 60, 20, "Button2", &hello, "to STKButton2");
  bt3  = stk_button_new(win, 400, 100, 60, 20, "Button3", &hello, "to STKButton3");


  stk_window_show(win);
  stk_run();
  
  return 0;
}
