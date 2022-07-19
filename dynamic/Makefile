all: clean stack.o queue.o tree.o menu.o ex

clean:
	find -name '*.o' | xargs rm -rf {}
	find -name '*.zip' | xargs rm -rf {}
	find -name 'ex' | xargs rm -rf {}

zip:
	zip -r linked *.h *.c Makefile

stack.o:
	gcc -Wall stack.c -c

queue.o:
	gcc -Wall queue.c -c

tree.o:
	gcc -Wall tree.c -c

menu.o:
	gcc -Wall menu.c -c

ex:
	gcc -Wall main.c stack.o queue.o tree.o menu.o -o ex
