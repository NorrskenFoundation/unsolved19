# Assignment 1

## Repo structure
        +--common.c
        +--common.h
        +--hash_table.c
        +--hash_table.h
        +--iterator.c
        +--iterator.h
        +--linked_list.c
        +--linked_list.h
        +--makefile
        +--test_hash_table.c
        +--test_iterator.c
        +--test_linked_list.c

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes:
```
git clone: git@github.com:IOOPM-UU/ali.hoseini.8952.git
```
navigate to the right folder by writing `cd fas1/inlupp1`

## Run tests
- `make test_hash_table` builds the tests for hash_table
- `./output` to run the test for hash table
- `make test_iterator` builds the tests for iterator
- `./output` to run the test for iterator
- `make test_linked_list` builds the test for linked_list
- `./output` to run the test for linked list

### mem_tests  
First you have to run one of the commands above then write
<pre>
make mem_test
</pre>
This will run valgrind for the test of the command

## Gcov
The results are generated by using gcov on test_hash_table.c and linked_list_list.c

<pre>
File 'test_hash_table.c'
Lines executed:90.46% of 241
Branches executed:100.00% of 48
Taken at least once:50.00% of 48
</pre>

<pre>
File 'test_linked_list.c'
Lines executed:97.75% of 89
Branches executed:100.00% of 2
Taken at least once:50.00% of 2
</pre>

## Authors
Nike Hiller
Ali Hoseini
11/11 - 2019
