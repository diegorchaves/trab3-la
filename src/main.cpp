#include <GL/glut.h>
#include <GL/freeglut_ext.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gl_canvas2d.h"
#include "auxiliar.h"
#define TAM 3

int screenWidth = 1000, screenHeight = 500;
int mouseX, mouseY;
int matrizA [TAM][TAM], matrizB [TAM][TAM], matrizC [TAM][TAM];
int estagio = 0;
int botaoMultiplicarX0 = 60;
int botaoMultiplicarY0 = 420;
int botaoDeterminanteX0 = 820;
int tamanhoXbotoes = 110;
int tamanhoYbotoes = 40;
int tamanhoMatrizX = 100;
int tamanhoMatrizY = 100;
int espacoEntreMatrizes = 250;
int espacoEntreBotoes = 50;
int posicaoInicialMatrizA = 50;

void imprimeMatriz (int matriz [TAM][TAM], int posicaoInicialMatriz){
    int i, j, offset = 50, posicaoY = 50;
    for (i = 0; i < TAM; i++){
        for (j = 0; j < TAM; j++){
            CV::text(posicaoInicialMatriz + i*offset, posicaoY + j*offset, matriz [i][j]);
        }
    }
}

void multiplicarMatriz (int matrizA [TAM][TAM], int matrizB [TAM][TAM], int matrizC [TAM][TAM]){
    int i, j, k;
    for (i = 0; i < TAM; i++){
        for (j = 0; j < TAM; j++){
            matrizC [i][j] = 0;
            for (k = 0; k < TAM; k++){
                matrizC [i][j] += matrizA [i][j] * matrizB [k][j];
            }
        }
    }
}

void somarMatriz (int matrizA [TAM][TAM], int matrizB [TAM][TAM], int matrizC [TAM][TAM]){
    int i, j;
    for (i = 0; i < TAM; i++){
        for (j = 0; j < TAM; j++){
            matrizC [i][j] = matrizA [i][j] + matrizB [i][j];
        }
    }
}

void subtrairMatriz (int matrizA [TAM][TAM], int matrizB [TAM][TAM], int matrizC [TAM][TAM]){
    int i, j;
    for (i = 0; i < TAM; i++){
        for (j = 0; j < TAM; j++){
            matrizC [i][j] = matrizA [i][j] - matrizB [i][j];
        }
    }
}

int calcularDeterminante (int matrizC [TAM][TAM]){
    int determinante;
    determinante = matrizC[0][0] * (matrizC[1][1] * matrizC[2][2] - matrizC[1][2] * matrizC[2][1]) -
                   matrizC[0][1] * (matrizC[1][0] * matrizC[2][2] - matrizC[1][2] * matrizC[2][0]) +
                   matrizC[0][2] * (matrizC[1][0] * matrizC[2][1] - matrizC[1][1] * matrizC[2][0]);
    return determinante;
}

void colchete1 (){
    CV::line (30, 30, 30, 160);
    CV::line (30, 30, 40, 30);
    CV::line (30, 160, 40, 160);
    CV::line (180, 30, 180, 160);
    CV::line (180, 30, 170, 30);
    CV::line (180, 160, 170, 160);
}

void colchete2 (){
    CV::line (280, 30, 280, 160);
    CV::line (280, 30, 290, 30);
    CV::line (280, 160, 290, 160);
    CV::line (430, 30, 430, 160);
    CV::line (430, 30, 420, 30);
    CV::line (430, 160, 420, 160);
}

void colchete3 (){
    CV::line (530, 30, 530, 160);
    CV::line (530, 30, 540, 30);
    CV::line (530, 160, 540, 160);
    CV::line (690, 30, 690, 160);
    CV::line (690, 30, 680, 30);
    CV::line (690, 160, 680, 160);
}

void sinalX (){
    CV::line (220, 90, 240, 110);
    CV::line (240, 90, 220, 110);
}

