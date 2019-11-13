#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int p = 0;
    char *antalRader = argv[1];
    int numRader = atoi(antalRader);

    char *antalKolumner = argv[2];
    int numKolumner = atoi(antalKolumner);

    for (int i = 1 ; i <= numRader ; ++i)
    {
        
        for (int n = 1; n <= numKolumner; ++n)
        {
          printf("*");  
          ++p; 
        }
        printf("\n");
    }
    printf("totalt: %d\n", p);
    return 0;
    
}
