#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvRB_Album 
{
    char titulo[50];
    int anoLancamento;
    int numMusicas;
    int cor;
    struct arvRB_Album *esq, *dir;
} arvRB_Album;

typedef struct arvRB_Artista 
{
    char nome[50];
    char estilo[50];
    int numAlbuns;
    int cor;
    arvRB_Album *albuns;
    struct arvRB_Artista *esq, *dir;
} arvRB_Artista;

// RED == 1 e BLACK == 0
//FUNCOES REFERENTES AOS ARTISTAS
struct arvRB_Artista *criaNo_Artista(char *nome, char *estilo);
int insere_ArvARB_Artista(struct arvRB_Artista **raiz, char *nome, char *estilo);
struct arvRB_Artista *inserirNO_Artista(struct arvRB_Artista *raiz, char *nome, char *estilo, int *resp);
struct arvRB_Artista *rotacionaEsquerda_Artista(struct arvRB_Artista *A);
struct arvRB_Artista *rotacionaDireita_Artista(struct arvRB_Artista *A);
void trocaCor_Artista(struct arvRB_Artista *raiz);
void imprimeArvore_Artista(struct arvRB_Artista *raiz);
struct arvRB_Artista *buscaArtista(struct arvRB_Artista *raiz, const char *nome);


//FUNCOES REFERENTES AO ALBUM 
struct arvRB_Album *criaNo_Album(char *titulo, int anoLancamento);
int insere_ArvARB_Album(struct arvRB_Album **raiz, char *titulo, int anoLancamento);
struct arvRB_Album *inserirNO_Album(struct arvRB_Album *raiz, char *titulo, int anoLancamento, int *resp);
struct arvRB_Album *rotacionaEsquerda_Album(struct arvRB_Album *A);
struct arvRB_Album *rotacionaDireita_Album(struct arvRB_Album *A);
void trocaCor_Album(struct arvRB_Album *raiz);
void imprimeArvore_Album(struct arvRB_Album *raiz);
struct arvRB_Album *buscaAlbum(struct arvRB_Album *raiz, const char *titulo);
void liberaArvore_Album(struct arvRB_Album **raiz);

int main() {
    struct arvRB_Artista *raiz = NULL;

    // Inserir artistas na árvore
    // struct arvRB_Artista artista1 = {"Adele", "Pop", 0, 1, NULL, NULL, NULL};
    // struct arvRB_Artista artista2 = {"Ed Sheeran", "Pop", 0, 1, NULL, NULL, NULL};
    // struct arvRB_Artista artista3 = {"Queen", "Rock", 0, 1, NULL, NULL, NULL};

    insere_ArvARB_Artista(&raiz, "Adele", "Pop");
    raiz->cor = 0; // Raiz sempre deve ser preta

    insere_ArvARB_Artista(&raiz, "Ed Sheeran", "Pop");
    insere_ArvARB_Artista(&raiz, "Queen", "Rock");

    // Imprime a árvore em ordem crescente
    printf("Árvore em ordem crescente:\n");
    imprimeArvore_Artista(raiz);
    printf("\n");

    const char *nomeBusca = "Adele";
    struct arvRB_Artista *artistaEncontrado = buscaArtista(raiz, nomeBusca);

    if (artistaEncontrado != NULL) {
        printf("O artista %s foi encontrado na árvore.\n", nomeBusca);
    } else {
        printf("O artista %s não foi encontrado na árvore.\n", nomeBusca);
    }

    insere_ArvARB_Album(&(artistaEncontrado)->albuns, "Album1", 2013);
    insere_ArvARB_Album(&(artistaEncontrado)->albuns, "Album2", 2013);
    insere_ArvARB_Album(&(artistaEncontrado)->albuns, "Album3", 2015);

    imprimeArvore_Album(artistaEncontrado->albuns);

    liberaArvore_Album(&(artistaEncontrado->albuns));

    return 0;
}


