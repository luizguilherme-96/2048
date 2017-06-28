// =========================================================//       ;;;      ;;;;;;;;;;;    ;;;;;;;;;;;;   ;;;;;;;;;;;;
// Title: 2048 						    //       ;;;            ;;;;     ;;;      ;;;   ;;;     
// Author: Luiz Souza                                       //       ;;;           ;;;;      ;;;      ;;;   ;;;
// Data: 11/06/17				            //       ;;; 	  ;;;;	     ;;;;;;;;;;;;   ;;;;;;;;;;;;
// Descr.: Implementation of the game 2048 in C language    //       ;;;         ;;;;                 ;;;   ;;;      ;;;
//                                                          //       ;;; 	;;;;                  ;;;   ;;;      ;;;
//==========================================================//       ;;;;;;;;  ;;;;;;;;;;     ;;;;;;;;;;;   ;;;;;;;;;;;;

// Libraries 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

// functions prototypes -------------------------------------------------------------------------------------------------//
void GameOver ();
void Win ();
void refresh (int m[4][4]);
void game (int m[4][4]);
void begin (int m[4][4]);
void NewPiece (int m[4][4]);
int check (int m[4][4]);
int getch (void);

// global variables ---------------------------------------------------------------------------------------------------------//
int m[4][4] = {{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}}, pontos = 0, melhor, g = 0, p = 0, jogo, flag = 0; 

// main loop: //------------------------------------------------------------------------------------------------------------------------------//
int main (){
	begin (m);				                 // Seta o tabuleiro. Com duas pecas de 2 ou 4 com chances de 90%  
	
	while (jogo == 0){
		refresh (m);
		game (m);	
		
		if (flag == 1) {
		NewPiece (m);
		} 
		jogo = check (m);
		refresh (m);
	}
	// conferindo a pontuação:
	FILE *fptr;
	fptr = fopen("caminho\\Melhor.txt","r");
	
	if (fptr == NULL){
		printf("Erro!");
		exit (1);
	}
	fscanf(fptr,"%d", &melhor);
	
	if (pontos > melhor){
		melhor = pontos;
		fptr = fopen("caminho\\Melhor.txt","w");
		fprintf(fptr,"%d", p);
		fclose(fptr);
	}

	//--- GANHOU OU PERDEU ---//
	if (jogo == 1){
		system ("cls");
		zerou ();
		if (pontos <= 10){
		    printf("\n\t\t\t\t  Pontos: %d\n\n", pontos);
		}
		else if (pontos >10 && pontos <= 100){
		    printf("\n\t\t\t\t          Pontos: %d\n", pontos);
		}
		else {
		    printf("\n\t\t\t        Pontos: %d\n", pontos);
		}
	}
	else {
		system ("cls");
		fim_de_jogo ();
		if (pontos <= 10){
		    printf("\n\t\t\t\t  Pontosn", pontos);
			printf("\n\t\t\t    Melhor Pontuação: %d\n", melhor);
		}
		else if (pontos >10 && pontos <= 100){
		    printf("\n\t\t\t\t          Pontos: %d\n", pontos);
			printf("\n\t\t\t\tMelhor Pontuação: %d\n", melhor);
		}
		else {
		    printf("\n\t\t\t\t        Pontos: %d\n", pontos);
			printf("\n\t\t\t\tMelhor Pontuação: %d\n", melhor);
		}
	}
	
	return 0;
}

// implementando as funÃ§Ãµes: //---------------------------------------------------------------------------------------------------------------//
void refresh (int m[4][4]){
	int i, j, a, l, c;
	// atualiza a tela com a nova matriz: 
	system ("cls");
	printf(" \n ");
	printf("\t    2048\n\n");
	// "formataÃ§Ã£o condicional" para apresentaÃ§Ã£o dos pontos:
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
	
}

