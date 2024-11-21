#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include "KDTree.h"

#define YELLOW 14
#define BLUE 1
#define BLACK 0

void configurarConsole(int largura, int altura) 
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT janela = {0, 0, largura - 1, altura - 1};
    COORD tamanhoBuffer = {largura, altura};

    // Ajusta o tamanho do buffer
    SetConsoleScreenBufferSize(hOut, tamanhoBuffer);

    // Ajusta o tamanho da janela
    SetConsoleWindowInfo(hOut, TRUE, &janela);

    // Maximiza o console
    HWND console = GetConsoleWindow();
    ShowWindow(console, SW_MAXIMIZE);
}

void preencherTelaAzul() {
    int linhas = 30; // Máximo de linhas para o console
    int colunas = 120; // Máximo de colunas para o console
    int i, j;

    textbackground(BLUE); 
    clrscr(); // Limpa a tela com a cor de fundo configurada

    for (i = 1; i <= linhas; i++) {
        for (j = 1; j <= colunas; j++) {
            gotoxy(j, i); 
            printf(" "); 
        }
    }
    gotoxy(120,30);
}

void Moldura(int CI, int LI, int CF, int LF, int CorT, int CorF) 
{
    int i;
    textcolor(CorT);
    textbackground(CorF);
    gotoxy(CI, LI); printf("%c", 201);
    gotoxy(CI, LF); printf("%c", 200);
    gotoxy(CF, LI); printf("%c", 187);
    gotoxy(CF, LF); printf("%c", 188);

    for (i = CI + 1; i < CF; i++) {
        gotoxy(i, LI); printf("%c", 205);
        gotoxy(i, LF); printf("%c", 205);
    }
    for (i = LI + 1; i < LF; i++) {
        gotoxy(CI, i); printf("%c", 186);
        gotoxy(CF, i); printf("%c", 186);
    }
    textcolor(7);
    textbackground(0);
}

int main()
{
	configurarConsole(120,30);
	preencherTelaAzul();
	textbackground(BLUE); 
	textcolor(YELLOW);
	
	int pontos[N][K], pontoBusca[K], raio;
    KDT *Raiz = NULL;
    char flag = 0;
    srand(time(NULL));
	
	/*------------------------------------------ PRIMEIRA TELA ----------------------------------------------------------*/
	system("cls");
	Moldura(3,2,118,4,BLACK,BLUE); //Borda Titulo
	textbackground(BLUE);
	textcolor(YELLOW);
	gotoxy(12,3); printf("#### ARVORE KD-TREE - DESENVOLVIDO POR LEANDRO M. C. RODRIGUES - PROFESSOR FRANCISCO DE ASSIS ####");
	
	Moldura(54,4,66,6,BLACK,BLUE); //Borda SubTitulo
	textbackground(BLUE);
	textcolor(YELLOW);
	gotoxy(57,5); printf("KD-TREE");
    
    geradorCordenadas(pontos);
    gotoxy(24,6);printf("*Numero De Pontos (N): %d*", N);
    gotoxy(71,6);printf("*Dimensao Dos Dados (K): %d*", K);
    gotoxy(4,10);printf("*Coordenadas Geradas*\n");
    exibeCordenadas(pontos);
    

    construirKDT(&Raiz, pontos, 0, N - 1, 0);
    gotoxy(40,17);printf("KD-Tree (Vertical):");
    //exibeKDT(Raiz);
    exibeKDTVert(Raiz, 46, 19, 22);
    
    pontoBusca[0] = geradorNum();
    pontoBusca[1] = geradorNum();
    raio = rand() % 10 + 10;
	
	gotoxy(23,8);printf("*Ponto para Buscar: (%d, %d)*", pontoBusca[0], pontoBusca[1]);
    gotoxy(79,8);printf("*Raio: %d*", raio);
	
	gotoxy(10,33);printf("*Resultado: ");
	buscaKDT(Raiz, pontoBusca, raio, &flag);
	if(!flag)
	{
		printf("Nao Foram Encontrados Pontos !");
	} 
	limpaKDT(Raiz);
    getch();
    /*-------------------------------------------------------------------------------------------------------------------*/

    textbackground(BLACK);
	system("cls");
	gotoxy(50,15);
    return 0;
}