#ifndef QUEUE_H
#define QUEUE_H

typedef struct nodeFromQueue{
	struct nodeFromQueue* next;
	char* autor;
}NOF;

typedef struct queue{
	NOF* last;
	NOF* first;
	int size;
} QUEUE;

// Aloca a memoria para uma queue
QUEUE* newQueue();

// Aloca a memoria para um no
NOF* newNodeQueue( char* str );

// desaloca a memoria de um no
void destroyNodeQueue( NOF** mynode );

// adciona um no a queue
void push_back( char* str, QUEUE* myq );

// retira um no da queue
void popQueue( QUEUE* myq );

// recebe uma queue devolve o seu tamanho
int size( QUEUE* myq );

// recebe uma queue devolve o pedido que esta no comeco desta
char* front( QUEUE* myq );

// desaloca a memoria da queue e todos os seus nos
void destroyQueue( QUEUE** myq );

#endif
