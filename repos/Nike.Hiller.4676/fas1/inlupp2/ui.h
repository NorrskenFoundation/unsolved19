#ifndef __UI_H__
#define __UI_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"
#include "hash_table.h"
#include "linked_list.h"


//----------- ui ---------------//

void event_loop(ioopm_hash_table_t *htns, ioopm_hash_table_t *htsn);

elem_t input_merch();

elem_t make_merch(char *name, char *desc, int price);
//todo void undo_action();

elem_t make_shelf(char* loc, int qty);

#endif
