#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef struct no_t_ {
	struct no_t_ *esq;
	struct no_t_ *dir;
	int val;
} no_t;

// Funcao que recebe duas arvores
// e retorna true caso elas sejam identicas
// (mesma estrutura e valores nos mesmos lugares)
// ou false caso contrario.
// Deve funcionar para qualquer arvore binaria
bool eh_igual(no_t *a1, no_t* a2){
	if(a1 == a2 && a1 == NULL){
		return true;
	}
	if(a1 == NULL || a2 == NULL) {
		return false;
	}
	
	bool esq = eh_igual(a1->esq, a2->esq);
	bool dir = eh_igual(a1->dir, a2->dir); //pos ordem 

	return esq && dir && a1->val == a2->val;
}

// Funcao que dada uma arvore, deve retornar a quantidade de nos
// da arvore que possuem exatamente dois filhos
// Deve funcionar para qualquer arvore binaria
int count2filhos(no_t *a){
	if(a == NULL) return 0;
	int count = 0;

	if(a->esq != NULL && a->dir != NULL){
		count = 1;
	}

	count = count + count2filhos(a->esq) + count2filhos(a->dir);

	return count;
}

// Funcao que deve retornar um ponteiro para o 
// segundo menor elemento da arvore, ou nulo se a arvore
// possuir menos do que 2 elementos
// Deve funcionar para qualquer arvore binaria de busca
no_t *segundo_menor(no_t *a){
	//para qualquer arvore binaria
	if(a == NULL) return NULL;
	if(a->esq == NULL && a->dir == NULL) return NULL; // só tem ele

	if(a->esq == NULL){
		no_t *aux = a->dir;
		while(aux->esq){
			aux = aux->esq;
		}
		return aux; //ou vai ser o primeiro da direita ou vai ser o ultimo esquerda da direita
	}

	while(a->esq->esq){ //enquanto nao for nula
		a = a->esq;
	}

	if(a->esq->dir != NULL){
        no_t *aux = a->esq->dir;   // começa no filho direito do menor
        while(aux->esq){           // desce até o menor dessa subárvore
            aux = aux->esq;
        }
        return aux;
    }
	return a;
}

//posibilidade recursiva
no_t *minimo(no_t *a){
    if(a->esq == NULL) return a;   // caso base: não dá pra ir mais à esquerda
    return minimo(a->esq);         // o menor está sempre mais à esquerda
}

no_t *segundo_menor_rec(no_t *a){
    if(a == NULL) return NULL;

    // Caso 1: a é o menor da árvore
    if(a->esq == NULL){
        if(a->dir == NULL) return NULL;  // só existe ele
        return minimo(a->dir);           // sucessor dele
    }

    // Caso 2: o filho esquerdo é o menor
    if(a->esq->esq == NULL){
        if(a->esq->dir == NULL) return a;  // sem direita: o sucessor é o pai
        return minimo(a->esq->dir);        // com direita: menor dela
    }

    // Caso 3: ainda há mais de um nível à esquerda, desce
    return segundo_menor_rec(a->esq);
}

// Dentre todos os caminhos possiveis da raiz ate cada umas das folhas,
// deve retornar o valor do menor destes caminhos (o valor do caminho eh
// a soma dos valores de todos os nos percorridos)
// Faca uma versao que funciona para arvore binaria de busca
// Faca uma outra versao que funcia para arvore binaria qualquer
int menor_caminho_raiz_folha(no_t *a){
    if(a == NULL) return 0;                       // árvore vazia: não há caminho

    if(a->esq == NULL && a->dir == NULL)          // folha: o caminho termina aqui
        return a->val;

    if(a->esq == NULL)                            // só tem filho direito
        return a->val + menor_caminho_raiz_folha(a->dir);

    if(a->dir == NULL)                            // só tem filho esquerdo
        return a->val + menor_caminho_raiz_folha(a->esq);

    int e = menor_caminho_raiz_folha(a->esq);     // dois filhos: escolhe o melhor lado
    int d = menor_caminho_raiz_folha(a->dir);
	
    return a->val + (e < d ? e : d);
}

