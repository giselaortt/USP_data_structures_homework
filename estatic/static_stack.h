#ifndef _STATIC_STACK_H
#define _STATIC_STACK_H

#define TAMSTACK 20                                         //Número máximo de mensagens
#define TAMNICK 15
#define TAMTEXT 144

typedef struct _Carta{
    char autor[TAMNICK];
    char texto[TAMTEXT];
} TEXT;

typedef struct _Pilha{                                      //Pilha de mensagens
    int topo;
    TEXT mensagens[TAMSTACK];                            //vetor de struct TEXT
} STACK;

void newStack(STACK *P);

int isEmptyStack(STACK *P);

int isFullStack(STACK *P);

void push(STACK *P, char* autor, char* text, int *erro);

void clearStack(STACK *P);

void popStack( STACK* myst );

void dumpStack(STACK *P, int *erro);

//TEXT* lermsg();

#endif
