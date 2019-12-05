#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"
#include "common.h"

/*
 * @file hash_table.c
 * @author Ali Hoseini & Nike Hiller
 * @date 26 oct 2019 
 * @brief hash table functions
 */  

#define No_Buckets 17

typedef struct entry entry_t;
struct entry
{
  elem_t key;
  elem_t value;   
  entry_t *next; 
};

struct hash_table
{
  entry_t *buckets;
  size_t size;
  size_t capacity;
  double load_factor;
  ioopm_eq_function eq_func;
  ioopm_hash_function hash_func;
};

ioopm_hash_table_t *ioopm_hash_table_dynamic(ioopm_eq_function eq_func, ioopm_hash_function hash_func, double load_factor, size_t capacity)
{
  ioopm_hash_table_t *hash_table = calloc(1, sizeof(ioopm_hash_table_t));
  hash_table->eq_func = eq_func;
  hash_table->hash_func = hash_func;
  hash_table->load_factor = load_factor;
  hash_table->capacity = capacity;
  hash_table->buckets = calloc(capacity, sizeof(entry_t));
  return hash_table;
}

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function eq_func, ioopm_hash_function hash_func)
{
  double load_factor = 0.75;
  ioopm_hash_table_t *result = ioopm_hash_table_dynamic(eq_func, hash_func, load_factor, No_Buckets);
  return result;
}

ioopm_hash_table_t *resize(ioopm_hash_table_t *hash_table)
{
  if((hash_table->capacity)*(hash_table->load_factor) < (hash_table->size))
    {
      ioopm_list_t *keys = ioopm_hash_table_keys(hash_table);
      ioopm_list_t *values = ioopm_hash_table_values(hash_table);
      ioopm_hash_table_clear(hash_table);
      size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};

      int i = 0;
      int prime_length = sizeof(primes)/sizeof(primes[0]);
      while(primes[i] <= hash_table->capacity && i < prime_length)
	{
	  i++;
	}
      hash_table->capacity = primes[i];
      hash_table->buckets = realloc(&hash_table->capacity, sizeof(entry_t));

      for(int j = 0; j < ioopm_linked_list_size(keys); j++)
	{
	  ioopm_hash_table_insert(hash_table, ioopm_linked_list_get(keys, j), ioopm_linked_list_get(values, j));
	}
      ioopm_linked_list_destroy(keys);
      ioopm_linked_list_destroy(values);
    }
  return hash_table;
}

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  

  return new_entry;
}
static void entry_destroy(entry_t *entry)
{
  free(entry);
}



static entry_t *find_previous_entry_for_key(entry_t *entry, elem_t key, ioopm_eq_function eq_func)
{
  entry_t *cursor = entry;

  while (1)
    {
      if(cursor->next == NULL){
	return cursor;
      }
      else if(eq_func(cursor->next->key, key)){
	return cursor;
      } 
      else{
	cursor = cursor->next;
      }
    }
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  resize(ht);
  unsigned long bucket = ht->hash_func(key) % No_Buckets;
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key, 
					       ht->eq_func);
  
  entry_t *next = entry->next;

  if (next != NULL && ht->eq_func(next->key, key))
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, NULL);
    }
}


option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{

  unsigned long bucket = ht->hash_func(key) % No_Buckets;
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->eq_func);
  entry_t *next = tmp->next;

  if (next && ht->eq_func(next->key, key))
    {
      option_t result;
      result.success = true;
      result.value = next->value;
      return result;

    }
  else
    {
      option_t result = { .success = false };
      return result;
    }
}

elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{

  option_t result = ioopm_hash_table_lookup(ht, key);
  if (!result.success)
    {
      printf("%s this does not work\n", result.value.string);
      return result.value;
    }
  unsigned long bucket = ht->hash_func(key) % No_Buckets;
  entry_t *previous = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->eq_func);
  entry_t *to_remove = previous->next;
  elem_t value_removed = to_remove->value;

  if (ht->eq_func(to_remove->key, key))
    {
      previous->next = to_remove->next;
      entry_destroy(to_remove);
      return value_removed;   
    }

  if (ht->eq_func(to_remove->key, key) && to_remove->next == NULL)
    {
      previous->next = NULL;
      entry_destroy(to_remove);
      return value_removed; 
    }

  return value_removed;
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  size_t capacity = ht->capacity;
  for (int i = 0; i < capacity; ++i)
    {
      entry_t *cursor = ht->buckets[i].next;
      for (int j = 0; cursor != NULL; ++j)
	{
	  entry_t *tmp = cursor;
	  cursor = cursor->next;
	  entry_destroy(tmp);
	}

    }
  free(ht->buckets);
  free(ht);
  return;
}


