#include <stdio.h>
#include <stdlib.h>
#include "static_stack.h"
#include <string.h>
#define TAMSTACK 20

void newStack(STACK *P){
    P->topo=-1;
}

int isEmptyStack(STACK *P){
    if (P->topo==-1)
        return 1;
    else return 0;
}

int isFullStack(STACK *P){
    if (P->topo==TAMSTACK-1)
        return 1;
    else return 0;
}

void push( STACK *P, char* autor, char* text, int *erro ){                     //TEXT criada pelo autor, STACK do destinatario
    if(!isFullStack(P)){
        *erro=0;
        P->topo++;
        strcpy( P->mensagens[P->topo].autor, autor );
        strcpy( P->mensagens[P->topo].texto, text );
    }
    else *erro=1;
}

void clearStack(STACK *P){                                  //Deleta a mensagem no topo da STACK de mensagens do usuario
    P->topo = -1;
}

void popStack( STACK* myst ){
    if( myst->topo >= 0 ) myst->topo--;
}

void dumpStack(STACK *P, int *erro){
    if(!isEmptyStack(P)){
        *erro=0;
        while(!isEmptyStack(P)){
            printf("(%s): %s\n", P->mensagens[P->topo].autor,  P->mensagens[P->topo].texto );
            P->topo--;
        }
    }
    else *erro=1;
}
