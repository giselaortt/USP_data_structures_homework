#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "menu.h"

#define TAMNICK 15
#define ERRO 1

int addFriend( TREE* network, char* first, char* sec ){
	NO* mynode; NO* mynode2;
	mynode = findNode( network->root, first );
	mynode2 = findNode( network->root, sec );
	if( mynode == NULL || mynode2 == NULL ) return ERRO;
	wrapAddNode( mynode->person->friends, newNode( mynode2->person ) );
	wrapAddNode( mynode2->person->friends, newNode( mynode->person ) );
	return !ERRO;
}
void askFriend( TREE* network ){
	char* str; char* str2;
	NO* mynode;
	str = (char*)malloc(sizeof(char)*10);
	str2 = (char*)malloc(sizeof(char)*10);
	printf("Digite o seu apelido:\n");
	scanf(" %[^\n]", str );
	printf("Quem voce deseja pedir em amizade?\n");
	scanf(" %[^\n]", str2 );
	mynode = findNode( network->root, str2 );
	push_back( str, mynode->person->asks );
	free( str2 );
	// nao damos free na primeira str pois ela sera "incorporada" a queue.
	printf("Seu pedido foi enviado com sucesso!\n\n");
}
void sendText( TREE* network ){
	char* name; char* autor; NO* mynode; NO* mynode2;
	name = (char*)malloc(sizeof(char)*TAMNICK);
	autor = (char*)malloc(sizeof(char)*TAMNICK);
	printf("Entre com o seu nome: ");
	scanf(" %[^\n]", autor );
	mynode = findNode( network->root, autor );
	if( mynode == NULL ) {
		printf("Nao existe ninguem com este apelido. Tente novamente!\n");
		free( name ); free( autor );
		return;
	}
	printf("Para quem voce quer mandar a mensagem?\n");
	scanf(" %[^\n]", name );
	mynode2 = findNode( mynode->person->friends->root, name );
	if( mynode2 != NULL ){
		TEXT* mytext = newText( autor );
		push( mytext, mynode2->person->talks );
		printf("Sua message foi enviada com sucesso!\n");
	} else{
		printf("Voce nao tem nenhum amigo com este apelido. Tente novamente!\n");
		free(autor);
	}
	// nao damos free na string autor pois esta sera "incorporada" a queue de conversas.
	free( name );
}
void readTexts( TREE* network ){
	char* str; NO* mynode;
	str = (char*)malloc(sizeof(char)*TAMNICK);
	printf("Digite o seu apelido:\n");
	scanf(" %[^\n]", str );
	printf("%s\n", str );
	mynode = findNode( network->root, str );
	if( mynode != NULL ) dumpStack( mynode->person->talks );
	else printf("Este apelido eh invalido. Tente novamente!\n");
	printf("\n");
	free( str );
}
void answerAsks( TREE* network ){
	char* str; NO* mynode; char op = 'T';
	str = (char*)malloc(sizeof(char)*10);
	printf("Digite o seu apelido:\n");
	scanf(" %[^\n]", str );
	printf("%s\n", str );
	mynode = findNode( network->root, str );
	if( mynode == NULL ){
		printf("apelido invalido. tente novamente!\n");
		free(str);
		return;
	}
	if( mynode->person->asks->size == 0 ){
		printf("Voce nao tem pedidos de amizade no momento.\n");
		free( str );
		return;
	}
	printf("Voce tem %d pedidos de amizade:\n\n", mynode->person->asks->size );
	while( mynode->person->asks->size && op != 'S' ){
		printf("%s quer ser seu amigo. ", front( mynode->person->asks ) );
		printf("Digite A para aceitar, R para recusar e S para sair.\n");
		scanf(" %c", &op );
		if( op == 'A' ){
			printf("Voce e %s agora sao amigs!\n\n", front( mynode->person->asks ) );
			addFriend( network, str, front( mynode->person->asks ) );
		}
		if( op != 'S' ) popQueue( mynode->person->asks );
	}
	free( str );
}
// esta funcao busca os amigos de amigos de um usuario e adciona-os em mytree
void sugest( NO* mynode, TREE* mytree ) {
	if( mynode == NULL ) return;
	wrapAddTree( mytree, mynode->person->friends );
	sugest( mynode->right, mytree );
	sugest( mynode->left, mytree );
}
int dumpSugest( NO* sugest, TREE* friends, char* nick ) {
	if( sugest == NULL ) return ERRO;
	int control = ERRO;
	if( strcmp( sugest->person->nick, nick ) && findNode( friends->root, sugest->person->nick ) == NULL ) {
		printf("  Nome: %s\n  Apelido: %s\n\n ", sugest->person->name, sugest->person->nick );
		control = 0;
	}
	if( dumpSugest( sugest->left, friends, nick ) != ERRO ) control = 0; 
	if( dumpSugest( sugest->right, friends, nick ) != ERRO ) control = 0;
	return control;
}
// a escolha do TAD tree para se armazenar as sugestoes de amizade foi unicamente devido
// a nescessidade de evitarmos repeticoes.
// Sabemos que a utilizacao de uma stack ou uma fica diminuiria a complexidade desta funcao
// de o( n*log n ) para o( n ) mas nao conseguimos pensar numa maneira adequada de 
// evitarmos as repeticoes.
void wrapSugest( TREE* network ){
	char* name; NO* mynode; TREE* mytree;
	name = (char*)malloc(sizeof(char)*TAMNICK);
	printf("Entre com seu apelido:\n");
	scanf(" %[^\n]", name );
	mynode = findNode( network->root, name );
	if( mynode == NULL ) {
		printf("Apelido invalido! Tente novamente!\n");
		free( name );
		return;
	}
	newTree( &mytree );
	sugest( mynode->person->friends->root, mytree );
	if( dumpSugest( mytree->root, mynode->person->friends, name ) == ERRO )
		printf("Nao ha sugestoes de amizade no momento.\n\n");
	free( name );
	wrapDestroyTree( &mytree );
	return;
}
