#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iso646.h>
#define AND 	1
#define OR	2
#define NOT 	3
#define NOR 	4
#define NAND	5
#define XOR	6
#define MAX_ENTRADA 		10
#define MAX_SAIDA    		10
#define MAX_PORTA_LOGICA	1000
#define MAX_CONECTOR 		1000
#define MAX_COMBINACOES 	1024

struct portaLogica{
	int tipo;
	int input[2];
	int output;
	int estado;
};
struct conector{
	int valor;
	int no;
};
struct input{
	char representacao[5];
	int valor;
	int no;
};
struct output{
	char representacao[5];
	int valor;
	int no;
};
struct numeroContador{
	int Conector;
    int Entrada;
    int Saida;
    int Porta;
    int Vez;
    int Linha;
};
struct table{
	int matrizTabelaVerdade[MAX_COMBINACOES][MAX_ENTRADA];
};

struct portaLogica porta[MAX_PORTA_LOGICA];
struct conector plug[MAX_CONECTOR];
struct input entrada[MAX_ENTRADA];
struct output saida[MAX_SAIDA];
struct table table;
struct numeroContador n;

int resolverPorta(int tipo, int x, int y){
    switch(tipo){
        case AND:
        return x&y;
        break;

        case OR:
        return x|y;
        break;

        case NOT:
        return !x;
        break;

        case XOR:
        return x^y;
        break;

        case NOR:
        return !(x|y);
        break;

        case NAND:
        return !(x&y);
        break;
    }
}
int tabelaVerdade(int nInput){
    char vet[10];
    int entrada;
    int j, l=0;
    for(entrada = 0; entrada < (pow(2, nInput)); entrada++){
        vet[0] = (entrada & 1  )?1:0;      
        vet[1] = (entrada & 2  )?1:0;      
        vet[2] = (entrada & 4  )?1:0;
        vet[3] = (entrada & 8  )?1:0;
        vet[4] = (entrada & 16 )?1:0;
        vet[5] = (entrada & 32 )?1:0;
        vet[6] = (entrada & 64 )?1:0;
        vet[7] = (entrada & 128)?1:0;
        vet[8] = (entrada & 256)?1:0;
        vet[9] = (entrada & 512)?1:0;
      
        for(j = 0; j < nInput; j++){
            table.matrizTabelaVerdade[entrada][l] = vet[j];
            l++;
        }l=0;
    }
}
int iniciarDados(int nEntrada, int nConector, int nPorta, int nLinha){
    int k, l, m, n, o;
    int coluna = 0;

	for(k = 0; k < nConector; k++){
		plug[k].valor = 5;
	}

	for(l = 0; l < nPorta; l++){
		porta[l].estado = 0;
	}
	
	for(m = 0; m < nEntrada; m++){
		entrada[m].valor = table.matrizTabelaVerdade[nLinha][coluna];
		coluna++;
	}

	for(n = 0; n < nEntrada; n++){
		for(o = 0; o < nConector; o++){
			if(entrada[n].no == plug[o].no){
				plug[o].valor = entrada[n].valor;
			}	
		}
	}	return 0;
}
int imprimirTela(int nEntrada, int nSaida){
    int p, q, r, s, t, u, x, y, z;
    char espaco[8]="";
    char vazio[8]="";
    int tamanho = 0;
      
    for(x = 0; x < nEntrada; x++){
        tamanho += strlen(entrada[x].representacao);
    }
    for(y = 0; y < nSaida; y++){
        tamanho += strlen(saida[y].representacao);
    }

    if(n.Vez == 0){
        for(p = tamanho + nEntrada*3 + nSaida*3 + 3; p > 0; p--){
            printf("-");
        }
        printf("\n"); printf("Entrada");
        for(z = 0; z < (tamanho + nEntrada*3 + nSaida*3 - 9); z++){
            printf(" ");
        }
        printf("Saida\n");
        for(p = tamanho + nEntrada*3 + nSaida*3 + 3; p > 0; p--){
            printf("-");
        }
        printf("\n");
        for(q = 0; q < nEntrada; q++){
            printf("| %s ", entrada[q].representacao);
        }
        printf("|-");
        for(r = 0; r < nSaida; r++){
            printf("| %s ", saida[r].representacao);
        }
        printf("|\n");
        for(s = tamanho + nEntrada*3 + nSaida*3 + 3; s > 0; s--){
            printf("-");
        }
        printf("\n");
    }

    for(t = 0; t < nEntrada; t++){
        for(int z = 0; z < strlen(entrada[t].representacao); z++){
            strcat(espaco, " ");
        }
        printf("|%s%d ",espaco, entrada[t].valor);strcpy(espaco, vazio);
    }

        printf("|-");
    for(u = 0; u < nSaida; u++){
        for(int z = 0; z < strlen(saida[u].representacao); z++){
            strcat(espaco, " ");
        }
        printf("|%s%d ", espaco, saida[u].valor);strcpy(espaco, vazio);
    }
        printf("|\n"); n.Vez++;
}


