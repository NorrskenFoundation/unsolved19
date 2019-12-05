#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct item{ 
	char *name;
	char *desc;
	int price;
	char *shelf;
};

typedef struct item item_t;

void print_item(item_t *item){
	printf("Name: %s\n", item->name);
	printf("Desc: %s\n", item->desc);
	printf("Price: %d.%d\n", item->price/100, item->price % 100 );
}	

item_t make_item(char *name, char *desc, int price, char *shelf){
	item_t new_item;
	new_item.name = name;
  new_item.desc = desc;
	new_item.price = price;
	new_item.shelf = shelf;

	return new_item;
}


item_t input_item(void){
	char *name = ask_question_string("Varans namn: ");
	char *desc = ask_question_string("Beskrivning av varan: ");
	int price = ask_question_int("Varans pris: ");
	char *shelf = ask_question_shelf("Varans plats: ");
  item_t created_item = make_item(name, desc, price, shelf);

	return created_item;
}


char *magick(char *array1[], char *array2[], char *array3[], int length){
	char buf[255];
	buf[0] = '\0';
	char *firstWord = array1[random() % length];	
	char *secondWord = array2[random() % length];	
	char *thirdWord = array3[random() % length];	
	
	strncat(buf, firstWord,255);
	strncat(buf,"-", 254);
	strncat(buf, secondWord,255);
	strncat(buf," ", 254);
	strncat(buf, thirdWord,255);
	strncat(buf,"\0", 254);
	
	return strdup(buf);

}

void list_db(item_t *item, int no_items){
	for(int i = 0; i < no_items; ++i){
    printf("%d. %s\n", i +1, item[i].name);
 }
}


item_t edit_db(item_t *item){
  int varaIndex  = ask_question_int("Vilken vara ska ändras?");
    while (varaIndex > 16 || varaIndex <  1){
      varaIndex = ask_question_int("Du måste välja ett nr mellan 1 och 16,Vilken vara ska ändras?");
    }
    print_item(&(item[varaIndex -1]));
    item[varaIndex-1] = input_item();
    return *item;
}

/*void print_menu(){
  puts("[L]ägga till en vara \n [T]a bort en vara\n [R]edigera en vara\n Ån[g]ra senaste ändringen\n Lista [h]ela varukatalogen\n [A]vsluta\n");
}


char ask_question_menu(char *menu){
  print_menu();
  char *input = ask_question_string("Välj ett alternativ \n");
  while(!strpbrk("LlTtRrGgHhAa", input))
  {
    input = ask_question_string("Inte giltigt alternativ. välj ett annat\n");
  }
  char choice = toupper(input[0]);
  return choice; 
} 
*/

/*void add_item_to_db(char *db, int db_siz){  
  db[0] = input_item();
}
*/

int main(int argc, char *argv[])
{
	char *array1[] = { "Laser",        "Polka",    "Extra" };
	char *array2[] = { "förnicklad",   "smakande", "ordinär" };
	char *array3[] = { "skruvdragare", "kola",     "uppgift" };

	if (argc < 2)
	{
		printf("Usage: %s number\n", argv[0]);
	}
	else
	{
		item_t db[16]; // Array med plats för 16 varor
		int db_siz = 0;    // Antalet varor i arrayen just nu

		int items = atoi(argv[1]); // Antalet varor som skall skapas

		if (items > 0 && items <= 16)
		{
			for (int i = 0; i < items; ++i)
			{
				// Läs in en vara, lägg till den i arrayen, öka storleksräknaren
				item_t item = input_item();
				db[db_siz] = item;
				++db_siz;
			}
		}
		else
		{
			puts("Sorry, must have [1-16] items in database.");
			return 1; // Avslutar programmet!
		}

		for (int i = db_siz; i < 16; ++i)
		{
			char *name = magick(array1, array2, array3, 3); /// Lägg till storlek
			char *desc = magick(array1, array2, array3, 3); /// Lägg till storlek
			int price = random() % 200000;
			char shelf[] = { random() % ('Z'-'A') + 'A',
				random() % 10 + '0',
				random() % 10 + '0',
				'\0' };
			item_t item = make_item(name, desc, price, shelf);

			db[db_siz] = item;
			++db_siz;
		}

		// Skriv ut innehållet
    list_db(db, db_siz);
    puts("\n");
    edit_db(db);
    list_db(db, db_siz);
    puts("\n");
	}
	return 0;
}
