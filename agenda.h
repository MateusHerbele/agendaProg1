#ifndef AGENDA_H  
#define AGENDA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct compromisso {
    char* evento;
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
};

//esse nome para o Nó não ficou muito bom
struct compromissoNo {
    struct compromisso* id;
    struct compromissoNo* proximo;
};

void verificaMallocNo(struct compromissoNo* alocacao);

void verificaMallocCompromisso(struct compromisso* alocacao);

struct compromisso* criaCompromisso();

void adicionaCompromisso(struct compromisso* novoCompromisso);

void ordenaCompromissos();

void imprimeCompromissos();

void removeCompromisso();

int habilitaCompromisso(struct compromisso* novoCompromisso);

void freeLista();


#endif//AGENDA_H