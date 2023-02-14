#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "agenda.h"


int main(){
    int opcao = 1;
    while(opcao != 0){
        printf("Bem vindo a sua agenda digital, vc tem as seguintes opções:\n");
        printf("0-Sair do programa\n1-Agendar um novo compromisso\n2-Remover Compromisso\n3-Imprimir todos os seus compromissos atuais\n");
        scanf("%d", &opcao);
        switch (opcao){
            case 0:
                freeLista();
                printf("\nObrigado por utilizar o programa!\n Encerrando programa...\n");
                break;
            case 1:
                criaCompromisso();
                break;
            case 2:
                removeCompromisso();
                break;
            case 3:
                imprimeCompromissos();
                break;
            default:
                printf("Opção inválida, retornando ao menu de opções\n");
        }
    }
    return 0;
}