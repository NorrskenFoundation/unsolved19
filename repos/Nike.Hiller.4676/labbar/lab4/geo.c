#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


struct point
{
  int x;
  int y;
};

struct rectangle
{
    int x;
    int y;
};

typedef struct point point_t;
//typedef struct rectangle rectangle_t

void translate(point_t *p1, point_t *p2)
{
  p1->x += p2->x;
  p1->y += p2->y;
}

//point_t *p = { .x = 10, .y = -42};


void print_point(point_t *p)
{
    printf("point(x=%d, y=%d)\n", p->x, p->y);
}

/*void print_rec(rectangle_t *r)
{
    
    print_point()
}*/


point_t make_point(int a, int b)
{
    point_t p2;
    p2.x = a;
    p2.y = b;

    return p2;
}



int main(void)
{
    point_t p;
    p.x = 42;
    p.y = 7;

    int x = 1;
    int y = 2;

    point_t p3 = make_point(x,y);
    print_point(&p);
    print_point(&p3);

    
    return 0;
}