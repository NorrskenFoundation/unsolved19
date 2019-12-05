#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

struct item
{
    char *name;
    char *desc;
    int price;
    char *shelf;
};


typedef struct item item_t;




  


char *magick(char *array_1[], char *array_2[], char *array_3[], int array_length)
{
   // int buf_size = 255;
    char buf[255];
    buf[0]= '\0';
    char *word_1 = array_1[rand() % array_length];
    char *word_2 = array_2[rand() % array_length];
    char *word_3 = array_3[rand() % array_length];

    strncat(buf, word_1, 255);
    strncat(buf,"-", 255);
    strncat(buf, word_2, 255);
    strncat(buf, " ", 255);
    strncat(buf, word_3, 255);
    strncat(buf, "\0", 255);

    return strdup(buf);

}


void print_item(item_t *item)
{
   printf(" Name: %s\n Desc: %s\n Price: %d\n Shelf: %s\n-------------\n", item->name, item->desc, item->price, item->shelf);
}

item_t make_item(char* name, char *desc, int price, char* shelf)
{
    item_t item;
    item.name = name;
    item.desc = desc;
    item.price = price;
    item.shelf = shelf;

    return item;
}

item_t input_item()
{
    char *name = ask_question_string("What is the name of your item?");
    char *desc = ask_question_string("How would you describe your item?");
    int price = ask_question_int("Whats is the price of your item?");
    char *shelf = ask_question_shelf("What shelf do you wan to put it on");
    return make_item(name, desc, price, shelf);
}

void list_db(item_t *db, int db_size) //db_size is number of items
{
    for (int i = 0; i < db_size; ++i)
    {
        printf("%d. %s\n", i+1, db[i].name);
    }
    
}

void edit_db(item_t *db, int db_size)
{
    
    int answer = ask_question_int("Which item do you want to fuck up?");

    
    while(answer >= db_size || answer <= 0)
    {
        answer = ask_question_int("Wrong input write something between 1 and 16");
    }

    print_item(&db[answer -1]);
    item_t new_item = input_item();
    db[answer-1] = new_item; 

}

//-------menu-----------

void print_menu()
{
    printf("[A] Add merch\n[L] List merch\n[R] Remove merch\n[E] Edit merch\n[S] Show stock\n[P] Replenish\n[C] Create cart\n[M] Remove cart\n[D] Add to cart\n[O] Calculate cost\n[T] Checkout\n[U] Undo\n[Q] Quit");
}

char ask_question_menu()
{
    print_menu();

    char *input = ask_question_string("What do you want to do?");

    while (!strpbrk("AaLlRrEeSsPpCcMmDdOoTtUuQq", input))
    {
        input = ask_question_string("Not a valid input");
    }
    char choice = toupper(input[0]);
    return choice;
    
}

void add_item_to_db(item_t *db, int *db_size)
{
    item_t item = input_item();
    db[*db_size] = item;
    *db_size = *db_size +1;
}

void remove_item_from_db(item_t *db, int *db_size)
{
    list_db(db, *db_size);

    int answer = ask_question_int("What item do you want to remove?");

     while(answer > *db_size || answer <= 0)
    {
        answer = ask_question_int("Wrong input write something between 1 and 16");
    }

    print_item(&db[answer -1]);

    for (int i = answer; i < *db_size; ++i)
    {
        db[i -1] = db[i];
    }
        *db_size = *db_size - 1;
}


void event_loop(ioopm_hash_table_t *htns, ioopm_hash_table_t *htsn)
{
  char choice = ask_question_menu();

  while(choice != 'Q')
    {
      if (choice == 'A') //add merch
        {
          add_item_to_db(db, db_size);
          list_db(db, *db_size);
          choice = ask_question_menu();
            
        }
      else if (choice == 'L') //list merch
        {
          remove_item_from_db(db, db_size);
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'R') //remove merch
        {
          edit_db(db, *db_size);
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'E') //edit merch
        {
          puts("Not implemeted yet");
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'S') //show stock
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'P') //replenish
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'C') //create cart
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'M') //remove cart
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'D') //add to cart
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'O') //Calculate loss
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'T') //Checkout
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
      else if (choice == 'U') //Undo
        {
          list_db(db, *db_size);
          choice = ask_question_menu();
        }
    }
    
}

int main(int argc, char *argv[])
{

  char *array1[] = {"happy", "sad", "angry"}; 
  char *array2[] = {"dog", "cat", "bird" }; 
  char *array3[] = { "black", "blue", "purple"};

  if (argc < 2)
  {
    printf("Usage: %s number\n", argv[0]);
  }
  else
  {
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu

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
        char *name = magick(array1, array2, array3, 3); 
        char *desc = magick(array1, array2, array3, 3); 
        int price = random() % 200000;
        char shelf[] = { random() % ('Z'-'A') + 'A',
                         random() % 10 + '0',
                         random() % 10 + '0',
                         '\0' };
        item_t item = make_item(name, desc, price, shelf);

        db[db_siz] = item;
        ++db_siz;
      }

     event_loop(db, &db_siz);


  }


  return 0;


}