int salvarPlug(int inputNo, int nConector){
	for(int t = 0; t < nConector; t++){
		if(inputNo == plug[t].no){
			return 1;
		}
	}	
	plug[nConector].no = inputNo;
	n.Conector++;
	return 0;
}
int main(){
	n.Conector = 0; n.Entrada = 0; n.Porta = 0; n.Saida = 0; n.Linha = 0; n.Vez = 0;
    	int resultado = 0;
    	int a, b, c, d, e, f, g, h, i, j; 
	char nomeCircuito[50]; 
	char dirArquivo[100]; 
	char tipo[10]; 

	printf("Insira o local do arquivo: ");
	fgets(dirArquivo, 100, stdin);
	for(a = 0; a < 99; a++){
		if(dirArquivo[a] == 10){
			dirArquivo[a] = 0;
			break;
		}
	}

	FILE *arquivo = fopen(dirArquivo, "r");
    
	if(arquivo == NULL){ 
		printf("Problemas na abertura do arquivo\n");
     	return 0;
	}

	while(fscanf(arquivo, "%s", tipo) != EOF){
		
		if(!strcmp(tipo, "AND")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
            		salvarPlug(porta[n.Porta].input[0], n.Conector);
            		salvarPlug(porta[n.Porta].input[1], n.Conector);
			salvarPlug(porta[n.Porta].output, n.Conector);
			porta[n.Porta].tipo = AND; n.Porta++;
		}else if(!strcmp(tipo, "OR")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
            		salvarPlug(porta[n.Porta].input[0], n.Conector);
            		salvarPlug(porta[n.Porta].input[1], n.Conector);
            		salvarPlug(porta[n.Porta].output, n.Conector);
			porta[n.Porta].tipo = OR; n.Porta++;
		}else if(!strcmp(tipo, "NOT")){
			fscanf(arquivo, "%d %d", &porta[n.Porta].input[0], &porta[n.Porta].output);
            		salvarPlug(porta[n.Porta].input[0], n.Conector);
            		salvarPlug(porta[n.Porta].output, n.Conector);
			porta[n.Porta].tipo = NOT; n.Porta++;
		}else if(!strcmp(tipo, "NAND")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
			salvarPlug(porta[n.Porta].input[0], n.Conector);
            		salvarPlug(porta[n.Porta].input[1], n.Conector);
            		salvarPlug(porta[n.Porta].output, n.Conector);
			porta[n.Porta].tipo = NAND; n.Porta++;
		}else if(!strcmp(tipo, "NOR")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
			salvarPlug(porta[n.Porta].input[0], n.Conector);
            		salvarPlug(porta[n.Porta].input[1], n.Conector);
            		salvarPlug(porta[n.Porta].output, n.Conector);
			porta[n.Porta].tipo = NOR; n.Porta++;
		}else if(!strcmp(tipo, "XOR")){
			fscanf(arquivo, "%d %d %d", &porta[n.Porta].input[0], &porta[n.Porta].input[1], &porta[n.Porta].output);
			salvarPlug(porta[n.Porta].input[0], n.Conector);
            		salvarPlug(porta[n.Porta].input[1], n.Conector);
            		salvarPlug(porta[n.Porta].output, n.Conector);
            		porta[n.Porta].tipo = XOR; n.Porta++;
		}else if(!strcmp(tipo, "INPUT")){
			fscanf(arquivo, "%d %s", &entrada[n.Entrada].no, entrada[n.Entrada].representacao);
            		salvarPlug(entrada[n.Entrada].no, n.Conector);
			n.Entrada++;
		}else if(!strcmp(tipo, "OUTPUT")){
			fscanf(arquivo, "%d %s", &saida[n.Saida].no, saida[n.Saida].representacao);
            		salvarPlug(saida[n.Saida].no, n.Conector);
            		n.Saida++;
		}else if(!strcmp(tipo, "CIRCUIT")){
			fgets(nomeCircuito, 50, arquivo);
		}else{
			printf("O arquivo aberto contém erro de escrita, por favor, verificar e corrigir.\n");
            		exit(0);
		}
	}
	fclose(arquivo); 
    	tabelaVerdade(n.Entrada); 
    	iniciarDados(n.Entrada, n.Conector, n.Porta, n.Linha);
	printf("\nCIRCUITO: %s\n", nomeCircuito);
	
    do{

        for(b = 0; b < n.Porta; b++){
            if(porta[b].estado == 0){
                if(porta[b].tipo == NOT){
                    for(c = 0; c < n.Conector; c++){
                        if(porta[b].input[0] == plug[c].no && plug[c].valor != 5){
                            for(d = 0; d < n.Conector; d++){       
                                if(porta[b].output == plug[d].no){
                                    plug[d].valor = resolverPorta(porta[b].tipo, plug[c].valor, 0);
                                    porta[b].estado = 1;
                                    break;
                                }
                            }
                        }
                    }
                }else{
                    for(e = 0; e < n.Conector; e++){
                        for(f = 0; f < n.Conector; f++){
                            if(porta[b].input[0] == plug[e].no && porta[b].input[1] == plug[f].no && plug[e].valor != 5 && plug[f].valor != 5){
                                for(g = 0; g < n.Conector; g++){
                                    if(porta[b].output == plug[g].no){
                                        plug[g].valor = resolverPorta(porta[b].tipo, plug[e].valor, plug[f].valor);
                                        porta[b].estado = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
	
        for(h = 0; h < n.Porta; h++){ 
            if(porta[h].estado == 0){
                resultado++; break;
            }
        }
        if(resultado == 0){ 
            for(i = 0; i < n.Saida; i++){
                for(j = 0; j < n.Conector; j++){
                    if(saida[i].no == plug[j].no){
                        saida[i].valor = plug[j].valor;
                    }
                }
            }
            imprimirTela(n.Entrada, n.Saida);
            n.Linha++; resultado = 0;
            iniciarDados(n.Entrada, n.Conector, n.Porta, n.Linha);                                      
        }else{
            resultado = 0;
        }
    }while(n.Linha < pow(2, n.Entrada));
}
