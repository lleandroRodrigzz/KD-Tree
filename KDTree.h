#include <conio.h>
#include <conio2.h>

#define K 2		//Define a dimensão dos dados
#define N 15	//Define o numero de pontos

struct kdtree{
	int ponto[K];
	struct kdtree *esq, *dir;
};
typedef struct kdtree KDT;

/*----------------------- Cordenadas ------------------------*/
int geradorNum()
{
	return rand() % 70 + 10;	
}

void geradorCordenadas(int pontos[N][K])
{
	int i,j;
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < K; j++)
		{
			pontos[i][j] = geradorNum();
		}
	}
}

void ordenarPontosNivel(int pontos[N][K], int inicio, int fim, int discri)
{
	int posMenor, aux, i, j, l;
	fim++;
	for(i = inicio; i < fim - 1; i++)
	{
		posMenor = i;
		for(j = i; j < fim; j++)
		{
			if(pontos[j][discri] < pontos[posMenor][discri])
				posMenor = j;
		}
	}
	// Trocar todas as posicoes menor que i
	for(l = 0; l < K; l++)
	{
		aux = pontos[i][l];
		pontos[i][l] = pontos[posMenor][l];
        pontos[posMenor][l] = aux;
	}
}

void exibeCordenadas(int pontos[N][K])
{
	printf("\n\t");
	for (int i = 0; i < N; i++)
        printf("(%d, %d) - ", pontos[i][0], pontos[i][1]);
    printf("\n\n");
}
/*-----------------------------------------------------------*/

/*----------------------- Calculo ------------------------*/
float distanciaEuclidiana(int ponto[], int ponto1[])
{
	int i;
	double dist = 0.0;
	
	for(i = 0; i < K; i++)
	{
		dist += pow(ponto[i] - ponto1[i], 2);
	}
	return sqrt(dist);
}
/*--------------------------------------------------------*/

/*----------------------- KD-Tree ------------------------*/
KDT *criaNo(int ponto[])
{
	int i;
	KDT *no = (KDT*)malloc(sizeof(KDT));
	for(i = 0; i < K; i++)
		no->ponto[i] = ponto[i];
	no->esq = no->dir = NULL;
	
	return no;
}

void construirKDT(KDT* *Raiz, int pontos[N][K], int inicio, int fim, int nivel)
{
	int discri, meio;
	if(inicio <= fim)
	{
		discri = nivel % K;
		ordenarPontosNivel(pontos, inicio, fim, discri);
		
		meio = (inicio + fim) / 2;
		
		*Raiz = criaNo(pontos[meio]);
		
		construirKDT(&(*Raiz)->esq, pontos, inicio, meio - 1, nivel + 1);
		construirKDT(&(*Raiz)->dir, pontos, meio + 1, fim, nivel + 1);
	}
}

void insereKDT(KDT* *Raiz, int ponto[], int nivel)
{
	int discri;
	discri = N % K;
	if(ponto[discri] < (*Raiz)->ponto[discri])
	{
		insereKDT(&(*Raiz)->esq, ponto, nivel + 1);
	}
	else
	{
		insereKDT(&(*Raiz)->dir, ponto, nivel + 1);
	}
}

void buscaKDT(KDT *Raiz, int ponto[], int raio, char *flag)
{
	static int cont = 0;
	double dEuclid;
	if(Raiz != NULL)
	{
		dEuclid = distanciaEuclidiana(Raiz->ponto, ponto);
		if(dEuclid <= raio)
		{
			cont++;
			printf("[%d,%d],  ", Raiz->ponto[0], Raiz->ponto[1]);
			if(cont == 9)
			{
				printf("\n\t\t\t");
				cont = 0;
			}
			*flag = 1;
		}
		buscaKDT(Raiz->esq, ponto, raio, flag);
		buscaKDT(Raiz->dir, ponto, raio, flag);
	}
}

void exibeKDT(KDT *Raiz)
{
	static int nivel = -1, i;
	if(Raiz != NULL)
	{
		nivel++;
		exibeKDT(Raiz->dir);
		
		for(i = 0; i < 5; i++)
			printf(" ");
		printf("(%d,%d)\n", Raiz->ponto[0], Raiz->ponto[1]);
		
		exibeKDT(Raiz->esq);
		nivel--;
	}
	
}

void exibeKDTVert(KDT *raiz, int x, int y, int deslocamento)
{
	int novoXEsq, novoXDir, novoY;
    if (raiz != NULL) {
        gotoxy(x, y);
        // Calcula a posição dos filhos
        printf("(%d,%d)\n", raiz->ponto[0], raiz->ponto[1]);
        novoXEsq = x - deslocamento;
        novoXDir = x + deslocamento;
        novoY = y + 2;
        // Exibe as subárvores esquerda e direita com recuo
        exibeKDTVert(raiz->esq, novoXEsq, novoY, deslocamento / 2);
        exibeKDTVert(raiz->dir, novoXDir, novoY, deslocamento / 2);
    }
}

void limpaKDT(KDT *Raiz)
{
	if(Raiz != NULL)
	{
		limpaKDT(Raiz->esq);
		limpaKDT(Raiz->dir);
		free(Raiz);
	}
}
/*--------------------------------------------------------*/