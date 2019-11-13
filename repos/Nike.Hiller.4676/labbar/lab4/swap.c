#include <stdio.h>

void swap(int *a, int *b)
{
  
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void print(char *str)
{
  while (*str != '\0')
  {
    putchar(*str);
    ++str;
  }
  
  putchar('\n');
}

int main(int argc, char *argv[])
{
  int x = 7;
  int y = 42;
  swap(&x, &y);
  printf("%d, %d\n", x, y);
  print(argv[1]);
  return 0;
}