void sinalIgual (){
    CV::line (470, 90, 490, 90);
    CV::line (470, 95, 490, 95);
}

void sinalSoma (){
    CV::line (220, 100, 240, 100);
    CV::line (230, 90, 230, 110);
}

void sinalSubtrair (){
    CV::line (220, 100, 240, 100);
}

void textMatrizAB (){
    CV::text(60, 200, "Matriz A");
    CV::text (320, 200, "Matriz B");
}

void textMatrizC (){
    CV::text(570, 200, "Matriz C");
}

void botaoGerar (){
    CV::rect (botaoMultiplicarX0, botaoMultiplicarY0 - 100, botaoMultiplicarX0 + tamanhoXbotoes, botaoMultiplicarY0 - 100 + tamanhoYbotoes);
    CV::text (botaoMultiplicarX0, botaoMultiplicarY0 - 100 + tamanhoYbotoes * 1.5, "Gerar de novo");
}

void botaoMultiplicar (){
    CV::rect (botaoMultiplicarX0, botaoMultiplicarY0, botaoMultiplicarX0 + tamanhoXbotoes, botaoMultiplicarY0 + tamanhoYbotoes);
    CV::text (botaoMultiplicarX0, botaoMultiplicarY0 + tamanhoYbotoes * 1.5, "Multiplicar");
}

void botaoDeterminante (){
    CV::rect (botaoDeterminanteX0, botaoMultiplicarY0, botaoDeterminanteX0 + tamanhoXbotoes, botaoMultiplicarY0 + tamanhoYbotoes);
    CV::text (botaoDeterminanteX0, botaoMultiplicarY0 + tamanhoYbotoes * 1.5, "Determinante");
}

void botaoSomar (){
    CV::rect (botaoMultiplicarX0 + tamanhoXbotoes + espacoEntreBotoes, botaoMultiplicarY0, botaoMultiplicarX0 + tamanhoXbotoes + espacoEntreBotoes + tamanhoXbotoes, botaoMultiplicarY0 + tamanhoYbotoes);
    CV::text (botaoMultiplicarX0 + tamanhoXbotoes + espacoEntreBotoes, botaoMultiplicarY0 + tamanhoYbotoes * 1.5, "Somar");
}

void botaoSubtrair (){
    CV::rect (botaoMultiplicarX0 + tamanhoXbotoes + 2 * espacoEntreBotoes + tamanhoXbotoes, botaoMultiplicarY0, botaoMultiplicarX0 + tamanhoXbotoes + 2 * espacoEntreBotoes + tamanhoXbotoes + tamanhoXbotoes, botaoMultiplicarY0 + tamanhoYbotoes);
    CV::text (botaoMultiplicarX0 + tamanhoXbotoes + 2 * espacoEntreBotoes + tamanhoXbotoes, botaoMultiplicarY0 + tamanhoYbotoes * 1.5, "Subtrair");
}



