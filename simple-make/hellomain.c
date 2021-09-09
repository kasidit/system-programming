#include <stdio.h>
extern void fun1(void);
extern void fun2(void);

int main(){
  fun1();
  fun2();
  printf ("s");
}

