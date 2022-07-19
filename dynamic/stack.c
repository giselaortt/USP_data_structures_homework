#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

#define TAMTEXT 144 // tamanho maximo de uma message
#define TAMNICK 15
#define false 0
#define true 1

TEXT* newText( char* autor ){
	TEXT* novo = (TEXT*)malloc(sizeof(TEXT));
	novo->text = (char*)malloc(sizeof(char)*TAMTEXT);
	novo->autor = autor;
	printf("Digite a message:\n");
	scanf(" %[^\n]", novo->text );
	return novo;
}

STACK* newStack(){
	STACK* nova = (STACK*)malloc(sizeof(STACK));
	nova->top = NULL;
	nova->size = 0;
	return nova;
}

NOP* newNodeStack( TEXT* mytext ){
	NOP* novo = (NOP*)malloc(sizeof(NOP));
	novo->text = mytext;
	novo->prev = NULL;
	return novo;
}

void destroyNodeStack( NOP** mynode ){
	if(mynode != NULL && *mynode != NULL) {
		free( (*mynode)->text->autor );
		free( (*mynode)->text->text );
		free( (*mynode)->text );
		free( (*mynode) );
		*mynode = NULL;
	}
}

void push( TEXT* mytext, STACK* mystack ){
	NOP* mynode = newNodeStack( mytext );
	(mystack)->size++;
	mynode->prev = (mystack)->top;
	(mystack)->top = mynode;
}

void popStack( STACK* mystack ){
	if( mystack == NULL || (mystack)->top == NULL ) return;
	if( mystack->size == 1 ){
		destroyNodeStack( &(mystack->top) );
		mystack->top = NULL;
		mystack->size--;
		return;
	}

	NOP* aux = mystack->top->prev;
	destroyNodeStack( &(mystack->top) );
	mystack->top = aux;
	mystack->size--;
	return;
}

TEXT* top( STACK* mystack ){
	return mystack->top->text;
}

void destroyStack( STACK** myst ){
	if( *myst == NULL ) return;
	while( (*myst)->size ) popStack( *myst );
	free( *myst );
	*myst = NULL;
}

int empty( STACK* myst ){
	if( myst == NULL || myst->size == 0 ) return true;
	return false;
}

void dumpStack( STACK* myst ){
	printf("Voce tem %d menssagens:\n\n", myst->size );
	while( !empty( myst ) ){
		printf("  De: %s\n", myst->top->text->autor );
		printf("  %s\n\n", myst->top->text->text );
		popStack( myst );
	}
}
