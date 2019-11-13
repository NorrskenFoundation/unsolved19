#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void print_number(int num)
{
    if (num % 3 == 0 && num != 0)
    {
        printf("Fizz");
    }
    if (num % 5 == 0 && num != 0)
    {
        printf("Buzz");
    }
    if (num % 3 != 0 && num % 5 != 0)
    {
        printf("%d", num);
    }
}

int main(int argc, char *argv[])
{
    char *input_tal = argv[1];
    int num_tal = atoi(argv[1]);

    for (int i = 1; i <= num_tal; ++i)
    {
        print_number(i);
        if (i < num_tal)
        {
            printf(",");
        }   
    }
    return 0;
    
}