void render()
{
    //Matriz AB -- estagio 0 -> nesse estagio sao impressas as matrizes A e B geradas aleatoriamente
    CV::clear(0, 0, 0);
    CV::color(255, 255, 255);
    textMatrizAB ();
    imprimeMatriz (matrizA, posicaoInicialMatrizA);
    colchete1 ();
    imprimeMatriz (matrizB, posicaoInicialMatrizA + espacoEntreMatrizes);
    colchete2 ();
    botaoMultiplicar();
    botaoSomar ();
    botaoSubtrair ();
    botaoGerar ();

    //Multiplicar -- estagio 1 -> esse estagio eh ativo caso o usuario clique no botao Multiplicar, imprime a matriz C resultante
    if (estagio == 1){
        textMatrizC ();
        multiplicarMatriz (matrizA, matrizB, matrizC);
        imprimeMatriz (matrizC, posicaoInicialMatrizA + 2 * espacoEntreMatrizes);
        colchete3 ();
        sinalIgual();
        sinalX ();
        botaoDeterminante();
    }

    //Determinante - estagio 2 -> caso o usuario multiplique, eh apresentado o botao de Determinante nesse estagio
    if (estagio == 2){
        textMatrizC ();
        imprimeMatriz (matrizC, posicaoInicialMatrizA + 2 * espacoEntreMatrizes);
        colchete3 ();
        sinalIgual();
        sinalX ();
        botaoDeterminante();
        CV::text (750, 200, "Determinante = ");
        CV::text (900, 200, calcularDeterminante(matrizC));
    }

    //Somar - estagio 3 -> caso o usuario clique em somar, eh impressa a matriz C resultante e o sinal de soma
    if (estagio == 3){
        textMatrizC ();
        somarMatriz (matrizA, matrizB, matrizC);
        imprimeMatriz (matrizC, posicaoInicialMatrizA + 2 * espacoEntreMatrizes);
        colchete3 ();
        sinalSoma();
        sinalIgual();
    }

    //Subtrair - estagio 4 -> caso o usuario clique em subtrair, eh impressa a matriz C resultante e o sinal de subtracao
    if (estagio == 4){
        textMatrizC ();
        subtrairMatriz (matrizA, matrizB, matrizC);
        imprimeMatriz (matrizC, posicaoInicialMatrizA + 2 * espacoEntreMatrizes);
        colchete3 ();
        sinalSubtrair ();
        sinalIgual();
    }
}

void keyboard(int key)
{
}

void keyboardUp(int key)
{
}

//essa funcao gera as matrizes A e B aleatoriamente com valores entre -10 e 10
void gerarMatriz (int matriz [TAM][TAM]){
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            matriz [i][j] = rand () % 21 - 10;
        }
    }
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
   //printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
    if (state == 0){
        //aqui faco o tratamento do botao de gerar matrizes
        if (x > botaoMultiplicarX0 && x < botaoMultiplicarX0 + tamanhoXbotoes && y > botaoMultiplicarY0 - 100 && y < botaoMultiplicarY0 - 100 + tamanhoYbotoes){
            gerarMatriz (matrizA);
            gerarMatriz (matrizB);
            estagio = 0;
        }
        //aqui faco o tratamento do botao de multiplicar
        else if (x > botaoMultiplicarX0 && x < botaoMultiplicarX0 + tamanhoXbotoes && y > botaoMultiplicarY0 && y < botaoMultiplicarY0 + tamanhoYbotoes){
            estagio = 1;
        }
        //aqui faco o tratamento do botao determinante
        else if (x > botaoDeterminanteX0 && x < botaoDeterminanteX0 + tamanhoXbotoes && y > botaoMultiplicarY0 && y < botaoMultiplicarY0 + tamanhoYbotoes){
            estagio = 2;
        }
        //aqui faco o tratamento do botao de soma
        else if (x > botaoMultiplicarX0 + tamanhoXbotoes + espacoEntreBotoes && x < botaoMultiplicarX0 + tamanhoXbotoes + espacoEntreBotoes + tamanhoXbotoes && y > botaoMultiplicarY0 && y < botaoMultiplicarY0 + tamanhoYbotoes){
            estagio = 3;
        }
        //e por fim, tratamento do botao de subtrair
        else if (x > botaoMultiplicarX0 + tamanhoXbotoes + 2 * espacoEntreBotoes + tamanhoXbotoes && x < botaoMultiplicarX0 + tamanhoXbotoes + 2 * espacoEntreBotoes + tamanhoXbotoes + tamanhoXbotoes && y > botaoMultiplicarY0 && y < botaoMultiplicarY0 + tamanhoYbotoes){
            estagio = 4;
        }
    }
}



int main(void)
{
    CV::init(&screenWidth, &screenHeight, "Calculos com Matrizes - Diego Ribeiro Chaves");
    srand (time(NULL));
    gerarMatriz (matrizA);
    gerarMatriz (matrizB);
    CV::run();
}
