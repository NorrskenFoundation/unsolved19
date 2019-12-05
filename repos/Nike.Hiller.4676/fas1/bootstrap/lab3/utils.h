#ifndef __UTILS_H__
#define __UTILS_H__
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

extern char *strdup(const char *);

typedef union {
	int   i;
	float f;
	char *s;
} answer_t;

typedef bool(*check_func)(char*);
typedef answer_t(*convert_func)(char*);


bool not_empty(char *str)
int clear_input_buffer(void);
int read_string (char *buf, int buf_size);
bool is_number(char *str);
int ask_question_int(char *question);
char *ask_question_string(char *question);
answer_t ask_question(char *question, check_func check, convert_func convert);
bool control_shelf(char *shelf);
char *ask_question_shelf(char *question);
#endif
