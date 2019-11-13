#include <stdlib.h>
#include <math.h>
#include <stdbool.h> 
#include <string.h>
#include <stdio.h>


struct point_t
{
  int x;
  int y;
};

int main(int argc, char *argv[])
{

struct point_t p1 = { .x = 10 };
struct point_t p2 = { .y = -42 };
struct point_t p3 = { };

printf("point(x=%d,y=%d)\n", p1.x, p1.y);
printf("point(x=%d,y=%d)\n", p2.x, p2.y);
printf("point(x=%d,y=%d)\n", p3.x, p3.y);
return 0;

}