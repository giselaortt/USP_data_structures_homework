#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "menu.h"


int main( void ){
    int userInput;
    TREE* network;
    newTree( &network );
    char c;
    do{
    	printf("Caro usuario, suas opcoes sao:\n\n");
        printf("1) Cadastrar um usuario\n");
        printf("2) Listar usuarios cadastrados e suas informacoes\n");
        printf("3) Pedir para ser parceiro de um usuario\n");
        printf("4) Avaliar pedidos de parceria\n");
        printf("5) Enviar mensagem para um parceiro\n");
        printf("6) Ver mensagens recebidas\n");
        printf("7) Ver sugestoes de novas parcerias\n");
        printf("8) Reinicializar sistema\n");
        printf("9) Fechar o programa\n\n");
        printf("O que deseja fazer?\n");
        scanf("%d", &userInput );
        scanf("%c", &c ); // lemos esse char apenas para limpar o buffer
        printf("\33[H\33[2J"); // limpar a tela no linux
        switch(userInput){
	        case 1:
	            newAcount( network ); 
	            break;

	        case 2:
	            dumpNetwork( network->root );
	            break;

	        case 3:
	            askFriend( network ); 
	            break;

	        case 4:
	            answerAsks( network );
	            break;

	        case 5:
				sendText( network );
	            break;

	        case 6:
	        	readTexts( network );
	            break;

	        case 7:
	            wrapSugest( network );
	            break;

	        case 8:
	            clearNetwork( &(network->root) ); 
	            break;

	        case 9:
	        	printf("Obrigada!\n");
	        	break;

	        default:
	            printf("Opcao invalida.\n\n");
        }

    }while(userInput!=9);
    destroyNetwork( &network );
    printf("Ate a proxima!\n");
    return 0;
