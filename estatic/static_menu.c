
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "static_stack.h"
#include "static_queue.h"
#include "static_tree.h"
#include "static_menu.h"

#define TAMNICK 10
#define ERRO 1

void askFriend( TREE* rede ){
	char str[TAMNICK]; char str2[TAMNICK];
	NO* mynode;
	printf("Digite o seu apelido:\n");
	scanf(" %[^\n]", str );
	printf("Quem voce deseja pedir em amizade?\n");
	scanf(" %[^\n]", str2 );
	mynode = wrapFindUser(rede,str2 );
	if( mynode == NULL ) {
		printf("Nao existe ninguem com este apelido. Tente novamente!\n");
		return;
	}
	pushQueue(&(mynode->asks),str);
	printf("Seu pedido foi enviado com sucesso!\n\n");
}

void sendText( TREE* rede ){
    int erro=0;
	char name[TAMNICK]; char autor[TAMNICK]; NO* mynode; NO* mynode2;
	printf("Entre com o seu nome: ");
	scanf(" %[^\n]", autor );
	mynode = wrapFindUser(rede,autor );
	if( mynode == NULL ) {
		printf("Nao existe ninguem com este apelido. Tente novamente!\n");
		return;
	}
	printf("Para quem voce quer mandar a mensagem?\n");
	scanf(" %[^\n]", name );
	mynode2 = findFriend(mynode, name );
	if( mynode2 != NULL ){
		char mytext[144];
		printf("Digite a mensagem:\n");
        scanf(" %[^\n]", mytext );
		push(&(mynode2->texts), autor, mytext,&erro);
		printf("Sua message foi enviada com sucesso!\n");
	} else printf("Voce nao tem nenhum amigo com este apelido. Tente novamente!\n");
}

void readTexts( TREE* rede ){
    int erro=0;
	char str[TAMNICK]; NO* mynode;
	printf("Digite o seu apelido:\n");
	scanf(" %[^\n]", str );
	printf("%s\n", str );
	mynode = wrapFindUser(rede,str );
	if( mynode != NULL ) dumpStack(&(mynode->texts),&erro);
	else printf("Este apelido eh invalido. Tente novamente!\n");
	printf("\n");
}

void answerAsks( TREE* rede ){
	char str[TAMNICK]; NO* mynode; char op = 'T';
	printf("Digite o seu apelido:\n");
	scanf(" %[^\n]", str );
	printf("%s\n", str );
	mynode = wrapFindUser( rede, str );
	if( mynode == NULL ){
		printf("apelido invalido. tente novamente!\n");
		return;
	}
	if( sizeQueue(mynode->asks) == 0 ){
		printf("Voce nao tem pedidos de amizade no momento.\n");
		return;
	}
	printf("Voce tem %d pedidos de amizade:\n\n", sizeQueue(mynode->asks) );
	while( sizeQueue(mynode->asks) && op != 'S' ){
		printf("%s quer ser seu amigo. ", front( mynode->asks ) );
		printf("Digite A para aceitar, R para recusar e S para sair.\n");
		scanf(" %c", &op );
		if( op == 'A' ){
			printf("Voce e %s agora sao amigs!\n\n", front( mynode->asks ) );
			addFriend( rede, str, front( mynode->asks ) );
		}
		if( op != 'S' ) popQueue(&(mynode->asks));
	}
}

// esta funcao busca os amigos de amigos de um usuario e adciona-os em mytree
void wrapSugest( TREE* mytree ) {
    int i,j;
    TREE* mynewtree;
    char nome[TAMNICK];
    NO* mynode;
    printf("Digite seu apelido:\n");
	scanf(" %[^\n]", nome );
    wrapFindUser(mytree,nome);
    for(i=0;i<mynode->numfriends;i++){
        for(j=0;j<mynode->friends[i]->numfriends;j++){
            wrapAddUser(mynewtree,mynode->friends[i]->friends[j]->name,mynode->friends[i]->friends[j]->nick);
        }
    }
    if( dumpSugest(mynode->friends,mynewtree,mynewtree->root) )
        printf("Nao ha sugestoes de amizade no momento!\n");
    else printf("\n");
}

int dumpSugest( NO* person, TREE* sugest, int node ) {
    int control;
    NO* myno = findFriend( person, sugest->users[node].nick);
    if( myno == NULL ){
        printf("%s ", sugest->users[node].nick );
        control++;
    }
	control += dumpSugest( person, sugest, sugest->users[node].left );
	control += dumpSugest( person, sugest, sugest->users[node].right );
	return control;
}

// a escolha do TAD tree para se armazenar as sugestoes de amizade foi unicamente devido
// a nescessidade de evitarmos repeticoes.
// Sabemos que a utilizacao de uma stack ou uma fica diminuiria a complexidade desta funcao
// de o( n*log n ) para o( n ) mas nao conseguimos pensar numa maneira adequada de
// evitarmos as repeticoes.

//mostra as opções ao usuário
void Options(){
    printf("Caro usuario, suas opcoes sao:\n");
    printf("1) Cadastrar um usuario\n");
    printf("2) Listar usuarios cadastrados e suas informacoes\n");
    printf("3) pedir para ser parceiro de um usuario\n");
    printf("4) avaliar lista de pedidos de parceria\n");
    printf("5) enviar mensagem para um parceiro\n");
    printf("6) ver mensagens recebidas\n");
    printf("7) sugerir novas parcerias\n");
    printf("8) reinicializar sistema\n");
    printf("9) fechar o programa\n\n");
    printf("O que deseja fazer?\nResposta: ");
}


//função chamada após o pedido de amizade ser aceito
void addFriend(TREE* rede, char* user1, char* user2){
    NO* myno1;
    NO* myno2;
    myno1 = wrapFindUser(rede,user1);
    myno2 = wrapFindUser(rede,user2);
    myno1->friends[myno1->numfriends++] = myno2;
    myno2->friends[myno2->numfriends++] = myno1;
}

void newAccount(TREE* mytree){
    char nome[TAMNAME], apelido[TAMNICK];
    printf("Digite seu nome:\n");
	scanf(" %[^\n]", nome );
	printf("Digite seu apelido:\n");
	scanf(" %[^\n]", apelido );
	if(wrapAddUser(mytree,nome,apelido) == ERRO){
        printf("Ocorreu um erro. Nao foi possivel criar sua conta.\n");
	}
	else{
        printf("Sua conta foi criada com sucesso!\n");
	}
}
