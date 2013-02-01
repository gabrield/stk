#include <stk_window.h>

int main()
{
  stk_window *w = stk_window_new(500, 500, 640, 480, NULL, NULL);
  stk_window_show(w);
  int a, b, c;


  a = 10;
  b = 20;
  c = 30;


  init();
  insert(&a);
  insert(&b);
  insert(w);

   print();
   search(&a);
   search(&c);
   search(&b);
   search(w);

  sleep(10);

  return 0;
}