#include "utils.h" 
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
extern char *strdup(const char *);

/*typedef union {
	int   i;
	float f;
	char *s;
} answer_t;
*/
typedef bool(*check_func)(char*);
typedef answer_t(*convert_func)(char*);

bool not_empty(char *str){

	return strlen(str) > 0;

}


bool is_number(char *str){
	int n = 0;
	int length = strlen(str); 

	if (str[n] == '-'){
			++n;
	}
		 while ( n < length){
			if (isdigit(str[n]) == false){
				return false;
		 } else {
				++n;	
		}
	}
	return true;

}


int clear_input_buffer(void){
	int c;
	do
		{
				c = getchar();
			}
	while ( c != '\n' && c != EOF);
	putchar('\n');
	return 0;
}


answer_t ask_question(char *question, check_func check, convert_func convert){
	char buf[255];
	int buf_siz = 255;
	
	do
	{
	printf("%s", question);
	read_string(buf, buf_siz);
	check(buf);
	}
	while(check(buf) == false);
		
	return convert(buf);
}	
char *ask_question_string(char *question){
	
	return ask_question(question, not_empty,(convert_func) strdup).s;

}

int ask_question_int(char *question){
	answer_t answer = ask_question(question, is_number, (convert_func) atoi);
	return answer.i;
}




bool control_shelf(char *shelf){
	
	if (isdigit(shelf[0])){
		return false;	
	}
	for (int i = 1; i < strlen(shelf); ++i){
		if (!isdigit(shelf[i])){
			
			return false;
		}	
	}
	return true;
}	



char *ask_question_shelf(char *question){
	return ask_question(question, control_shelf, (convert_func) strdup).s;
}


int read_string(char *buf, int buf_siz){
	int a;
	int counter = 0;
	while (counter < buf_siz)
		{
			a = getchar();
			if (a != EOF && a != '\n'){
			buf[counter] = a;
			++counter;
			}
			else{
			break;
			}		
	}
	buf[counter] = '\0';
	if(counter >= buf_siz){
		clear_input_buffer();
}
	return counter;
			
}	

