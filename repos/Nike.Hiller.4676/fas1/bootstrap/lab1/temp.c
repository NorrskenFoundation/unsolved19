#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

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
		


int main (int argc, char *argv[]){
	if (argc > 1 && is_number(argv[1])){
		printf("%s is number\n", argv[1]);
	}	else {
				if (argc > 0){
				printf("%s is not a number\n", argv[1]);
			}
			else
			 { 
				printf("Please provide a command line argument!");
			 }
	 }		
	 return 0;
}
