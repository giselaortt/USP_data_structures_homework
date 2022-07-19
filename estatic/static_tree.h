#ifndef _STATIC_TREE_H
#define _STATIC_TREE_H

#include "static_stack.h"
#include "static_queue.h"

#define TAMNICK 15
#define TAMNAME 50
#define TAMTREE 50
#define TAMFRIENDS 50

// por simplicidade, vamos guardar os amigos de um usuario linearmente,
// diferente do que fizemos na parte dinamica do trabalho.

typedef struct user{
	char name[TAMNAME];
	char nick[TAMNICK];
	QUEUE asks;
	STACK texts;
	struct user *friends[TAMFRIENDS];
	int numfriends;
	int father;
	int left;
	int right;
}NODE;

typedef struct tree{
	NODE users[TAMTREE];
	int root;
	int full;
}TREE;

//recebe um ponteiro para �rvore e a inicializa
void newTree( TREE* myt );

//inicializa um usu�rio
void newUser( NODE* myuser, char* name, char* nick );

//adiciona um usu�rio na �rvore
int addUser( TREE* myt, int node, char* name, char* nick );

//procura um usu�rio na �rvore e o retorna
NODE* findUser( TREE* myt, int node, char* nick );

//fun��o para facilitar o uso da addUser();
int wrapAddUser( TREE* myt, char* name, char* nick );

//fun��o para facilitar o uso da findUser();
NODE* wrapFindUser( TREE* myt, char* nick );

//imprime todos os n�s da �rvore
void dumpTree( TREE* myt, int node );

//apaga a �rvore
void clearTree( TREE* myt );

//procura um usu�rio na lista de amigos
NODE* findFriend( NODE* myuser, char* nick );

//verifica se a �rvore est� cheia
int isFull( TREE* myt );

#endif
