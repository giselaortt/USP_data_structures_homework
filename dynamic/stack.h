#ifndef STACK_H
#define STACK_H

#define TAMTEXT 144 // tamanho maximo de uma message
#define TAMNICK 15

typedef struct message{
	char* text;
	char* autor;
}TEXT;

typedef struct nodeFromStck{
	struct nodeFromStck* prev;
	TEXT* text;
}NOP;

typedef struct stack{
	NOP* top;
	int size;
} STACK;

// aloca a memoria para uma message
TEXT* newText( char* autor );
// aloca a memoria para uma stack
STACK* newStack();
// aloca a memoria para um no
NOP* newNodeStack( TEXT* mytext );
// desaloca a memoria para um no
void destroyNodeStack( NOP** mynode );
// recebe um no e uma stack e adciona o no na stack
void push( TEXT* mytext, STACK* mystack );
// retira um no da stack
void popStack( STACK* mystack );
// retorna a primeira mensagem da stack
TEXT* top( STACK* mystack );
// desaloca a memoria de uma stack e de todos os seus nos
void destroyStack( STACK** myst );
// imprime todas as menssagens da stack
void dumpStack( STACK* myst );

int empty( STACK* myst );

#endif
