#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "queue.h"
#include "tree.h"

#define maxi( a, b ) a > b ? a : b
#define TAM 1000
#define ERRO 1
#define TAMNAME 50
#define TAMNICK 10


TREE* newTree( ){
	TREE* nova = (TREE*)malloc(sizeof(TREE));
	nova->root = NULL;
	return nova;
}


USER* newUser(){
	USER* myuser = NULL;
	myuser = (USER*)malloc(sizeof(USER));
	printf("Digite o seu nome: ");
	scanf(" %[^\n]\n", myuser->name );
	//scanf("%c", &gambiarra ); // nao estou consseguindo limpar o buffer :(
	//printf("Esse eh o seu nomde %s\n", myuser->name );
	printf("Digite o seu apelido: ");
	scanf(" %[^\n]\n", myuser->nick );
	//printf("%s\n", myuser->nick );
	myuser->talks = newStack();
	myuser->asks = newQueue();
	myuser->friends = newTree(  );
	return myuser;
}


NO* newNode( USER* myuser ){
	if( myuser == NULL ) myuser = newUser();
	NO* mynode = (NO*)malloc(sizeof(NO));
	mynode->alt = 0;
	mynode->dad = mynode->left = mynode->right = NULL;
	mynode->person = myuser;
	return mynode;
}

void newAcount( TREE* rede ){
	NO* novo = newNode( NULL );
	if( wrapAddNode( rede, novo ) == ERRO ){
		printf("Este apelido ja existe. Tente novamente!\n");
		destroyUser( &novo->person );
		destroyNode( &novo );
	}
	else printf("Sua conta foi criada com sucesso!\n");
}

void destroyNode( NO** mynode ){
	if( *mynode == NULL ) return;
	destroyUser( &((*mynode)->person ) );
	free( (*mynode) );
	*mynode = NULL;
}

// as funcoes destroynode e destroytree apenas
// delasocam as estruturas arvore e no,
// sem desalocar a estrutura usuario
// ( pois esta esta tbm presente na arvore da rede )
// ela deve ser usada apenas quando formos destruir
// a arvore de amigos de um usuario.
void destroyTree( NO** mynode ){
	if( *mynode == NULL ) return;
	if( (*mynode)->left != NULL ) destroyNode( &((*mynode)->left) );
	if( (*mynode)->right != NULL ) destroyNode( &((*mynode)->right) );
	free( (*mynode) );
	*mynode = NULL;
}

void wrapDestroyTree( TREE** mytree ){
	destroyTree( &((*mytree)->root) );
	free( *mytree );
	*mytree = NULL;
}

void destroyUser( USER** myuser ){
	if( *myuser == NULL ) return;
	destroyNetwork( &(*myuser)->friends );
	destroyQueue( &(*myuser)->asks );
	destroyStack( &(*myuser)->talks );
	free( *myuser );
}

// esta funcao, alem de desalocar a memoria dos nos,
// tambem desaloca a memoria do usuario.
// ela deve ser usada ao finalizar o programa.
void clearNetwork( NO** mynode ){
	if( *mynode == NULL ) return;
	clearNetwork( &((*mynode)->left) );
	clearNetwork( &((*mynode)->right) );
	destroyUser( &((*mynode)->person) );
	free( *mynode );
	*mynode = NULL;
}

void destroyNetwork( TREE** mytree ){
	clearNetwork( &((*mytree)->root) );
	free( *mytree );
	*mytree = NULL;
}

int addNode( NO* treeno, NO* newno ){
	if( strcmp(treeno->person->nick, newno->person->nick ) == 0 )
		return ERRO;
	if( strcmp(treeno->person->nick, newno->person->nick ) < 0 ){
		if( treeno->right != NULL )return addNode( treeno->right, newno );
		newno->dad = treeno;
		treeno->right = newno;
		return !ERRO;
	}
	if( treeno->left != NULL ) return addNode( treeno->left, newno );
	newno->dad = treeno;
	treeno->left = newno;
	return !ERRO;
}

int wrapAddNode ( TREE* mytree, NO* newno ) {
	if( mytree->root == NULL ){
		mytree->root = newno;
		return 0;
	}
	return addNode( mytree->root, newno );
}

void addTree( TREE* mytree , NO* myno ){
	if( strcmp(mynode->person->nick, str) == 0 )
		return mynode;
	if( strcmp(mynode->person->nick, str) < 0 )
		return findNode( mynode->right, str );
	return findNode( mynode->left, str );
}

void dumpFriends( NO* mynode ){
	if( mynode == NULL ) return;
	dumpFriends( mynode->left );
	printf("%s ", mynode->person->nick );
	dumpFriends( mynode->right );
}

void dumpNetwork( NO* mynode ){
	if( mynode == NULL ) return;
	dumpNetwork( mynode->left );
	printf("Nome: %s\nApelido: %s\n", mynode->person->name, mynode->person->nick );
	printf("lista de amigos: ");
	dumpFriends( mynode->person->friends->root );
	printf("\n\n");
	dumpNetwork( mynode->right );
	//printf("%d\n", mynode->alt );
}
