#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <string.h>
#include "tad.h"

void inicializaProcessador(tpDesc &listaProcessador, int quant) {
	inicializarDesc(listaProcessador);
	for(int i = 0; i < quant; i++) {
		inserirProcessador(listaProcessador);
	}
}

int main()
{
	telacheia();
	Sleep(1000);
	int isEscPressed = 0, key ,i =0, ut = 0, retomadaExist = 0, adcp1, adcp2, adcp3, adcp4, rmvp1, rmvp2, rmvp3, rmvp4;
	tpReg lido;
	tpDesc descritor;
	tpProcessador *processador = new tpProcessador;
	inicializaProcessador(descritor, 4);
	FILE *ptrArq = fopen("retomada.txt", "r+");
	if (ptrArq == NULL) {
		fclose(ptrArq);
		ptrArq = fopen("listaProcessos.txt", "r+");
	}
	else {
		fscanf(ptrArq, "%d;%d;%d;%d;%d;%d", &descritor.quantI, &descritor.quantL, &descritor.quantD, &descritor.quantGDI, &descritor.quantGDE, &ut);
		fscanf(ptrArq, "%d;%d;%d;%d", &retornaProcessador(descritor, 1) -> listaProcesso.quant, &retornaProcessador(descritor, 2) -> listaProcesso.quant, &retornaProcessador(descritor, 3) -> listaProcesso.quant, &retornaProcessador(descritor, 4) -> listaProcesso.quant);
		retomadaExist = 1;
	}
	
	if(ptrArq == NULL)
		printf("Erro ao abrir o arquivo!");
	else {
		textcolor(8);
		retangulo(1, 1, 121, 35); // Bordas
		fscanf(ptrArq, "%d;%[^;];%[^;];%d", &lido.processador, &lido.nomeArq, &lido.nomeProcesso, &lido.ut);
		desenhaprocessador(8, WHITE, 1);
		desenhaprocessador(8, WHITE, 2);
		desenhaprocessador(8, WHITE, 3);
		desenhaprocessador(8, WHITE, 4);
		textcolor(WHITE);
		proxprocessocaixa();
		proxprocesso(ftell(ptrArq));
		while (!feof(ptrArq) && !isEscPressed) 
		{	
			textcolor(WHITE);
			tempocaixa(ut);
			adcp1 = adcp2 = adcp3 = adcp4 = rmvp1 = rmvp2 = rmvp3 = rmvp4 = 0;
	        if (kbhit()) {
	            key = getch();
	            
	            if (key == 27) {
	                isEscPressed = 1;
	            }
	        }
	        if(!isEscPressed) 
	        {
	        	if (ut % 2 == 0 && !feof(ptrArq)) {
	        		proxprocesso(ftell(ptrArq));
	        		if(strcmp(lido.nomeProcesso,"Gravar Dispositivo Interno") == 0)
	        			lido.prioridade = 1;
					if(strcmp(lido.nomeProcesso, "Gravar Dispositivo Externo") == 0)
						lido.prioridade = 2;
		        	if(strcmp(lido.nomeProcesso, "Deletar") == 0)
		        		lido.prioridade = 3;
		        	if(strcmp(lido.nomeProcesso, "Ler") == 0) 
		        		lido.prioridade = 4;
		        	if(strcmp(lido.nomeProcesso, "Imprimir") == 0)
		        		lido.prioridade = 5;
					
		        	// Adiciona Processo
		        	if(lido.processador == 1) {
		        		inserirProcessoOrdenado(descritor.inicio -> listaProcesso, lido);
		        		desenhaprocessador(10, 15, 1);
		        		adcp1++;
		        		gotoxy(5, 38);
		        		textcolor(10);
		        		printf("Adicionado!");
		        		gotoxy(5, 39);
		        		fprioridade(lido.prioridade);
		        		printf("%s", lido.nomeArq);
					}
			        if(lido.processador == 2) {
			        	inserirProcessoOrdenado(descritor.inicio -> prox -> listaProcesso, lido);
			        	desenhaprocessador(10, 15, 2);
			        	adcp2++; 
			        	gotoxy(36, 38);
		        		textcolor(10);
		        		printf("Adicionado!");
		        		gotoxy(36, 39);
		        		fprioridade(lido.prioridade);
		        		printf("%s", lido.nomeArq);
					}
					if(lido.processador == 3) {
						inserirProcessoOrdenado(descritor.inicio -> prox -> prox -> listaProcesso, lido);
						desenhaprocessador(10, 15, 3);
						adcp3++;
						gotoxy(65, 38);
		        		textcolor(10);
		        		printf("Adicionado!");
		        		gotoxy(65, 39);
		        		fprioridade(lido.prioridade);
		        		printf("%s", lido.nomeArq);
					}
		        		
					if(lido.processador == 4) {
						inserirProcessoOrdenado(descritor.fim -> listaProcesso, lido);
						desenhaprocessador(10, 15, 4);
						adcp4++;
						gotoxy(96, 38);
		        		textcolor(10);
		        		printf("Adicionado!");
		        		gotoxy(96, 39);
		        		fprioridade(lido.prioridade);
		        		printf("%s", lido.nomeArq);
					}
				}
				infoscaixa(descritor);
				exibeListaProcesso(retornaProcessador(descritor, 1) -> listaProcesso.inicio, retornaProcessador(descritor, 1) -> listaProcesso.quant_atual, 1);
				exibeListaProcesso(retornaProcessador(descritor, 2) -> listaProcesso.inicio, retornaProcessador(descritor, 2) -> listaProcesso.quant_atual, 2);
				exibeListaProcesso(retornaProcessador(descritor, 3) -> listaProcesso.inicio, retornaProcessador(descritor, 3) -> listaProcesso.quant_atual, 3);
				exibeListaProcesso(retornaProcessador(descritor, 4) -> listaProcesso.inicio, retornaProcessador(descritor, 4) -> listaProcesso.quant_atual, 4);
				
				//Remover processo
				if (!listaProcessosVazia(retornaProcessador(descritor, 1) -> listaProcesso)) {
					retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.ut--;
					if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.ut == 0) {
						rmvp1++;
						gotoxy(5, 40);
		        		textcolor(RED);
		        		printf("Sera removido:");
		        		gotoxy(5, 41);
		        		fprioridade(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade);
		        		printf("%s", retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.nomeArq);
		        		
		        		if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 1)
	        				descritor.quantGDI++;
						if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 2)
							descritor.quantGDE++;
			        	if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 3)
			        		descritor.quantD++;
			        	if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 4)
			        		descritor.quantL++;
			        	if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 5)
			        		descritor.quantI++;
		        		
						removido(1);
						retirarInicioListaProcessos(retornaProcessador(descritor, 1) -> listaProcesso);
					}
				}
				
				if (!listaProcessosVazia(retornaProcessador(descritor, 2) -> listaProcesso)) {
					retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.ut--;
					if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.ut == 0) {
						rmvp2++;
						gotoxy(36, 40);
		        		textcolor(RED);
		        		printf("Sera removido:");
		        		gotoxy(36, 41);
		        		fprioridade(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade);
		        		printf("%s", retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.nomeArq);
		        		
		        		if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 1)
	        				descritor.quantGDI++;
						if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 2)
							descritor.quantGDE++;
			        	if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 3)
			        		descritor.quantD++;
			        	if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 4)
			        		descritor.quantL++;
			        	if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 5)
			        		descritor.quantI++;
		        		
						removido(2);
						retirarInicioListaProcessos(retornaProcessador(descritor, 2) -> listaProcesso);
					}
				}
				
				if (!listaProcessosVazia(retornaProcessador(descritor, 3) -> listaProcesso)) {
					retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.ut--;
					if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.ut == 0){
						rmvp3++;
						gotoxy(65, 40);
		        		textcolor(RED);
		        		printf("Sera removido:");
		        		gotoxy(65, 41);
		        		fprioridade(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade);
		        		printf("%s", retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.nomeArq);
		        		
		        		if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 1)
	        				descritor.quantGDI++;
						if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 2)
							descritor.quantGDE++;
			        	if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 3)
			        		descritor.quantD++;
			        	if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 4)
			        		descritor.quantL++;
			        	if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 5)
			        		descritor.quantI++;
		        		
						removido(3);
						retirarInicioListaProcessos(retornaProcessador(descritor, 3) -> listaProcesso);
					}
				}
				
				if (!listaProcessosVazia(retornaProcessador(descritor, 4) -> listaProcesso)) {
					retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.ut--;
					if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.ut == 0) {
						rmvp4++;
						gotoxy(96, 40);
		        		textcolor(RED);
		        		printf("Sera removido:");
		        		gotoxy(96, 41);
		        		fprioridade(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade);
		        		printf("%s", retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.nomeArq);
		        		
		        		if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 1)
	        				descritor.quantGDI++;
						if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 2)
							descritor.quantGDE++;
			        	if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 3)
			        		descritor.quantD++;
			        	if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 4)
			        		descritor.quantL++;
			        	if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 5)
			        		descritor.quantI++;
		        		
						removido(4);
						retirarInicioListaProcessos(retornaProcessador(descritor, 4) -> listaProcesso);
					}
				}
				
				ut++;
				tempo(900);
				if (ut % 2 == 0 && !feof(ptrArq))
				fscanf(ptrArq, "%d;%[^;];%[^;];%d", &lido.processador, &lido.nomeArq, &lido.nomeProcesso, &lido.ut);
				if (adcp1 || adcp2 || adcp3 || adcp4 || rmvp1 || rmvp2 || rmvp3 || rmvp4) {
					if (adcp1) {
						desenhaprocessador(8, WHITE, 1);
						gotoxy(5, 38);
		        		printf("                              ");
		        		gotoxy(5, 39);
		        		printf("                              ");
					}
						
					if(adcp2) {
						desenhaprocessador(8, WHITE, 2);
						gotoxy(36, 38);
		        		printf("                               ");
		        		gotoxy(36, 39);
		        		printf("                               ");
					}
					if(adcp3) {
						desenhaprocessador(8, WHITE, 3);
						gotoxy(65, 38);
		        		printf("                                ");
		        		gotoxy(65, 39);
		        		printf("                                ");
					}
					if(adcp4) {
						desenhaprocessador(8, WHITE, 4);
						gotoxy(96, 38);
		        		printf("                               ");
		        		gotoxy(96, 39);
		        		printf("                               ");
					} 
					if (rmvp1) {
						desenhaprocessador(8, WHITE, 1);
						gotoxy(5, 40);
		        		printf("                               ");
		        		gotoxy(5, 41);
		        		printf("                               ");
					}
					if (rmvp2) {
						desenhaprocessador(8, WHITE, 2);
						gotoxy(36, 40);
		        		printf("                               ");
		        		gotoxy(36, 41);
		        		printf("                               ");
					}
					if (rmvp3) {
						desenhaprocessador(8, WHITE, 3);
						gotoxy(65, 40);
		        		printf("                               ");
		        		gotoxy(65, 41);
		        		printf("                               ");
					}
					if (rmvp4) {
						desenhaprocessador(8, WHITE, 4);
						gotoxy(96, 40);
		        		printf("                                ");
		        		gotoxy(96, 41);
		        		printf("                                ");
					}
				}
			}
    	}
    	
    	textcolor(WHITE);
		proxprocessocaixa();
    	
    	while(feof(ptrArq) && !isEscPressed && !descVazio(descritor)) {
    		adcp1 = adcp2 = adcp3 = adcp4 = rmvp1 = rmvp2 = rmvp3 = rmvp4 = 0;
    		textcolor(WHITE);
			tempocaixa(ut);
    		desenhaprocessador(8, WHITE, 1);
			desenhaprocessador(8, WHITE, 2);
			desenhaprocessador(8, WHITE, 3);
			desenhaprocessador(8, WHITE, 4);
    		infoscaixa(descritor);
			exibeListaProcesso(retornaProcessador(descritor, 1) -> listaProcesso.inicio, retornaProcessador(descritor, 1) -> listaProcesso.quant_atual, 1);
			exibeListaProcesso(retornaProcessador(descritor, 2) -> listaProcesso.inicio, retornaProcessador(descritor, 2) -> listaProcesso.quant_atual, 2);
			exibeListaProcesso(retornaProcessador(descritor, 3) -> listaProcesso.inicio, retornaProcessador(descritor, 3) -> listaProcesso.quant_atual, 3);
			exibeListaProcesso(retornaProcessador(descritor, 4) -> listaProcesso.inicio, retornaProcessador(descritor, 4) -> listaProcesso.quant_atual, 4);
			
			//Remover processo
			if (!listaProcessosVazia(retornaProcessador(descritor, 1) -> listaProcesso)) {
				retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.ut--;
				if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.ut == 0) {
					rmvp1++;
					gotoxy(5, 40);
	        		textcolor(RED);
	        		printf("Sera removido:");
	        		gotoxy(5, 41);
	        		fprioridade(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade);
	        		printf("%s", retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.nomeArq);
	        		
	        		if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 1)
        				descritor.quantGDI++;
					if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 2)
						descritor.quantGDE++;
		        	if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 3)
		        		descritor.quantD++;
		        	if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 4)
		        		descritor.quantL++;
		        	if(retornaProcessador(descritor, 1) -> listaProcesso.inicio -> reg.prioridade == 5)
		        		descritor.quantI++;
	        		
					removido(1);
					retirarInicioListaProcessos(retornaProcessador(descritor, 1) -> listaProcesso);
				}
			}
			
			if (!listaProcessosVazia(retornaProcessador(descritor, 2) -> listaProcesso)) {
				retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.ut--;
				if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.ut == 0) {
					rmvp2++;
					gotoxy(36, 40);
	        		textcolor(RED);
	        		printf("Sera removido:");
	        		gotoxy(36, 41);
	        		fprioridade(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade);
	        		printf("%s", retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.nomeArq);
	        		
	        		if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 1)
        				descritor.quantGDI++;
					if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 2)
						descritor.quantGDE++;
		        	if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 3)
		        		descritor.quantD++;
		        	if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 4)
		        		descritor.quantL++;
		        	if(retornaProcessador(descritor, 2) -> listaProcesso.inicio -> reg.prioridade == 5)
		        		descritor.quantI++;
	        		
					removido(2);
					retirarInicioListaProcessos(retornaProcessador(descritor, 2) -> listaProcesso);
				}
			}
			
			if (!listaProcessosVazia(retornaProcessador(descritor, 3) -> listaProcesso)) {
				retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.ut--;
				if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.ut == 0){
					rmvp3++;
					gotoxy(65, 40);
	        		textcolor(RED);
	        		printf("Sera removido:");
	        		gotoxy(65, 41);
	        		fprioridade(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade);
	        		printf("%s", retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.nomeArq);
	        		
	        		if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 1)
        				descritor.quantGDI++;
					if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 2)
						descritor.quantGDE++;
		        	if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 3)
		        		descritor.quantD++;
		        	if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 4)
		        		descritor.quantL++;
		        	if(retornaProcessador(descritor, 3) -> listaProcesso.inicio -> reg.prioridade == 5)
		        		descritor.quantI++;
	        		
					removido(3);
					retirarInicioListaProcessos(retornaProcessador(descritor, 3) -> listaProcesso);
				}
			}
			
			if (!listaProcessosVazia(retornaProcessador(descritor, 4) -> listaProcesso)) {
				retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.ut--;
				if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.ut == 0) {
					rmvp4++;
					gotoxy(96, 40);
	        		textcolor(RED);
	        		printf("Sera removido:");
	        		gotoxy(96, 41);
	        		fprioridade(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade);
	        		printf("%s", retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.nomeArq);
	        		
	        		if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 1)
	        			descritor.quantGDI++;
					if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 2)
						descritor.quantGDE++;
		        	if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 3)
		        		descritor.quantD++;
		        	if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 4)
		        		descritor.quantL++;
		        	if(retornaProcessador(descritor, 4) -> listaProcesso.inicio -> reg.prioridade == 5)
		        		descritor.quantI++;
	        		
					removido(4);
					retirarInicioListaProcessos(retornaProcessador(descritor, 4) -> listaProcesso);
				}
			}
			tempo(900);
			ut++;
			if (adcp1 || adcp2 || adcp3 || adcp4 || rmvp1 || rmvp2 || rmvp3 || rmvp4) {
				if (adcp1) {
					desenhaprocessador(8, WHITE, 1);
					gotoxy(5, 38);
	        		printf("                              ");
	        		gotoxy(5, 39);
	        		printf("                              ");
				}
					
				if(adcp2) {
					desenhaprocessador(8, WHITE, 2);
					gotoxy(36, 38);
	        		printf("                               ");
	        		gotoxy(36, 39);
	        		printf("                               ");
				}
				if(adcp3) {
					desenhaprocessador(8, WHITE, 3);
					gotoxy(65, 38);
	        		printf("                                ");
	        		gotoxy(65, 39);
	        		printf("                                ");
				}
				if(adcp4) {
					desenhaprocessador(8, WHITE, 4);
					gotoxy(96, 38);
	        		printf("                               ");
	        		gotoxy(96, 39);
	        		printf("                               ");
				} 
				if (rmvp1) {
					desenhaprocessador(8, WHITE, 1);
					gotoxy(5, 40);
	        		printf("                               ");
	        		gotoxy(5, 41);
	        		printf("                               ");
				}
				if (rmvp2) {
					desenhaprocessador(8, WHITE, 2);
					gotoxy(36, 40);
	        		printf("                               ");
	        		gotoxy(36, 41);
	        		printf("                               ");
				}
				if (rmvp3) {
					desenhaprocessador(8, WHITE, 3);
					gotoxy(65, 40);
	        		printf("                               ");
	        		gotoxy(65, 41);
	        		printf("                               ");
				}
				if (rmvp4) {
					desenhaprocessador(8, WHITE, 4);
					gotoxy(96, 40);
	        		printf("                                ");
	        		gotoxy(96, 41);
	        		printf("                                ");
				}
			}
    	}
    	
    	if (!feof(ptrArq) && ut > 0) {
    		FILE *ptrRetomada = fopen("temp.txt", "w+");
    		
	    	if (ptrRetomada == NULL) {
		    	printf("Erro ao abrir o arquivo temp.txt\n");
		    	return 1;
			}
			fprintf(ptrRetomada, "%d;%d;%d;%d;%d;%d\n", descritor.quantI, descritor.quantL, descritor.quantD, descritor.quantGDI, descritor.quantGDE, ut);
			fprintf(ptrRetomada, "%d;%d;%d;%d\n", retornaProcessador(descritor, 1) -> listaProcesso.quant, retornaProcessador(descritor, 2) -> listaProcesso.quant, retornaProcessador(descritor, 3) -> listaProcesso.quant, retornaProcessador(descritor, 4) -> listaProcesso.quant);
	    	while(!descVazio(descritor)) {	
	    		if (!listaProcessosVazia(retornaProcessador(descritor, 1) -> listaProcesso)) {
	    			lido = retirarInicioListaProcessos(retornaProcessador(descritor, 1) -> listaProcesso);
	    			fprintf(ptrRetomada, "%d;%s;%s;%d\n", lido.processador, lido.nomeArq, lido.nomeProcesso, lido.ut);
				}
				if (!listaProcessosVazia(retornaProcessador(descritor, 2) -> listaProcesso)) {
	    			lido = retirarInicioListaProcessos(retornaProcessador(descritor, 2) -> listaProcesso);
	    			fprintf(ptrRetomada, "%d;%s;%s;%d\n", lido.processador, lido.nomeArq, lido.nomeProcesso, lido.ut);
				}
				if (!listaProcessosVazia(retornaProcessador(descritor, 3) -> listaProcesso)) {
	    			lido = retirarInicioListaProcessos(retornaProcessador(descritor, 3) -> listaProcesso);
	    			fprintf(ptrRetomada, "%d;%s;%s;%d\n", lido.processador, lido.nomeArq, lido.nomeProcesso, lido.ut);
				}
				if (!listaProcessosVazia(retornaProcessador(descritor, 4) -> listaProcesso)) {
	    			lido = retirarInicioListaProcessos(retornaProcessador(descritor, 4) -> listaProcesso);
	    			fprintf(ptrRetomada, "%d;%s;%s;%d\n", lido.processador, lido.nomeArq, lido.nomeProcesso, lido.ut);
				}
			}
			
			fscanf(ptrArq, "%d;%[^;];%[^;];%d", &lido.processador, &lido.nomeArq, &lido.nomeProcesso, &lido.ut);
			while(!feof(ptrArq)) {
				fprintf(ptrRetomada, "%d;%s;%s;%d\n", lido.processador, lido.nomeArq, lido.nomeProcesso, lido.ut);
				fscanf(ptrArq, "%d;%[^;];%[^;];%d", &lido.processador, &lido.nomeArq, &lido.nomeProcesso, &lido.ut);
			}
			
			fclose(ptrRetomada);
			fclose(ptrArq);
			remove("retomada.txt");
			rename("temp.txt", "retomada.txt");
		}
		if (feof(ptrArq) && retomadaExist == 1) {
			fclose(ptrArq);
			remove("retomada.txt");
		}
		else {
			fclose(ptrArq);
		}
	}
	
    moldurafinal(descritor, ut);
    textcolor(8);
    gotoxy(20,37);
    return 0;
}
