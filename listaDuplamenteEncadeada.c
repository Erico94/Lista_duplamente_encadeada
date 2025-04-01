#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[30];
    float nota;
    int turma;
} Aluno;

struct Nodo
{
    Aluno dado;
    struct Nodo *ant;
    struct Nodo *prox;
};
typedef struct Nodo nodo;

struct Descritor
{
    int quantidade;
    nodo *primeiro;
    nodo *ultimo;
};
typedef struct Descritor descritor;

void InicializarLista(nodo *, descritor *);
int VerificaSeEstaVazia(descritor *);
Aluno AcessarPrimeiroELemento(descritor *);
Aluno AcessarUltimoELemento(descritor *);
void InserirInicio(nodo *, descritor *, Aluno *);
void InserirNoFinal(nodo *, descritor *, Aluno *);
void ExcluirDoInicio(nodo *, descritor *);
void ExcluirDoFinal(descritor *);
void ExcluirListaInteira(nodo *, descritor *);
void ImprimeTodosOsElementos(nodo *, descritor *, char);

int main()
{
    Aluno aluno;
    nodo *L = (nodo *)malloc(sizeof(nodo));
    descritor *D = (descritor *)malloc(sizeof(descritor));
    InicializarLista(L, D);

    free(L);
    free(D);
    return 1;
}

void InicializarLista(nodo *L, descritor *D)
{
    L->ant = NULL;
    L->prox = NULL;

    D->primeiro = NULL;
    D->ultimo = NULL;
    D->quantidade = 0;
}
int VerificaSeEstaVazia(descritor *D)
{
    if (D->quantidade == 0)
    {
        return 1;
    }
    return 0;
}
Aluno AcessarPrimeiroELemento(descritor *D)
{
    nodo *no = D->primeiro;
    return no->dado;
}
Aluno AcessarUltimoELemento(descritor *D)
{
    nodo *no = D->ultimo;
    return no->dado;
}
void InserirInicio(nodo *L, descritor *D, Aluno *dado)
{
    nodo *novoNo = (nodo *)malloc(sizeof(nodo));
    if (novoNo == NULL)
    {
        printf("Erro ao alocar memoria");
        exit(1);
    }
    strcpy(novoNo->dado.nome, dado->nome);
    novoNo->dado.turma = dado->turma;
    novoNo->dado.nota = dado->nota;
    if (VerificaSeEstaVazia(D))
    {
        L->prox = novoNo;
        novoNo->prox = NULL;
        D->ultimo = novoNo;
    }
    else
    {
        nodo *antigoPrimeiro = L->prox;
        L->prox = novoNo;
        novoNo->prox = antigoPrimeiro;
        antigoPrimeiro->ant = novoNo;
    }
    D->quantidade++;
    D->primeiro = novoNo;
    novoNo->ant = NULL;
}
void InserirNoFinal(nodo *L, descritor *D, Aluno *dado)
{
    nodo *novo = (nodo *)malloc(sizeof(nodo));
    strcpy(novo->dado.nome, dado->nome);
    novo->dado.nota = dado->nota;
    novo->dado.turma = dado->turma;
    if (VerificaSeEstaVazia(D))
    {
        L->prox = novo;
        novo->ant = NULL;
        D->primeiro = novo;
    }
    else
    {
        nodo *antigoUltimo = D->ultimo;
        novo->ant = antigoUltimo;
        D->ultimo->prox = novo;
    }
    novo->prox = NULL;
    D->ultimo = novo;
    D->quantidade++;
}
void ExcluirDoInicio(nodo *L, descritor *D)
{
    if (VerificaSeEstaVazia(D))
    {
        printf("A lista esta vazia, impossivel excluir.");
        return;
    }
    else
    {
        nodo *prim = L->prox;
        nodo *seg = prim->prox;
        L->prox = seg;
        seg->ant = NULL;
        D->primeiro = seg;
        free(prim);
        D->quantidade--;
    }
}
void ExcluirDoFinal(descritor *D)
{
    nodo *ultimo = D->ultimo;
    nodo *penultimo = ultimo->ant;
    penultimo->prox = NULL;
    D->ultimo = penultimo;
    D->quantidade--;
    free(ultimo);
}
void ExcluirListaInteira(nodo *L, descritor *D)
{
    if (!VerificaSeEstaVazia(D))
    {
        nodo *proxNodo;
        nodo *atual = L->prox;
        while (atual != NULL)
        {
            proxNodo = atual->prox;
            free(atual);
            atual = proxNodo;
            D->quantidade--;
        }
    }
}
void ImprimeTodosOsElementos(nodo *L, descritor *D, char ordem)
{
    if (VerificaSeEstaVazia(D))
    {
        printf("A lista esta vazia.");
        return;
    };
    if (ordem == 'c')
    {
        nodo *temp = L->prox;
        printf("%-10s %-6s %-5s", "Nome", "Nota", "Turma");
        while (temp != NULL)
        {
            printf("%-10s %-6.1f %-4d", temp->dado.nome, temp->dado.nota, temp->dado.turma);
            temp = temp->prox;
        };
    }else if(ordem =='d'){
        nodo *temp = D->ultimo;
        printf("%-10s %-6s %-5s", "Nome", "Nota", "Turma");
        while (temp != NULL)
        {
            printf("%-10s %-6.1f %-4d", temp->dado.nome, temp->dado.nota, temp->dado.turma);
            temp = temp->ant;
        };
    }
    printf("\n\n");
}