#ifndef _STATIC_MENU_H
#define _STATIC_MENU_H

#include "static_stack.h"
#include "static_queue.h"
#include "static_tree.h"

#define TAMNICK 10

// supondo que a pessoa tenha aceitado o pedido de amizade
//int addFriend( TREE* rede, char* first, char* sec );

// enviar um pedido de amizade
void askFriend( TREE* rede );

// enviar message para outro usuario
void sendText( TREE* rede );

// exibe na tela todas as mensagens de um usuario
void readTexts( TREE* rede );

// avalia os pedidos de amizade de um usuario
void answerAsks( TREE* rede );

// sugerir amigos.
// aqui, criamos uma arvore temporaria, adcionamos os amigos dos amigos
// do usuario. para cada usuario adcionado, conferimos se ja ha amizade entre eles.
// Caso nao haja, imprimimos seu nome.

void wrapSugest( TREE* mytree );

// retorna uma flag erro caso nao haja nenhuma sugestao de amizade
// imprime as sugestoes caso contrario.
int dumpSugest( NO* person, TREE* sugest, int node );

//imprime para o usuário suas opões
void Options();

//função chamada após ser aceito o pedido de amizade
void addFriend(TREE* rede, char* user1, char* user2);

//cria nova conta e armazena na árvore
void newAccount(TREE* mytree);

#endif

