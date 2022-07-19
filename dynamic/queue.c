#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

#define TAMNICK 15

QUEUE* newQueue(){
	QUEUE* nova = (QUEUE*)malloc(sizeof(QUEUE));
	nova->last = NULL;
	nova->first = NULL;
	nova->size = 0;
	return nova;
}

NOF* newNodeQueue( char* str ){
	NOF* novo = (NOF*)malloc(sizeof(NOF));
	novo->autor = str;
	novo->next = NULL;
	return novo;
}

void destroyNodeQueue( NOF** mynode ){
	free( (*mynode)->autor );
	(*mynode)->autor = NULL;
	free( (*mynode) );
	*mynode = NULL;
}

void push_back( char* str, QUEUE* myq ){
	(myq)->size++;
	NOF* mynode = newNodeQueue( str );
	if( (myq)->last == NULL ){
		(myq)->last = mynode;
		(myq)->first = mynode;
		return;
	}
	myq->last->next = mynode;
	myq->last = mynode;
	return;
}

void popQueue( QUEUE* myq ){
	if( myq == NULL || myq->first == NULL ) return;
	if( myq->first == myq->last ){
		destroyNodeQueue( &(myq->first) );
		myq->first = NULL;
		myq->last = NULL;
		myq->size--;
		return;
	}
	NOF* aux = myq->first;
	myq->first = myq->first->next;
	destroyNodeQueue( &aux );
	myq->size--;
	return;
}

int size( QUEUE* myq ){
	return myq->size;
}

char* front( QUEUE* myq ){
	if( myq == NULL || myq->first == NULL ) return NULL;
	return myq->first->autor;
}

void destroyQueue( QUEUE** myq ){
	if( *myq == NULL ) return;
	while( (*myq)->size ) popQueue( *myq );
	free( *myq );
	*myq = NULL;
}
