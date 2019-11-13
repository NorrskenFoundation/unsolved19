#include <stdio.h>
#include <string.h>


int string_length(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        ++i;
    
    }  
 return i;   
}

char *print(char *str)
{
    int length = string_length(str);
    for (int i = 0; i < length; ++i)
    {
    putchar(str[i]);
    }

return 0;
}

char *println(char *str)
{
    int lengt_ln = string_length(str);
    for (int j = 0; j < lengt_ln; ++j)
    {
       putchar(str[j]);
    }
    putchar('\n');
return 0;   
}

int main(int argc, char *argv[])
{
  
  println(argv[1]);
  
  if (argc < 2)
  {
    print(argv[0]);
  }
  else
  {
    for (int i = 1; i < argc; ++i)
    {
      //int expected = strlen(argv[i]);
      //int actual   = string_length(argv[i]);
      print(argv[i]);    }
  }
  return 0;
}