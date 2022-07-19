#include <stdio.h>
#include <string.h>
#include "static_queue.h"
#include <stdio.h>

#define TAMQUEUE 20

void newQueue( QUEUE *new ) {
	new->beg = new->end = 0;
	return;
}

void clearQueue(QUEUE *curr) {
	(*curr).beg = (*curr).end = 0;
}

int fullQueue(QUEUE curr) {
	if(sizeQueue(curr) == TAMQUEUE-1) return 1;
	return 0;
}

int emptyQueue(QUEUE curr) {
	if(sizeQueue(curr) == 0) return 1;
	return 0;
}

int sizeQueue(QUEUE curr) {
	if(curr.end >= curr.beg) return curr.end - curr.beg;
	return TAMQUEUE - (curr.beg-curr.end);
}

int pushQueue(QUEUE *curr, char name[]) {
	if(!fullQueue(*curr)) {
		strcpy((*curr).names[(*curr).end], name);
	 	(*curr).end++;
		(*curr).end%= TAMQUEUE;
		return 1;
	}
	return 0;
}

int popQueue(QUEUE *curr) {
	if(!emptyQueue((*curr))) {
		(*curr).beg++;
		(*curr).beg %= TAMQUEUE;
		return 1;
	}
	return 0;
}

void dumpQueue(QUEUE* curr) {
	int i = 0, j = curr->beg;
	while(i < sizeQueue(*curr)) {
		printf("%s\n", curr->names[j%TAMQUEUE]);
		i++;
		j++;
	}
	clearQueue( curr );
}

char* frontQueue(QUEUE* curr) {
	if(!emptyQueue(*curr))
		return ( curr->names[curr->beg] );
	else return NULL;
}
