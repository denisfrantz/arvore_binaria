#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 50

typedef struct No {
    int req;
    char encant[TAM];
    struct No *esquerda;
    struct No *direita;
} No;

No* criarNo(int req, char* encant) {
    No* no = (No*) malloc(sizeof(No));
    no->req = req;
    strcpy(no->encant, encant);
    no->esquerda = NULL;
    no->direita = NULL;
    
    return no;
}

int isArvoreVazia(No* raiz) {
    if (raiz == NULL)
        return 1;
	else
		return 0;
}

No* inserirNo(No* raiz, int req, char* encant) {
    if (isArvoreVazia(raiz)) {
		raiz = criarNo(req, encant);
    }
    else if (req < raiz->req) {
        raiz->esquerda = inserirNo(raiz->esquerda, req, encant);
    }
    else {
    	raiz->direita = inserirNo(raiz->direita, req, encant);
	}
	return raiz;
}

No* buscarNo(No* raiz, int req) {
    if (isArvoreVazia(raiz) || raiz->req == req) {
        return raiz;
    }
    else if (req < raiz->req) {
        return buscarNo(raiz->esquerda, req);
    }
    else {
        return buscarNo(raiz->direita, req);
    }
}

No* encontrarMenorNo(No* no) {
    No* atual = no;
    while (atual->esquerda != NULL) {
        atual = atual->esquerda;
    }
    return atual;
}

No* removerNo(No* raiz, int req) {
    if (req < raiz->req) {
        raiz->esquerda = removerNo(raiz->esquerda, req);
    }
    else if (req > raiz->req) {
        raiz->direita = removerNo(raiz->direita, req);
    }
    else {
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            raiz = NULL;
        }
        else if (raiz->esquerda == NULL) {
            No* aux = raiz;
            raiz = raiz->direita;
            free(aux);
        }
        else if (raiz->direita == NULL) {
            No* aux = raiz;
            raiz = raiz->esquerda;
            free(aux);
        }
        else {
            No* aux = encontrarMenorNo(raiz->direita);
            raiz->req = aux->req;
            raiz->direita = removerNo(raiz->direita, aux->req);
        }
    }
    return raiz;
}

void emOrdem(No* raiz) {
	if (!isArvoreVazia(raiz)) {
		emOrdem(raiz->esquerda);
    	printf("[%d] -> %s", raiz->req, raiz->encant);
    	emOrdem(raiz->direita);	
	}
}

void preOrdem(No* raiz) {
	if (!isArvoreVazia(raiz)) {
		printf("[%d] -> %s", raiz->req, raiz->encant);
    	preOrdem(raiz->esquerda);
    	preOrdem(raiz->direita);
	}
}

void posOrdem(No* raiz) {
	if (!isArvoreVazia(raiz)) {
		posOrdem(raiz->esquerda);
    	posOrdem(raiz->direita);
    	printf("[%d] -> %s", raiz->req, raiz->encant);
	}
}

void menu(){
	int req, opcao;
	char encant[TAM];
	No* raiz = NULL;
	
	printf ("[1] Inserir\n");
	printf ("[2] Remover\n");
	printf ("[3] Busca\n");
	printf ("[4] Em Ordem\n");
	printf ("[5] Pre-Ordem\n");
	printf ("[6] Pos-Ordem\n");
	printf ("[7] Sair\n");
	
	while (1){
		printf ("\nEscolha uma opcao: ");
		scanf ("%d", &opcao);
		
	    switch (opcao) {
	    	case 1:
	    		printf ("INSERIR o requerimento: ");
				scanf ("%d", &req);
				getchar();
				if (!buscarNo(raiz, req)){
					printf ("INSERIR o encantamento: ");
					fgets(encant, TAM, stdin);
					raiz = inserirNo(raiz, req, encant);
					printf("O encantamento foi inserido na arvore com sucesso!\n");
				}
				else {
					printf("Erro: ja existe um encantamento com esse requerimento na arvore!\n"); 
				}
				break;
	            
	        case 2:
	        	if (isArvoreVazia(raiz)) {
	        		printf("Erro: a arvore esta vazia!\n");
				}
				else {
					printf ("REMOVER o requerimento: ");
				    scanf ("%d", &req);
				    if (req != raiz->req) {
				    	if (!buscarNo(raiz, req)) {
				    	printf("Erro: nao existe nenhum encantamento com %d de requerimento na arvore!\n", req);
						}
						else {
							raiz = removerNo(raiz, req);
							printf("O encantamento foi removido da arvore com sucesso!\n");
						}
					}
					else {
						printf ("Erro: nao e possivel remover a raiz!\n");
					}
				}
			    break;
    			
    		case 3:
    			if (isArvoreVazia(raiz)) {
    				printf("Erro: a arvore esta vazia!\n");
				}
				else {
					printf("BUSCAR o requerimento: ");
				    scanf("%d", &req);
				    No* noEncontrado = buscarNo(raiz, req);
				    if (noEncontrado == NULL) {
				        printf("Nao existe nenhum encantamento com %d de requerimento na arvore.\n", req);
				    } 
					else {
				        printf("O requerimento %d foi encontrado na arvore. Ele esta associado ao encantamento %s", req, noEncontrado->encant);
				    }
				}
				break;
    			
    		case 4:
    			if (isArvoreVazia(raiz)){
    				printf("Erro: a arvore esta vazia!\n");
				}
				else {
					printf("Arvore em ordem:\n");
					emOrdem(raiz);
				}
    			break;
    			
    		case 5:
    			if (isArvoreVazia(raiz)){
    				printf("Erro: a arvore esta vazia!\n");
				}
				else {
					printf("Arvore em pre-ordem:\n");
    				preOrdem(raiz);
				}
    			break;
    			
    		case 6:
    			if (isArvoreVazia(raiz)){
    				printf("Erro: a arvore esta vazia!\n");
				}
				else {
					printf("Arvore em pos-ordem:\n");
    				posOrdem(raiz);
				}
    			break;
    			
    		case 7:
    			printf ("Programa finalizado!\n");
    			exit(0);
    			
    		default:
    			printf ("Opcao invalida!\n");
		}
	}
}

int main() {
    menu();
    
    return 0;
}
