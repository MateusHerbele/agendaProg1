#include "agenda.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct compromissoNo* head = NULL;

//Verifica se foi possível alocar memória
void verificaMallocNo(struct compromissoNo* alocacao){
    if(alocacao == NULL){
        printf("Erro de alocação de memória, o programa será terminado\n");
        exit(1);
    }
}
void verificaMallocCompromisso(struct compromisso* alocacao){
    if(alocacao == NULL){
        printf("Erro de alocação de memória, o programa será terminado\n");
        exit(1);
    }
}


//Cria um compromisso
struct compromisso* criaCompromisso(){

    struct compromisso* novoCompromisso = (struct compromisso*)malloc(sizeof(struct compromisso));
    verificaMallocCompromisso(novoCompromisso);
    size_t tamanho = 0; /*Tipo de variável adequado para se trabalhar usando o getline*/
    
    printf("Descrição do evento: ");
    getchar();/* forma que eu encontrei para q o fgets não recebecesse o /n do scanf anterior e pulasse a ação dele*/ 
    getline(&novoCompromisso->evento, &tamanho, stdin);

    printf("Coloque a data do evento (dd mm ano):\n");
    scanf("%d %d %d", &novoCompromisso->dia, &novoCompromisso->mes, &novoCompromisso->ano);
    printf("Que horas acontecerá o evento? (horas min): \n");
    scanf("%d %d", &novoCompromisso->hora, &novoCompromisso->min);
    
    if(habilitaCompromisso(novoCompromisso)){
        adicionaCompromisso(novoCompromisso);
        return novoCompromisso;
    }
    
}

//Adiciona a lista
void adicionaCompromisso(struct compromisso* novoCompromisso) {

    struct compromissoNo* novoNo = (struct compromissoNo*) malloc(sizeof(struct compromissoNo));
    verificaMallocNo(novoNo);
    novoNo->id = novoCompromisso;
    novoNo->proximo = NULL;

    if (head == NULL) {
        head = novoNo;
    } else {
        struct compromissoNo* atual = head;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
    ordenaCompromissos();
}
//Ordena a lista
void ordenaCompromissos() {

    struct compromissoNo *atual;
    int trocas;//Serve pra checar se houve trocas feito no while interno, assim se for 0 sabe q está ordenado

    if (head == NULL){
        return;
    }

    while (1) {
        trocas = 0;
        atual = head;
        while (atual->proximo != NULL) {
            if ((atual->id->ano > atual->proximo->id->ano) || (atual->id->ano == atual->proximo->id->ano && atual->id->mes > atual->proximo->id->mes) || (atual->id->ano == atual->proximo->id->ano && atual->id->mes == atual->proximo->id->mes && atual->id->dia > atual->proximo->id->dia) ||(atual->id->ano == atual->proximo->id->ano && atual->id->mes == atual->proximo->id->mes && atual->id->dia == atual->proximo->id->dia && atual->id->hora > atual->proximo->id->hora)) {
            /*Esse if compara todas as situações que devem ser ordenadas,
            mas como existe a ordem ano>mes>dia>horário ent pra cada coisa igual ela tem q ser
            recomprovada para o outro, o que deixou com essa quantidade enorme de condições
            */
                struct compromisso* temp = atual->id;

                atual->id = atual->proximo->id;
                atual->proximo->id = temp;
                trocas = 1;
            }
            atual = atual->proximo;
        }
        if (trocas == 0){
            return;
        } 
    }
}

//Printa toda a lista
void imprimeCompromissos() {
    if(head == NULL) {
    printf("Não há compromissos cadastrados ainda\n");
} else {
    struct compromissoNo* atual = head;
    while (atual != NULL) {
        printf("Evento: %s\n", atual->id->evento);
        printf("Data: %d/%d/%d\n", atual->id->dia, atual->id->mes, atual->id->ano);
        printf("Horário: %d:%d\n\n", atual->id->hora, atual->id->min);
        atual = atual->proximo;
    }
}
}
//Remove um compromisso
void removeCompromisso() {
    char* conteudo = NULL;
    size_t tamanho = 0; /*Tipo de variável adequado para se trabalhar usando o getline*/

    if(head == NULL) {
    printf("Não há compromissos cadastrados ainda\n");
} else {
    printf("\nDigite a descrição do evento para apagá-lo:\n");
    
    getchar();

    ssize_t copiaEvento = getline(&conteudo, &tamanho, stdin); /* ssize_t é a versão signed da size_t, 
    caso não seja retornado nada vai devolver -1*/
    if (copiaEvento == -1) {
        printf("Evento inválido");
        return;
    }
    struct compromissoNo* atual = head;
    struct compromissoNo* anterior = NULL;
    while (atual != NULL) {
        if (strcmp(atual->id->evento, conteudo) == 0) {
            if (anterior == NULL) {
                head = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            //Libera a memória alocada
            free(atual->id->evento);
            free(atual->id);
            free(atual);
            free(conteudo);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Compromisso não encontrado\n");
}
}
//Impedir que seja marcado um compromisso no mesmoa ano, mês e hora
//Impedir que seja marcado no dia 29 de fevereiro em anos !bissextos
//Impedir marcar valores inválidos de dia, ano, horas e minutos

int habilitaCompromisso(struct compromisso* novoCompromisso) {

    struct compromissoNo* atual = head;

    int ano = novoCompromisso->ano;
    int mes = novoCompromisso->mes;
    int dia = novoCompromisso->dia;
    int hora = novoCompromisso->hora;
    int min = novoCompromisso->min;

    if(strlen(novoCompromisso->evento) == 1){
        printf("\nO Progama não admite eventos sem nome\n");
        return 0;
    }

    if(ano < 2023){
        printf("\nNão é possível marcar eventos no passado");
        return 0;
    }
    if(mes < 1 || mes > 12){
        printf("\nSomentes meses de 1 a 12 são válidos\n");
        return 0;
    }
    if(dia < 0 || dia > 31 || (dia > 28 && mes == 2 && ano % 4 != 0) || (dia > 29 && mes == 2 && ano % 4 == 0) || (dia > 30 && (mes == 4 || mes == 6 || mes == 9 || mes == 11))){
        printf("\nDia inexistente\n");
        return 0;
    }
    if(hora < 0 || hora > 23){
        printf("\nHora inválida\n");
        return 0;
    }
    if(min < 0|| min > 59){
        printf("\nMinutos inválidos\n");
        return 0;
    }

    while (atual != NULL) {
        if (atual->id->ano == novoCompromisso->ano && atual->id->dia == novoCompromisso->dia && atual->id->hora == novoCompromisso->hora) {
            printf("\nNão é possível agendar mais que um compromisso no mesmo ano, dia e hora\n");
            return 0;
        }
        atual = atual->proximo;
    }
    return 1;
}
//Free em tudo
void freeLista() {
    struct compromissoNo* temp = head;
    while(temp != NULL) {
        head = temp;
        temp = temp->proximo;
        free(head);
    }
}

