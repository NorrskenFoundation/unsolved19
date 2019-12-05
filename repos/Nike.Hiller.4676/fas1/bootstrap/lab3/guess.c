#include <stdlib.h>
#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int main(void){
	srandom(time(NULL));	
	int random_number = (random() % 101);
	//int size_of_username_array = 255;
	char *question = "Skriv in ditt namn \n";
	char *username;

	username = ask_question_string(question);
	printf("Du %s, jag tänker på ett tal ...  kan du gissa vilket? ", username);

	int tries_counter = 0;
	while (tries_counter < 16){
		++tries_counter;
		int user_guess = ask_question_int ("");
		if(user_guess == random_number){
			printf("Bingo! Det tog %d gissningar att komma fram till %d\n", tries_counter, random_number);

			return 0;
		}
		else if(user_guess < random_number){
			printf("%d är för litet! Försök igen:\n", user_guess);
		}
		else{
			printf("%d är för stort! Försök igen:\n", user_guess);
		}

	}
	printf("Nu har du slut på gissningar! Jag tänkte på %d\n", random_number);



	return 0;
}