void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; ++i)
    {
      entry_t *cursor = ht->buckets[i].next;
      ht->buckets[i].next = NULL;
      for (int j = 0; cursor != NULL; ++j)
	{
	  entry_t *tmp = cursor;
	  cursor = cursor->next;
	  entry_destroy(tmp);
	}
    }
  return; 

}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; ++i)
    {
      entry_t *cursor = ht->buckets[i].next;
      if (cursor != NULL)
	{
	  return false;
	}
    }
  return true;
}

/*
bool ioopm_hash_table_empty_rec(ioopm_hash_table_t *ht)
{
  return bucket_is_empty_rec(ht->buckets[0], 0, 17);
}
​
bool bucket_is_empty_rec(entry_t *bucket, i, bucket_n)
{
  if (i >= bucket_n) {
    return true;
  }
  if(bucket != NULL)
  {
    return false;
  }
  return bucket_is_empty_rec(bucket->next, i+1, max_i);
}
*/



bool hash_table_lookup_caller(ioopm_hash_table_t *ht, elem_t key)
{

  option_t result = ioopm_hash_table_lookup(ht, key);
  if (result.success)
    {

      printf("key %d maps to %s!\n", key.int_nr, result.value.string);
    }
  else
    {

      printf("key %d does not map to anything!\n", key.int_nr);
    }
  ioopm_hash_table_destroy(ht);
  return 0;
}



size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  size_t counter = 0;
  for (int i = 0; i < No_Buckets; ++i)
    {
      entry_t *cursor = ht->buckets[i].next;

      for (int j = 0; cursor != NULL; ++j)
	{
	  ++counter;
	  cursor = cursor->next;
	}
    }
  return counter;

}


ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *result = ioopm_linked_list_create(ht->eq_func);
  entry_t *cursor;

  for(size_t i = 0; i < No_Buckets; i++)
    {
      cursor = (&ht->buckets[i])->next;
      while (cursor != NULL)

	{
	  ioopm_linked_list_append(result, cursor->key);
	  cursor = cursor->next;	  
	}
    }

  return result;
}



ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  ioopm_list_t *result = ioopm_linked_list_create(ht->eq_func);
  entry_t *cursor;

  for (size_t i = 0; i < No_Buckets; ++i)
    {
      cursor = (ht->buckets[i].next);
      while (cursor != NULL)
	{
	  ioopm_linked_list_append(result, cursor->value);
	  cursor = cursor->next;
	}
    }
  return result;
}


bool predicate(elem_t key, void *extra)
{
  return key.int_nr > 36;
}

void apply_print_h(elem_t key, elem_t value, void *extra)
{
  printf("The key is:%d The value is:%s\n", key.int_nr, value.string);
}  

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply, void *extra)
{
  for(int i = 0; i < No_Buckets; ++i)
    {
      entry_t *cursor = &ht->buckets[i];
      entry_t *follow = cursor->next;
      while (follow != NULL)
	{
	  cursor = follow;
	  follow = follow->next;
      
	  (apply(cursor->key, (cursor->value), extra));
	}   
    }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht,ioopm_predicate key_equiv, elem_t key)
{

  return ioopm_hash_table_any(ht,key_equiv, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht,ioopm_predicate value_equiv, elem_t value)
{
  return (ioopm_hash_table_any(ht, value_equiv, &value.string));
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate p, void *x)
{
  bool result = true;
  for(int i = 0; i < No_Buckets; ++i)  
    {
      entry_t *cursor = ht->buckets[i].next;
      while (cursor != NULL && result)
	{
	  result = result && p(int_elem(cursor->key.int_nr), char_elem(cursor->value.string), x);
	  cursor = cursor->next;
	}
    }
  return result;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate p, void *x)
{
  for(int i = 0; i < No_Buckets; ++i)  
    {
      entry_t *cursor = ht->buckets[i].next;
      while (cursor != NULL)
	{
	  bool result = p((cursor->key), (cursor->value), x);

	  if(result){
	    return true;
	  }
	  cursor = cursor->next;
	}
    }
  return false;
}
