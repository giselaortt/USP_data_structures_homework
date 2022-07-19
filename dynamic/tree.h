#ifndef TREE_H
#define TREE_H

#include "stack.h"
#include "queue.h"

#define ERRO 1
#define TAMNAME 50
#define TAMNICK 15

typedef struct user USER;

typedef struct no NO;

typedef struct tree TREE;

typedef struct user{
	char name[TAMNAME];
	char nick[TAMNICK];
	TREE* friends;
	STACK* talks;
	QUEUE* asks;
}USER;

typedef struct no{
    struct no* left;
    struct no* right;
    struct no* dad;
    USER* person;
    int alt; // altura do no atual
} NO;

typedef struct tree{
	NO* root; // altura da MENOR folha
}TREE;

// aloca a memoria para a arvore
void newTree( TREE** nova );
// aloca a memoria para uma conta
USER* newUser();
// aloca a memoria para um no de arvore
NO* newNode( USER* myuser );
// as funcoes destroynode e destroytree apenas
// delasocam a memoria das estruturas arvore e no,
// sem desalocar a estrutura usuario
// ( pois esta esta tbm presente na arvore da rede )
// ela deve ser usada apenas quando formos destruir
// a arvore de amigos de um usuario.
void destroyNode( NO** mynode );

void destroyTree( NO** mytree );

void wrapDestroyTree( TREE** mytree );

// PREOBLEMAS AQUI!!
void destroyUser( USER** myuser );
// estas funcoes, alem de desalocar a memoria dos nos da arvore,
// tambem desalocam a memoria do usuario.
// a clearRede desaloca todos os usuarios da rede
void clearRede( NO** mynode );
// a destroi rede desaloca todos os usuaris e tambem a rede em si
void destroyRede( TREE** mytree );
// Adciona um no na arvore, recursivamente
int addNode( NO* treeno, NO* newno );

int wrapAddNode ( TREE* mytree, NO* newno );

//estas funcoes trabalham em conjunto de forma a
// receber duas arvores e adcionar todos os usuarios da segunda
// na primeira arvore.
void addTree( TREE* mytree, NO* myno );

void wrapAddTree( TREE* first, TREE* sec );

// Acha um no na arvore recursivamente. Deve sempre ser 
// chamada pelo no root da arvore.
NO* findNode( NO* mynode, char* str );

// imprime em preorder os parceiros de um usuario
void dumpFriends( NO* mynode );

// imprime em preorder as informacoes dos usuarios e seus parceiros
void dumpRede( NO* mynode );

// adiciona conta na rede
void newAcount( TREE* rede );

#endif