void comeco (int m[4][4]){
	int aux, alt,num, cont, i, j;
	srand(time(NULL));
	for (aux=0;aux<=1;){
	alt = rand();
	alt %=10;
	if (alt == 0){
	    num = 4;
	}
	else {
	    num = 2; 
	}
	alt = rand();
	alt %=16;
	for (i=0;i<4;i++){
	    for (j=0;j<4;j++){
	        if (alt == 0 && m [0][0] == 0){
	            m[i][j] = num;
	            cont = 0;
	            i = 4;
	            j = 4;
	            aux++;
	        }
	        else if (m[i][j] == 0){
	            cont ++;
	            if (cont == alt){
	              if (m[i][j] != 0){
	                    alt = rand();
	                    alt %= 16;
	                    cont = 0;
	                }
	                else if (m[i][j] == 0){
	                    m[i][j] = num;
	                    cont = 0;
	                    i = 4;
	                    j = 4;
	                    aux++;
	                }
	            }
	            else if (cont > 15){
	                cont = 0;
	            }
	        }
	    }
	}
	}
	}
	

void arranjando (int m[4][4]){
	int i, j, a, b;
	char seta;
	seta = getch();
	//scanf("%c",& seta);
	switch (seta){
	//-----------------------D---------------------//
		
	case  'd':                 
	flag = 0;
	    for (i=0;i<4;i++){                                               
	        for (j=3;j>0;){                                          
	            if (m[i][j] == 0){                                       
	                j--;                                                 
	            }
	            else if (m[i][j] != 0){                                  
	                for (a=(j-1);a>=0;a--){                              
	                    if (m[i][a] == m[i][j]){                         
	                        m[i][j] += m[i][a];                          
	                        m[i][a] = 0;
							pontos += m[i][j];                                 
	                        j--;       
							flag = 1;                                  
	                    }
	                    else if (m[i][a] != 0 && m[i][a] != m[i][j]){
	                        j--;
	                    }
	                    else if (a == 0 && m[i][a] == 0){
	                        j--;
	                        break;
	                    }
	                }
	            }
	        }
	    }
	//---------------reorganizando-----------------//                   
		for (i=0;i<4;i++){
		    for (j=2;j>=0;j--){
		        if (m[i][j] != 0){
		            for (b=(j+1);m[i][b] == 0 && b<4;){
		                m[i][b] = m[i][j];
		                m[i][j] = 0;
						flag = 1;
		                j++;
		                b++;
		            }
		        }
		        else {
		            continue;
		        }
		    }
		}
	//-----------------------A---------------------//
		break;
		case 'a':
		flag = 0;
	    for (i=0;i<4;i++){                                               
	        for (j=0;j<3;){                                              
	            if (m[i][j] == 0){                                       
	                j++;                                                 
	            }
	            else if (m[i][j] != 0){                                   
	                for (a=(j+1);a<=3;a++){                              
	                    if (m[i][a] == m[i][j]){                         
	                        m[i][j] += m[i][a];                          
	                        m[i][a] = 0;  
							pontos += m[i][j];                              
	                        j++;     
							flag = 1;                                    
	                    }
	                    else if (m[i][a] != 0 && m[i][a] != m[i][j]){
	                        j++;
	                    }
	                    else if (a == 3 && m[i][a] == 0){
	                        j++;
	                        break;
	                    }
	                }
	            }
	        }
	    }
	//---------------reorganizando-----------------//                   
		for (i=0;i<4;i++){
		    for (j=1;j<=3;j++){
		        if (m[i][j] != 0){
		            for (b=(j-1);m[i][b] == 0 && b>=0;){
		                m[i][b] = m[i][j];
						flag = 1;
		                m[i][j] = 0;
		                j--;
		                b--;
		            }
		        }
		        else {
		            continue;
		        }
		    }
		}
	//-----------------------S---------------------//
		break;
		case 's':
		flag = 0;
	    for (j=0;j<4;j++){                                               
	        for (i=3;i>0;){                                              
	            if (m[i][j] == 0){                                       
	                i--;                                                 
	            }
	            else if (m[i][j] != 0){                                   
	                for (a=(i-1);a>=0;a--){                              
	                    if (m[a][j] == m[i][j]){                         
	                        m[i][j] += m[a][j];                          
	                        m[a][j] = 0; 
							pontos += m[i][j];                               
	                        i--;      
							flag = 1;                                   
	                    }
	                    else if (m[a][j] != 0 && m[a][j] != m[i][j]){
	                        i--;
	                    }
	                    else if (a == 0 && m[a][j] == 0){
	                        i--;
	                        break;
	                    }
	                }
	            }
	        }
	    }
	//---------------reorganizando-----------------//                   
		for (j=0;j<4;j++){
		    for (i=2;i>=0;i--){
		        if (m[i][j] != 0){
		            for (b=(i+1);m[b][j] == 0 && b<4;){
		                m[b][j] = m[i][j];
		                m[i][j] = 0;
						flag = 1;
		                i++;
		                b++;
		            }
		        }
		        else {
		            continue;
		        }
		    }
		}
		break;
	//----------------------W----------------------//
		case 'w':
		flag = 0;
	    for (j=0;j<4;j++){                                               
	        for (i=0;i<4;){                                              
	            if (m[i][j] == 0){                                       
	                i++;                                                 
	            }
	            else if (m[i][j] != 0){                                   
	                for (a=(i+1);a<=4;a++){                              
	                    if (m[a][j] == m[i][j]){                         
	                        m[i][j] += m[a][j];                          
	                        m[a][j] = 0; 
							pontos += m[i][j];                               
	                        i++;                 
							flag = 1;                        
	                    }
	                    else if (m[a][j] != 0 && m[a][j] != m[i][j]){
	                        i++;
	                    }
	                    else if (a == 4 && m[a][j] == 0){	
	                        i++;
	                        break;
	                    }
	                }
	            }
	        }
	    }
	//---------------reorganizando-----------------//                   
		for (j=0;j<4;j++){
		    for (i=1;i<=3;i++){
		        if (m[i][j] != 0){
		            for (b=(i-1);m[b][j] == 0 && b>=0;){
		                m[b][j] = m[i][j];
		                m[i][j] = 0;
						flag = 1;
		                i--;
		                b--;
		            }
		        }
		        else {
		            continue;
		        }
		    }
		}
		break;                 
	}
}

