# Assignment 2

A simple webstore backend

## Structure

    Documention
    profiling
    src
        +--common.c
        +--common.h
        +--hash_functions.c
        +--hash_functions.h
        +--hash_table.c
        +--hash_table.h
        +--iterator.h
        +--linked_list.c
        +--linked_list.h
        +--linked_list_test.c
        +--logic.c
        +--logic.h
        +--main.c
        +--ui.c
        +--ui.h
        +--utils.c
        +--utils.h
    tests
        +--linked_list.c
        +--logic_test.c
    Doxyfile
    Makefile


## Getting started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes
```
git clone git@github.com:JonathanLindroth/IOOPM_Sprint2.git
```
### Running the program

In the IOOPM_Sprint2/inlupp2 repo write:
```
make run
```

### Running the tests

```
make logic_test
make mem_test
```
## Gcov

Result based on test by logic_test.c
```
File 'src/logic.c'
Lines executed:77.62% of 143
Branches executed:70.59% of 34
Taken at least once:58.82% of 34
Calls executed:71.60% of 81
Creating 'logic.c.gcov'
```


## Authors
Jonathan Lindroth  
Nike Hiller
