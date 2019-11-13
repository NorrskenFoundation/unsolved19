#include "utils.h"
#include <stdlib.h>


int main(int argc, char *argv[])
{
    int random_tal = random();
    int buf_size = 10;
    char buf[buf_size];  //plats för 10 tecken
    char *name;
    name = ask_question_string("Skriv in ditt namn", buf, buf_size);
    printf("%s\n", name);
    
}

/* notes:

1. name = ask_ques_string ("namn")
2.
*/