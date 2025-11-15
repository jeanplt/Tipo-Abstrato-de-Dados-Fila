#include <stdlib.h>
#include "fila.h"

/*
 * Implementacao das funcao da TAD pilha
 * Autor:
 *    Jean Pablo Lopes Teixeira
 *
 * Versao 1.0.0 de 03/10/2023
*/

struct fila *fila_cria ()
{
    struct fila *f = malloc(sizeof(struct fila));

    /* Testa se o malloc deu certo */ 
    if (f == NULL) 
        return NULL;

    /* Inicializa o inicio, fim e tamanho da fila para poder retorna-la */
    f->ini = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    
    return f;
}

void fila_destroi (struct fila **fila)
{
    /* Verifica se a fila ja foi criada */
    if (*fila == NULL) 
        return;

    /* Ponteiro para receber o dado do inicio da fila e ir desalocando
    sua memoria no 'For' ate 'atual' ser NULL */
    struct nodo *atual;

    for (atual = (*fila)->ini; atual != NULL; atual = (*fila)->ini) 
    {
        (*fila)->ini = atual->prox;
        free(atual);
    }
    
    /* Libera a memoria da pilha em si e depois faz o aterramento */
    free(*fila);
    *fila = NULL;
}

int enqueue (struct fila *fila, int dado)
{
    struct nodo *novoDado = malloc(sizeof(struct nodo));

    /* Testa se o malloc deu certo */
    if (novoDado == NULL) 
        return 0;

    /* Ponteiro recebe dado para ser inserido no final da fila */
    novoDado->chave = dado;
    novoDado->prox = NULL;

    struct nodo *final = fila->fim;

    /* Verifica se a fila esta vazia para inserir ou nao o dado no inicio da fila */
    if (fila_vazia(fila)) 
        fila->ini = novoDado;

    else
        final->prox = novoDado;

    /* Fila recebe o novo dado e seu tamanho eh aumentado em 1 */
    fila->fim = novoDado;
    fila->tamanho++;

    return 1;
}

int dequeue (struct fila *fila, int *dado)
{
    /* Verifica se a pilha esta vazia */
    if (fila_vazia(fila))
        return 0;
    
    /* Ponteiro para receber elemento do inicio da fila */
    struct nodo *inicio = fila->ini;

    *dado = inicio->chave;
    fila->ini = inicio->prox;
    
    /* Verifica se o inicio da fila ficou vazio, para declarar o fim 
    dela vazio tambem */
    if (fila->ini == NULL) 
        fila->fim = NULL;

    free(inicio); 

    fila->tamanho--;

    return 1;
}

int fila_tamanho (struct fila *fila)
{
    return fila->tamanho;
}

int fila_vazia (struct fila *fila)
{
    return (fila->ini == NULL);
}