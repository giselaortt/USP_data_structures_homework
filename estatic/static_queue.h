#ifndef _STATIC_QUEUE_H
#define _STATIC_QUEUE_H

#define TAMNICK 15
#define TAMQUEUE 20

typedef struct static_queue {
	char names[TAMQUEUE][TAMNICK];
	int beg, end;
} QUEUE;

void newQueue ( QUEUE* );

void clearQueue ( QUEUE * );

int pushQueue ( QUEUE *, char name[] );

int popQueue ( QUEUE * );

int sizeQueue ( QUEUE );

int emptyQueue ( QUEUE );

int fullQueue ( QUEUE );

char* frontQueue ( QUEUE* );

void dumpQueue ( QUEUE* );

#endif
