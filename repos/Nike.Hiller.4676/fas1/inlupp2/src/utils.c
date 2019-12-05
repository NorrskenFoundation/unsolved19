#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "common.h"
// fråga enter ger för litet

typedef union {
    int int_value;
    float float_value;
    char *string_value;
} answer_t;

extern char *strdup(const char *);

typedef bool (*check_func)(char *);
typedef answer_t (*convert_func)(char *);

bool not_empty(char *str)
{
    return strlen(str) > 0;
}

bool is_number(char *str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (str[0] == '-' && i == 0)
        {
            continue;
        }
        else if (isdigit(str[i]))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    if (strlen(str) == 0)
    {
        return false;
    }

    return true;
}

bool is_shelf(char *shelf)
{
     if (strlen(shelf) <= 1)
        {
            return false;
        }

    if (isalpha(shelf[0]))
    {
        for (int i = 1; i < strlen(shelf); ++i)
        {
            if (!isdigit(shelf[i]))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

void clear_input_buffer()
{
    int c;
    do
    {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

int read_string(char *buf, int buf_size)
{
    char current;
    int size = 0;

    do
    {
        current = getchar();
        buf[size] = current;
    } while (current != '\n' && size++ < buf_size - 1);
    buf[size] = '\0';

    if (size > buf_size - 1)
    {
        clear_input_buffer();
    }
    return size;
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
    int buf_size = 255;
    char buf[buf_size];
    do
    {
        printf("%s\n", question);
        read_string(buf, buf_size);
    } while (!check(buf));
    return convert(buf);
}

int ask_question_int(char *question)
{
    answer_t answer = ask_question(question, is_number, (convert_func)atoi);
    return answer.int_value; // svaret som ett heltal
}

char *ask_question_string(char *question)
{
    return ask_question(question, not_empty, (convert_func)strdup).string_value;
}
char *ask_question_shelf(char *question)
{
    return ask_question(question, is_shelf, (convert_func)strdup).string_value;
}

