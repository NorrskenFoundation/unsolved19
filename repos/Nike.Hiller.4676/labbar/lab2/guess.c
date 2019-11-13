#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h> 
#include <string.h>
#include <time.h>


int main(int argc, char *argv[])
{
    int r = random()%100;
    char *name;
    
    name = ask_question_string("Skriv in ditt namn");
    printf("Du %s, jag tänker på ett tal mellan 1-100 kan du gissa vilket?", name);

    int guess;
    char *question = "";
    guess = ask_question_int(question);
    
    //printf("%d\n", r);

    for (int i = 1; i < 16; ++i)
    {
        if (guess < r)
        {
            printf("För litet!");
            guess = ask_question_int(question);
        }
        else if (guess > r)
        {
           printf("För stort!");
           guess = ask_question_int(question);
        }
        else if (guess == r)
        {
            printf("Bingo!\nDet tog %s %d gissninar att komma fram till svaret\n",name, i);
            i = 16;
        }
    }  
    printf("Nu har du slut på gissningar, jag tänkte på %d\n", r);
  
}  
  
