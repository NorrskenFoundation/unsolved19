#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool is_prime(int n)
{
    for (int x = 2; x<= n; ++x)
    {
        for (int y = 2; y <= n; ++y)
        {
            int tmp =  x * y;
            if (tmp == n)
            {
                return false;
            }
        }
    }
    return true;
}



int main(int argc, char *argv[])
{
    //int p = 0;
    char *tal = argv[1];
    int numTal = atoi(tal);


    if (is_prime(numTal))
    {
        puts("primetal");
    }
    else
    {
        puts("inte primetal");
    }


    /*for (int i = 1 ; i <= numRader ; ++i)
    {
        
        for (int n = 1; n <= numKolumner; ++n)
        {
          printf("*");  
          ++p; 
        }
        printf("\n");
    }
    printf("totalt: %d\n", p);*/
    return 0;
    
}
