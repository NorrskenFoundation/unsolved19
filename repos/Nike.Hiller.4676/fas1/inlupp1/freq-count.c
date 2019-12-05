#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"


#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

typedef struct freq freq_t;
struct freq
{
  char *key;
  int value;
};

static int cmpstringp(const void *p1, const void *p2)
{
  freq_t *w1 = (freq_t *)p1;
  freq_t *w2 = (freq_t *)p2;
  
  return strcmp(w1->key, w2->key);
}


void sort_keys(freq_t *array_keys, size_t no_keys)
{
  qsort(array_keys, no_keys, sizeof(struct freq), cmpstringp);
}

void process_word(char *word, ioopm_hash_table_t *ht)
{

  option_t word_value = ioopm_hash_table_lookup(ht, char_elem(word));
  if (word_value.success)
    {
      ioopm_hash_table_insert(ht, char_elem(word), int_elem(word_value.value.int_nr +1 ));
    }
  else
    {
      char *heap_word = strdup(word);
      ioopm_hash_table_insert(ht,char_elem(heap_word), int_elem(1));
    }
}


void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");
  
  while (true) 
    {
      char *buf = NULL;
      size_t len = 0;
      getline(&buf, &len, f);
      if (feof(f))
	{
	  free(buf);
	  break;
	}
      
      for (char *word = strtok(buf, Delimiters);
           word && *word;
           word = strtok(NULL, Delimiters)
           )
        {
          process_word(word, ht);
        }

      free(buf);
    }
  
  fclose(f);
}

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(compare_string_elements, hash_function);
  if (argc > 1)
    {
      for (int i = 1; i < argc; ++i)
        {
	  process_file(argv[i], ht);
	}
      
      ioopm_list_t *keys = ioopm_hash_table_keys(ht);
      ioopm_list_t *values = ioopm_hash_table_values(ht);
      size_t size = ioopm_linked_list_size(keys);
      freq_t *array_keys_values = calloc(1, size*sizeof(struct freq));
      
      for(size_t i = 0; i < size; ++i) 
	{
	  array_keys_values[i].key = ioopm_linked_list_get(keys, i).string;
	  array_keys_values[i].value = ioopm_linked_list_get(values, i).int_nr;
	}
             
       sort_keys(array_keys_values, size); 
       
       
	 for(size_t i = 0; i < size; ++i)
	 {
	 printf("%s, %d\n", array_keys_values[i].key,  array_keys_values[i].value); 
	 
	 free(array_keys_values[i].key);
	 }
	 
	 printf("Number of unique word: %lu\n", ioopm_linked_list_size(keys));
	 ioopm_linked_list_destroy(keys);
	 ioopm_linked_list_destroy(values);
	 
	 free(array_keys_values);
	 
    }
  else
    {
	     puts("Usage: freq-count file1 ... filen");
	   }
       
       ioopm_hash_table_destroy(ht);
       return 0;
    }

