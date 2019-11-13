#include <stdlib.h>
#include <stdio.h> 


typedef int(*int_fold_func)(int, int);
#define INT_MAX 2147483647
#define INT_MIN -2147483648


int foldl_int_int(int numbers[], int numbers_siz, int_fold_func f, int start_value)
{
  int result = start_value;

  // Loopa över arrayen och för varje element e utför result = f(result, e)
  for (int i = 0; i < numbers_siz; ++i)
  {
    result = f(result, numbers[i]);
  }

  return result;
}

int add(int a, int b)
{
  return a + b;
}

int sum(int number[], int number_siz)
{
    return foldl_int_int(number, number_siz, add, 0); 
}

int max(int a, int b)
{
    if(a >b)
    {
        return a;
    }
    else
    {
        return b;
    }
    // a > b ? a : b; ternary. skillnad mot binary. om a är större än b returnerna a else b 
}

int min(int a, int b)
{
    return a < b ? a : b;
    
}

int biggest(int number[], int number_siz)
{
    return foldl_int_int(number, number_siz, max, INT_MIN);
}

int smallest(int number[], int number_siz)
{
    return foldl_int_int(number, number_siz, min, INT_MAX); // INT_MIN är ett macro 
}

int main(int argc, char *argv[])
{
    int number[3] = {1,5,4};

    int result = biggest(number, 3);
    printf("biggest and badest is %d\n", result);
    
    result = sum(number, 3);
    printf("sum is %d\n", result);
    
    result = smallest(number, 3);
    printf("smallest and cutest is %d\n", result);

    



    return 0;
}