struct arvRB_Artista *criaNo_Artista(char *nome, char *estilo) {
    arvRB_Artista *novo_no = (arvRB_Artista *)malloc(sizeof(arvRB_Artista)); // Aloca memória para o novo nó.

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }


    strncpy(novo_no->nome, nome, sizeof(novo_no->nome)); 
    strncpy(novo_no->estilo, estilo, sizeof(novo_no->estilo)); 
    novo_no->numAlbuns = 0;
    novo_no->cor = 1;
    novo_no->albuns = NULL;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

int insere_ArvARB_Artista(struct arvRB_Artista **raiz, char *nome, char *estilo) {
    int resp = 1;
    *raiz = inserirNO_Artista(*raiz, nome, estilo, &resp);
    if (*raiz != NULL)
        (*raiz)->cor = 0;

    return resp;
}

struct arvRB_Artista *inserirNO_Artista(struct arvRB_Artista *raiz, char *nome, char *estilo, int *resp) {
    if (raiz == NULL) {
        struct arvRB_Artista *novo;
        novo = criaNo_Artista(nome, estilo);
        if (novo == NULL){
            *resp = 0;
            return NULL;
        }
        return novo;
    }

    int comparacao = strcmp(nome, raiz->nome);

    if (comparacao == 0) {
        *resp = 0; // Artista já existe na árvore
        return raiz;
    } else if (comparacao < 0) {
        raiz->esq = inserirNO_Artista(raiz->esq, nome, estilo, resp);
    } else {
        raiz->dir = inserirNO_Artista(raiz->dir, nome, estilo, resp);
    }

    if (raiz->dir != NULL && raiz->dir->cor == 1 && (raiz->esq == NULL || raiz->esq->cor == 0))
        raiz = rotacionaEsquerda_Artista(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == 1 && raiz->esq->esq != NULL && raiz->esq->esq->cor == 1)
        raiz = rotacionaDireita_Artista(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == 1 && raiz->dir != NULL && raiz->dir->cor == 1)
        trocaCor_Artista(raiz);

    return raiz;
}



struct arvRB_Artista *rotacionaEsquerda_Artista(struct arvRB_Artista *A) {
    struct arvRB_Artista *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}

struct arvRB_Artista *rotacionaDireita_Artista(struct arvRB_Artista *A) {
    struct arvRB_Artista *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}

void trocaCor_Artista(struct arvRB_Artista *raiz) {
    raiz->cor = !raiz->cor;

    if (raiz->esq != NULL)
        raiz->esq->cor = !raiz->esq->cor;
    if (raiz->dir != NULL)
        raiz->dir->cor = !raiz->dir->cor;
}


void imprimeArvore_Artista(struct arvRB_Artista *raiz) {
    if (raiz != NULL) {
        imprimeArvore_Artista(raiz->esq);
        printf("Nome: %s, Estilo: %s, Número de Álbuns: %d\n", raiz->nome, raiz->estilo, raiz->numAlbuns);
        imprimeArvore_Artista(raiz->dir);
    }
}

// Função de busca de artista na árvore
struct arvRB_Artista *buscaArtista(struct arvRB_Artista *raiz, const char *nome) {
    if (raiz == NULL) {
        return NULL; // Árvore vazia ou artista não encontrado
    }

    int comparacao = strcmp(nome, raiz->nome);

    if (comparacao == 0) {
        return raiz; // Artista encontrado
    } else if (comparacao < 0) {
        return buscaArtista(raiz->esq, nome); // Busca na subárvore esquerda
    } else {
        return buscaArtista(raiz->dir, nome); // Busca na subárvore direita
    }
}

struct arvRB_Album *criaNo_Album(char *titulo, int anoLancamento) {
    arvRB_Album *novo_no = (arvRB_Album *)malloc(sizeof(arvRB_Album)); // Aloca memória para o novo nó.

