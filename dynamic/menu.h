#ifndef MENU_H
#define MENU_H

#include "stack.h"
#include "queue.h"
#include "tree.h"

#define TAMNICK 15

// supondo que a pessoa tenha aceitado o pedido de amizade
//int addFriend( TREE* network, char* first, char* sec );

// enviar um pedido de amizade
void askFriend( TREE* network );

// enviar message para outro usuario
void sendText( TREE* network );

// exibe na tela todas as mensagens de um usuario
void readTexts( TREE* network );

// avalia os pedidos de amizade de um usuario
void answerAsks( TREE* network );

// sugerir amigos.
// aqui, criamos uma arvore temporaria, adcionamos os amigos dos amigos
// do usuario. para cada usuario adcionado, conferimos se ja ha amizade entre eles.
// Caso nao haja, imprimimos seu nome.

void sugest( NO* mynode, TREE* mytree );

// retorna uma flag erro caso nao haja nenhuma sugestao de amizade
// imprime as sugestoes caso contrario.
int dumpSugest( NO* sugest, TREE* friends, char* nick );

// funcao responssavel por sugerir amigos. complexidade nlogn
void wrapSugest( TREE* network );

#endif
