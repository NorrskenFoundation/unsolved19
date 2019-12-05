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
	printf("name: %s\n", item->name);
	printf("desc: %s\n", item->desc);
	printf("price: %d.%d\n", item->price/100, item->price % 100 );
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
	char *name = ask_question_string("varans namn: ");
	char *desc = ask_question_string("beskrivning av varan: ");
	int price = ask_question_int("varans pris: ");
	char *shelf = ask_question_shelf("varans plats: ");
  item_t created_item = make_item(name, desc, price, shelf);

	return created_item;
}


char *magick(char *array1[], char *array2[], char *array3[], int length){
	char buf[255];
	buf[0] = '\0';
	char *firstword = array1[random() % length];	
	char *secondword = array2[random() % length];	
	char *thirdword = array3[random() % length];	
	
	strncat(buf, firstword,255);
	strncat(buf,"-", 254);
	strncat(buf, secondword,255);
	strncat(buf," ", 254);
	strncat(buf, thirdword,255);
	strncat(buf,"\0", 254);
	
	return strdup(buf);

}

void list_db(item_t *item, int no_items){
	for(int i = 0; i < no_items; ++i){
    printf("%d. %s\n", i +1, item[i].name);
 }
}


item_t edit_db(item_t *item){
  int varaindex  = ask_question_int("vilken vara ska ändras?");
    while (varaindex > 16 || varaindex <  1){
      varaindex = ask_question_int("du måste välja ett nr mellan 1 och 16,vilken vara ska ändras?");
    }
    print_item(&(item[varaindex -1]));
    item[varaindex-1] = input_item();
    return *item;
}

void print_menu(){
  puts("[l]ägga till en vara\n[t]a bort en vara\n[r]edigera en vara\nån[g]ra senaste ändringen\nlista [h]ela varukatalogen\n[a]vsluta\n");
}


char ask_question_menu(void){
  print_menu();
  char *input = ask_question_string("välj ett alternativ \n");
  while(!strpbrk("llttrrgghhaa", input))
  {
    input = ask_question_string("inte giltigt alternativ. välj ett annat\n");
  }
  char choice = toupper(input[0]);
  return choice; 
} 

void add_item_to_db(item_t *db, int *db_siz){  
  puts("lägg till ny vara:\n");
  db[*db_siz] = input_item();
 *db_siz = *db_siz + 1;
}

void remove_item_from_db(item_t *db, int *db_siz){
  int varadelete = 457;
  while(varadelete > *db_siz || varadelete < 1){
  varadelete = ask_question_int("vilken vara vill du ta bort?\n");
  }
  for(int i = varadelete -1; i != *db_siz; ++i){
       db[i]= db[i + 1];
    }  
  *db_siz = *db_siz -1;
} 

void event_loop(item_t *db, int db_siz){
  bool avslut = false;
  while( !avslut){
    char answer = ask_question_menu();

    switch (answer){

      case 'L' :
        add_item_to_db(db, &db_siz);
        break;
      case 'T' :
        remove_item_from_db(db, &db_siz);
        break;
      case 'R' :
        edit_db(db);
        break;
      case 'H' :
        list_db(db, db_siz);
        break;
      case 'G' :
        puts("Not yet implemented\n");
        break;
      case 'A' :
        avslut = true;
        break;
    }    
  }
}



int main(int argc, char *argv[])
{
	char *array1[] = { "Laser",        "Polka",    "Extra" };
	char *array2[] = { "förnicklad",   "smakande", "ordinär" };
	char *array3[] = { "skruvdragare", "kola",     "uppgift" };

/*if (argc < 2)
	{
		printf("Usage: %s number\n", argv[0]);
	}
	else
	{*/
		item_t db[20]; // Array med plats för 20 varor
		int db_siz = 0;    // Antalet varor i arrayen just nu

		//int items = atoi(argv[1]); // Antalet varor som skall skapas

		//if (items > 0 && items <= 16)
	//	{
			/*for (int i = 0; i < items; ++i)
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
*/
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
    /*list_db(db, db_siz);
    puts("\n");
    edit_db(db);
    list_db(db, db_siz);
    puts("\n");
    add_item_to_db(db ,&db_siz);
    puts("\n");*/
   // list_db(db, db_siz);
   // remove_item_from_db(db, &db_siz);
   // list_db(db, db_siz);
    event_loop(db, db_siz); 
	
	return 0;
}
