hash_table:
	gcc -pedantic -Wall -g -c hash_table.c -o output

linked_list:
	gcc -pedantic -Wall -g -c linked_list.c -o output

iterator:
	gcc -pedantic -Wall -g -c iterator.c -o output

test_hash_table:
	gcc -ggdb -Wall -std=c11 test_hash_table.c hash_table.c linked_list.c  common.c -o output

test_linked_list:
	gcc -ggdb -Wall -std=c11 test_linked_list.c common.c linked_list.c  -o output -lcunit

test_iterator:
	gcc -ggdb -Wall -std=c11 -fprofile-arcs -ftest-coverage test_iterator.c linked_list.c common.c iterator.c  -o output -lcunit

freq_count:
	gcc -pedantic -Wall -g freq-count.c hash_table.c linked_list.c common.c -o output

coverage_hash_table:
	gcc -ggdb -Wall -std=c11 -fprofile-arcs -ftest-coverage test_hash_table.c hash_table.c linked_list.c  common.c -o output
	./output
	gcov -b test_hash_table.c

coverage_linked_list:
	gcc -ggdb -Wall -std=c11 -fprofile-arcs -ftest-coverage test_linked_list.c common.c linked_list.c  -o output -lcunit
	./output
	gcov -b test_linked_list.c

mem_test:
	valgrind --leak-check=full --track-origins=yes ./output

prof_compile:
	gcc -pg -Wall freq-count.c hash_table.c linked_list.c common.c -o prof_output
