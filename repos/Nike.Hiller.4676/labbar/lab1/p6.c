#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h> 
#include <string.h>


bool is_number(char *str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[0] == '-' && i == 0)
        {
            continue;
        }
        if (isdigit(str[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
        

    } return true;
}

int gcd(int a, int b)
{
  while (a != b)
  {
      if ( a > b)
      {
        a = a - b; 
        continue; 
      }
      if (a < b)
      {
          b = b -a;
          continue;
      }
     
  }
  return a;      
}



int main(int argc, char *argv[])
{
    char *tal1 = argv[1];
    int numTal1 = atoi(tal1);
    char *tal2 = argv[2];
    int numTal2 = atoi(tal2);
    
    if (is_number(tal1) && is_number(tal2) && numTal1 > 0 && numTal2 > 0)
    {
        int result = gcd(numTal1,numTal2);
        printf("gcd = %d\n", result);
    }
    else
    {
        puts("needs to be two postive numbers");
    }
    return 0;
    
}