    if (novo_no == NULL) {
        printf("Erro na alocação de memória.\n");
        exit(1);
    }


    strncpy(novo_no->titulo, titulo, sizeof(novo_no->titulo)); 
    novo_no->anoLancamento = anoLancamento;
    novo_no->numMusicas = 0;
    novo_no->cor = 1;
    //novo_no->albuns = NULL;
    novo_no->esq = NULL;
    novo_no->dir = NULL;

    return novo_no;
}

int insere_ArvARB_Album(struct arvRB_Album **raiz, char *titulo, int anoLancamento) {
    int resp = 1;
    *raiz = inserirNO_Album(*raiz, titulo, anoLancamento, &resp);
    if (*raiz != NULL)
        (*raiz)->cor = 0;

    return resp;
}

struct arvRB_Album *inserirNO_Album(struct arvRB_Album *raiz, char *titulo, int anoLancamento, int *resp) {
    
    if (raiz == NULL) {
        struct arvRB_Album *novo;
        novo = criaNo_Album(titulo, anoLancamento);
        if (novo == NULL){
            *resp = 0;
            return NULL;
        }
        return novo;
    }

    int comparacao = strcmp(titulo, raiz->titulo);

    if (comparacao == 0) {
        *resp = 0; // Artista já existe na árvore
        return raiz;
    } else if (comparacao < 0) {
        raiz->esq = inserirNO_Album(raiz->esq, titulo, anoLancamento, resp);
    } else {
        raiz->dir = inserirNO_Album(raiz->dir, titulo, anoLancamento, resp);
    }

    if (raiz->dir != NULL && raiz->dir->cor == 1 && (raiz->esq == NULL || raiz->esq->cor == 0))
        raiz = rotacionaEsquerda_Album(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == 1 && raiz->esq->esq != NULL && raiz->esq->esq->cor == 1)
        raiz = rotacionaDireita_Album(raiz);

    if (raiz->esq != NULL && raiz->esq->cor == 1 && raiz->dir != NULL && raiz->dir->cor == 1)
        trocaCor_Album(raiz);

    return raiz;
}



struct arvRB_Album *rotacionaEsquerda_Album(struct arvRB_Album *A) {
    struct arvRB_Album *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}

struct arvRB_Album *rotacionaDireita_Album(struct arvRB_Album *A) {
    struct arvRB_Album *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = 1;
    return B;
}

void trocaCor_Album(struct arvRB_Album *raiz) {
    raiz->cor = !raiz->cor;

    if (raiz->esq != NULL)
        raiz->esq->cor = !raiz->esq->cor;
    if (raiz->dir != NULL)
        raiz->dir->cor = !raiz->dir->cor;
}

// Função de busca de artista na árvore
struct arvRB_Album *buscaAlbum(struct arvRB_Album *raiz, const char *titulo) {
    if (raiz == NULL) {
        return NULL; // Árvore vazia ou artista não encontrado
    }

    int comparacao = strcmp(titulo, raiz->titulo);

    if (comparacao == 0) {
        return raiz; // Artista encontrado
    } else if (comparacao < 0) {
        return buscaAlbum(raiz->esq, titulo); // Busca na subárvore esquerda
    } else {
        return buscaAlbum(raiz->dir, titulo); // Busca na subárvore direita
    }
}


void imprimeArvore_Album(struct arvRB_Album *raiz) {
    if (raiz != NULL) {
        imprimeArvore_Album(raiz->esq);
        printf("Titulo: %s, Ano de Lancamento: %d, Número de Musicas: %d\n", raiz->titulo, raiz->anoLancamento, raiz->numMusicas);
        imprimeArvore_Album(raiz->dir);
    }
}

void liberaArvore_Album(struct arvRB_Album **raiz) {
    if (*raiz != NULL) {
        liberaArvore_Album(&((*raiz)->esq));
        liberaArvore_Album(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;  // Define o ponteiro como NULL após liberar a memória
    }
}

