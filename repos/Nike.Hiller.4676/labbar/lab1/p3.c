#include <stdio.h>

int main(void)
{
    //int i = 1; bäst att ha här eller i loopen?
    int p = 0;

    for (int i = 1 ; i <= 10 ; ++i)
    {
        for (int n = 1; n <= i; ++n)
        {
          printf("*");  
          ++p; 
        }
        printf("\n");
    }
    printf("totalt: %d\n", p);
    return 0;
    
}
