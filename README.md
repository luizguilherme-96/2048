# 2048
Implementação do jogo 2048 em C.  Aqui coloco pedaços de código que me ajudam a escrever o código por completo. Quando o projeto estiver finalizado o código ficará disponível nesse repositório.


// Aqui está uma sujestão de como se imprimir a matriz m que possui os valores de cada parte do tabuleiro.

#include <stdio.h>
#include <stdlib.h>

// Código : Imprimindo a matriz
// Descrição: Usa uma formatação condicional para que o tabuleiro nao sofra alguma distorção ou desconfiguração quando imprimir 
// números maiore. A posição da pontuação também varia com seu valor para que sempre fique mais ou menos centralizada com o //tabuleiro.


// vairáveis:
int m[4][4] = {{0, 2048, 2, 16},{2, 0, 4, 128},{0, 2, 256, 1024},{4, 4, 2, 32}};
int i, j, a, l, c, pontos = 1110;
char seta;
 
// MAIN LOOP: 
int main () {

// atualiza a tela com a nova matriz: 
system ("cls");
printf(" \n ");
printf("\t    2048\n\n");
// "formatação condicional" para apresentação dos pontos:
if (pontos <= 10){
    printf("\t  Pontos: %d\n\n", pontos);
}
else if (pontos >10 && pontos <= 100){
    printf("          Pontos: %d\n\n", pontos);
}
else {
    printf("        Pontos: %d\n\n", pontos);
}
//-----------------------------------------------------//
for (l=0;l<4;l++){
    printf ("-----------------------------\n");
    for (c=0;c<4;c++){
     if (m[l][c]==0){
        if (c == 3){
            printf("|      |");
        }
        else {
            printf("|      ");
        }
    }
     else {
        if (c == 3){
            if (m[l][c] > 1023){
                printf("| %d |",m[l][c]);
            }
            else if (m[l][c] > 127){
                printf("| %d  |",m[l][c]);
            }
            else if (m[l][c] > 15){
                printf("|  %d  |",m[l][c]);
            }
            else {
                printf("|  %d   |",m[l][c]);
            }
        }
        else {
            if (m[l][c] > 1023){
                printf("| %d ",m[l][c]);
            }
            else if (m[l][c] > 127){
                printf("| %d  ",m[l][c]);
            }
            else if (m[l][c] > 15){
                printf("|  %d  ",m[l][c]);
            }
            else {
                printf("|  %d   ",m[l][c]);
            }
            }
        }
    }
       printf("\n"); 
 }


printf ("-----------------------------\n");
printf("\n\n");
printf("          Comandos:\n\n\t     w\n\n          a  s  d\n\n\n");
//printf("-------------------------\n\n");
return 0;
}

// Texto para mostrar na final do jogo.  Caso perca ou ganhe o jogo, é preciso mostrar quem fez saporrah.
//printf(" Design and Developed by:\n\n");
//printf("  ;;;;      ;;;;;;;;;;\n  ;;;;      ;;;;;;;;;\n  ;;;;         ;;;;;\n  ;;;;        ;;;;;\n  ;;;;;;;;   ;;;;;;;;;\n  ;;;;;;;;  ;;;;;;;;;; \n\n\n\n");