void nova_peca (int m[4][4]){
	int alt,num, cont, i, j;
	
	
	cont =0;
	
	alt = rand();
	alt %=10;
	if (alt == 0){
	    num = 4;
	}
	else {
	    num = 2; 
	}
	
	alt = rand();
	alt %=16;
	
	for (i=0;i<4;i++){
	    for (j=0;j<4;j++){
			if (m[i][j] == 0 && cont != alt){
				cont ++;
			}
			else if (m[i][j] == 0 && cont == alt){
				m[i][j] = num;
				i = 4;
				j = 4;
			}
			else if (cont == alt && m[i][j] != 0){
				alt = rand();
				alt %= 16;
				cont = 0;
				i = 0;
				j = 0;
			}
			else if (m[i][j] != 0 && cont != alt){
				cont ++;
			}
	    }
	}
}

int verificar (int m[4][4]){
	int i, j, aux = -1, jogo;
	
	for (i=0;i<4;i++){
		for (j=0;j<4;j++){
			if (m[i][j] == 0){
				aux = 0;
				i = 4;
				j = 4;
			}
			else if (m[i][j] == 2048){
				aux = 1;
				j = 4;
				i = 4;
			}
			else {
				if (j  == 3 && i != 3){
					if (m[i][j] == m[i+1][j]){
						aux = 0;
						j = 4;
						i = 4;
					}
				}
				else if ( i == 3 && j != 3){
					if (m[i][j] == m[i][j+1]){
						aux = 0;
						j = 4;
						i = 4;
					}
				}
				else if (i == 3 && j == 3){
					continue;
				}
				else {
					if (m[i][j] == m[i+1][j] || m[i][j] == m[i][j+1]){
						aux = 0;
						j = 4;
						i = 4;
					}
				}
			}
	}
}
	
	if (aux == 0){
		jogo = 0;
	}
	else if (aux  == 1){
		jogo = 1;
	}
	else {
		jogo = -1;
	}
	
	return jogo;
}

