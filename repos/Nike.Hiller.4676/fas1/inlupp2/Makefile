ui:
	gcc -ggdb -Wall -c -std=c11 src/utils.c src/common.c src/linked_list.c src/hash_table.c src/hash_functions.c src/logic.c src/ui.c

logic_test:
<<<<<<< HEAD
	gcc -ggdb -Wall -std=c11 logic_test.c utils.c common.c linked_list.c hash_table.c hash_functions.c logic.c ui.c  -o output -lcunit

main:
	gcc -g -Wall -std=c11 main.c utils.c common.c linked_list.c hash_table.c hash_functions.c logic.c  -o output
=======
	gcc -ggdb -Wall -std=c11 tests/logic_test.c src/utils.c src/common.c src/linked_list.c src/hash_table.c src/hash_functions.c src/logic.c src/ui.c  -o output -lcunit -g -O0 -coverage

main:
	gcc -ggdb -Wall -std=c11 src/utils.c src/common.c src/linked_list.c src/hash_table.c src/hash_functions.c src/logic.c src/ui.c src/main.c -o webstore  
>>>>>>> a0dc8116782f60cb9860d66a41cdbcd2b665e18f

mem_test:
	valgrind --leak-check=full --track-origins=yes ./output

run:
	./webstore
