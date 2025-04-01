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

void SeedAlunos(nodo *, descritor *);
void InicializarLista(nodo *, descritor *);
int VerificaSeEstaVazia(descritor *);
Aluno AcessarPrimeiroELemento(descritor *);
Aluno AcessarUltimoELemento(descritor *);
void InserirInicio(nodo *, descritor *, Aluno *);
void InserirNoMeio(nodo *, descritor *, Aluno);
void InserirNoFinal(nodo *, descritor *, Aluno *);
void ExcluirDoInicio(nodo *, descritor *);
void ExcluirDoFinal(descritor *);
void ExcluirListaInteira(nodo *, descritor *);
void ImprimeTodosOsElementos(nodo *, descritor *, char);
void cadastrar_aluno(nodo *, descritor *, char);

int main()
{
    nodo *L = (nodo *)malloc(sizeof(nodo));
    descritor *D = (descritor *)malloc(sizeof(descritor));
    InicializarLista(L, D);
    SeedAlunos(L, D);
    int op;

    while (1)
    {
        Aluno aluno;
        aluno.nota = 6;
        aluno.turma = 54;
        strcpy(aluno.nome, "Bruno");

        printf("\n1-Inserir no inicio;");
        printf("\n2-Inserir no final;");
        printf("\n3-Excluir do inicio;");
        printf("\n4-Excluir do final;");
        printf("\n5-Excluir lista inteira;");
        printf("\n6-Mostrar lista em ordem crescente;");
        printf("\n7-Mostrar lista em ordem decrescente;");
        printf("\n8-Inserir elemento em posicao intermediaria.");
        printf("\n9-Sair");

        printf("\nDigite a opcao desejada:");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            cadastrar_aluno(L, D, 'i');
            break;
        case 2:
            cadastrar_aluno(L, D, 'f');
            break;
        case 3:
            ExcluirDoInicio(L, D);
            break;
        case 4:
            ExcluirDoFinal(D);
            break;
        case 5:
            ExcluirListaInteira(L, D);
            break;
        case 6:
            ImprimeTodosOsElementos(L, D, 'c');
            break;
        case 7:
            ImprimeTodosOsElementos(L, D, 'd');
            break;
        case 8:
            InserirNoMeio(L, D, aluno);
            break;
        case 9:
            exit(0);
        default:
            printf("\nOpcao invalida.");
        }
    }

    free(L);
    free(D);
    return 1;
}

void SeedAlunos(nodo *L, descritor *D)
{
    Aluno alunos[] = {
        {"Alice", 8, 101},
        {"Bruno", 7, 102},
        {"Carla", 9, 101},
        {"Daniel", 6, 103},
        {"Elisa", 7, 102}};
    int quantidade = sizeof(alunos) / sizeof(alunos[0]);

    for (int i = 0; i < quantidade; i++)
    {
        InserirNoFinal(L, D, &alunos[i]);
    }
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
void InserirNoMeio(nodo *L, descritor *D, Aluno dado)
{
    nodo *novoNo = (nodo *)malloc(sizeof(nodo));
    strcpy(novoNo->dado.nome, dado.nome);
    novoNo->dado.nota = dado.nota;
    novoNo->dado.turma = dado.turma;

    if (VerificaSeEstaVazia(D))
    {
        L->prox = novoNo;
        novoNo->ant = NULL;
        novoNo->prox = NULL;
        D->primeiro = novoNo;
        D->ultimo = novoNo;
    }
    else
    {
        nodo *temp, *ant;
        nodo *no = L->prox;
        while (no != NULL)
        {
            if (strcmp(no->dado.nome, dado.nome) == 0)
            {
                ant = no;
                temp = no->prox;
                novoNo->ant = ant;
                novoNo->prox = temp;
                no->prox = novoNo;
                temp->ant = novoNo;
                break;
            }
            no = no->prox;
        }
    }
    D->quantidade++;
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
            printf("\n%-10s %-6.1f %-4d", temp->dado.nome, temp->dado.nota, temp->dado.turma);
            temp = temp->prox;
        };
    }
    else if (ordem == 'd')
    {
        nodo *temp = D->ultimo;
        printf("%-10s %-6s %-5s", "Nome", "Nota", "Turma");
        while (temp != NULL)
        {
            printf("\n%-10s %-6.1f %-4d", temp->dado.nome, temp->dado.nota, temp->dado.turma);
            temp = temp->ant;
        };
    }
    printf("\n\n");
}
void cadastrar_aluno(nodo *L, descritor *D, char local)
{
    Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));
    printf("\nDados do aluno:");
    getchar();
    printf("\nNome:");
    scanf("%[^\n]s", novoAluno->nome);
    printf("\nNota:");
    scanf("%f", &novoAluno->nota);
    printf("\nTurma (numero):");
    scanf("%d", &novoAluno->turma);
    if (local == 'i')
    {
        InserirInicio(L, D, novoAluno);
    }
    else if (local == 'f')
    {
        InserirNoFinal(L, D, novoAluno);
    }
    return;
}