void fim_de_jogo (){
	
	printf("\t\t\t.............   ....    ....................\n");
	printf("\t\t\t.............   ....    ....................\n");
	printf("\t\t\t....            ....    ....    ....    ....\n");
	printf("\t\t\t....            ....    ....    ....    ....\n");	
	printf("\t\t\t........        ....    ....    ....    ....\n");
	printf("\t\t\t........        ....    ....    ....    ....\n");
	printf("\t\t\t....            ....    ....    ....    ....\n");
	printf("\t\t\t....            ....    ....    ....    ....\n");
	printf("\t\t\t....            ....    ....    ....    ....\n");
	printf("\t\t\t....            ....    ....    ....    ....\n");
	printf("\t\t\t....            ....    ....    ....    ....\n\n");
	
	printf("\t\t\t     ........              ............     \n");
	printf("\t\t\t     ....   ....           ............     \n");
	printf("\t\t\t     ....     ....         ....             \n");
	printf("\t\t\t     ....      ....        ....             \n");	
	printf("\t\t\t     ....      .....       ..........       \n");
	printf("\t\t\t     ....      .....       ..........       \n");
	printf("\t\t\t     ....      .....       ....             \n");
	printf("\t\t\t     .....     .....       ....             \n");
	printf("\t\t\t     ....     .....        ....             \n");
	printf("\t\t\t     ....   ....           ............     \n");
	printf("\t\t\t     .........             ............     \n\n");
	
	printf("\t         ....     ...............    ................    ...............\n");
	printf("\t         ....     ...............    ................    ...............\n");
	printf("\t         ....     ....       ....    ....                ....       ....\n");
	printf("\t         ....     ....       ....    ....                ....       ....\n");
	printf("\t         ....     ....       ....    ....                ....       ....\n");	
	printf("\t         ....     ....       ....    ....                ....       ....\n");
	printf("\t         ....     ....       ....    ....    ........    ....       ....\n");
	printf("\t         ....     ....       ....    ....    ........    ....       ....\n");
	printf("\t         ....     ....       ....    ....        ....    ....       ....\n");
	printf("\t  .     ....      ....       ....    ....        ....    ....       ....\n");
	printf("\t  ..   ....       ...............    ................    ...............\n");
	printf("\t   ......         ...............    ................    ...............\n");	
	
	if (pontos > melhor)
	{
		melhor = pontos;
	}
}

void zerou (){
	
	printf("\t\t\t...............     .................     .................         ................\n");
	printf("\t\t\t...............     .................     .................         ................\n");
	printf("\t\t\t....       ....     ....         ....     ....         ....         ....        ....\n");
	printf("\t\t\t....       ....     ....         ....     ....         ....         ....        ....\n");	
	printf("\t\t\t....       ....     ....         ....     ....         ....         ................\n");
	printf("\t\t\t....       ....     .................     .................         ................\n");
	printf("\t\t\t....       ....     .................     .................         ....        ....\n");
	printf("\t\t\t....       ....     ....  .....           ....  .....               ....        ....\n");
	printf("\t\t\t....       ....     ....    .....         ....    .....             ....        ....\n");
	printf("\t\t\t...............     ....      .....       ....      .....           ....        ....\n");
	printf("\t\t\t...............     ....        .....     ....        .....         ....        ....\n\n");
	
	if (pontos > melhor)
	{
		melhor = pontos;
	}
}

int getch(void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}
