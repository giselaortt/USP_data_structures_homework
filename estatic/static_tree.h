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

//recebe um ponteiro para árvore e a inicializa
void newTree( TREE* myt );

//inicializa um usuário
void newUser( NODE* myuser, char* name, char* nick );

//adiciona um usuário na árvore
int addUser( TREE* myt, int node, char* name, char* nick );

//procura um usuário na árvore e o retorna
NODE* findUser( TREE* myt, int node, char* nick );

//função para facilitar o uso da addUser();
int wrapAddUser( TREE* myt, char* name, char* nick );

//função para facilitar o uso da findUser();
NODE* wrapFindUser( TREE* myt, char* nick );

//imprime todos os nós da árvore
void dumpTree( TREE* myt, int node );

//apaga a árvore
void clearTree( TREE* myt );

//procura um usuário na lista de amigos
NODE* findFriend( NODE* myuser, char* nick );

//verifica se a árvore está cheia
int isFull( TREE* myt );

#endif
