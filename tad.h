struct tpReg {
	int ut, prioridade, processador;
	char nomeProcesso[40], nomeArq[40];
};

struct tpProcesso {
	tpReg reg;
	tpProcesso *prox, *ant;
};

struct tpDescProcessos {
	tpProcesso *inicio, *fim;
	int quant, quant_atual;
};

struct tpProcessador {
	tpProcessador *prox, *ant;
	tpDescProcessos listaProcesso;
};

struct tpDesc {
	tpProcessador *inicio, *fim;
	int quant, quantI, quantGDE, quantGDI, quantD, quantL;
};


tpProcesso *novoProcesso(tpReg registro) {
	tpProcesso *processo;
	processo = new tpProcesso;
	
	processo->reg = registro;
	processo->prox = processo->ant = NULL;

	return processo;
}

void inicializarListaProcesso(tpDescProcessos &listaProcesso) {
	listaProcesso.fim = listaProcesso.inicio = NULL;
	listaProcesso.quant = listaProcesso.quant_atual = 0;
}

tpProcessador *novoProcessador() {
	tpProcessador *processador;
	processador = new tpProcessador;
	
	processador->prox = processador->ant = NULL;
	inicializarListaProcesso(processador->listaProcesso);
	
	return processador;
}

void inicializarDesc(tpDesc &descritor) {
	descritor.fim = descritor.inicio = NULL;
	descritor.quant = descritor.quantD = descritor.quantGDE = descritor.quantI = descritor.quantGDI = descritor.quantL = 0;
}

tpReg retirarInicioListaProcessos(tpDescProcessos &listaProcessos) {
	listaProcessos.quant++;
	tpReg removido;
	tpProcesso *aux;
	removido = listaProcessos.inicio->reg;
	
	aux = listaProcessos.inicio;
	listaProcessos.inicio = listaProcessos.inicio->prox;
	
	// Verifica se a lista n�o ficou vazia
	if(listaProcessos.inicio != NULL)
		listaProcessos.inicio->ant = NULL;
	
	listaProcessos.quant_atual--;
	delete(aux);
	return removido;
}

tpReg elementoInicioListaProcessos(tpDescProcessos listaProcessos) {
	return listaProcessos.inicio->reg;
}

tpReg elementoFinalListaProcessos(tpDescProcessos listaProcessos) {
	return listaProcessos.fim->reg;
}

char listaProcessosVazia(tpDescProcessos listaProcessos) {
	return listaProcessos.inicio == NULL;
}

void inserirProcessoOrdenado(tpDescProcessos &listaProcessos, tpReg registro) {
	tpProcesso *processo, *processoAux;
	processo = novoProcesso(registro);
	
	if(listaProcessos.inicio == NULL) {
		listaProcessos.inicio = listaProcessos.fim = processo;
	}
	else {
		// Insere processo no final
		listaProcessos.fim->prox = processo;
		processo->ant = listaProcessos.fim;
		listaProcessos.fim = processo;
		
		while(processo->ant != NULL && processo->reg.prioridade < processo->ant->reg.prioridade) {
			
			// Troca final
			if(processo->prox == NULL) {
				// Troca inicio
				if(processo->ant->ant == NULL) {
					processo->ant->prox = NULL;
					processo->prox = processo->ant;
					processo->ant->ant = processo;
					processo->ant = NULL;
					listaProcessos.inicio = processo;
				}
				else {
					processo->ant->ant->prox = processo;
					processo->ant->prox = NULL;
					processoAux = processo->ant->ant;
					processo->ant->ant = processo;
					processo->prox = processo->ant;
					processo->ant = processoAux;
				}
				listaProcessos.fim = processo->prox;
			}
			// Troca apenas o inicio
			else if(processo->ant->ant == NULL) {
				processo->ant->prox = processo->prox;
				processo->prox->ant = processo->ant;
				processo->ant->ant = processo;
				processo->prox = processo->ant;
				processo->ant = NULL;
				listaProcessos.inicio = processo;	
			}
			// Troca comum
			else {
				processo->ant->ant->prox = processo;
				processo->prox->ant = processo->ant;
				processo->ant->prox = processo->prox;
				processo->prox = processo->ant;
				processo->ant = processo->ant->ant;
				processo->prox->ant = processo;
			}
		}
	}
	listaProcessos.quant_atual++;
}

void inserirProcessador(tpDesc &descritor) {
	tpProcessador *processador;
	processador = novoProcessador();

	if(descritor.inicio == NULL) {
		descritor.fim = descritor.inicio = processador;
	}
	else {
		descritor.fim->prox = processador;
		processador->ant = descritor.fim;
		descritor.fim = processador;
	}
	
	descritor.quant++;
}

tpProcessador *retornaProcessador(tpDesc listaProcessador, int numProcessador) {
	tpProcessador *processador = listaProcessador.inicio;
	for(int i = 1; i < numProcessador; i++) {
		processador = processador->prox;
	}
	return processador;
}

char descVazio(tpDesc descritor) {
	if (listaProcessosVazia(retornaProcessador(descritor, 1) -> listaProcesso) && listaProcessosVazia(retornaProcessador(descritor, 2) -> listaProcesso) && listaProcessosVazia(retornaProcessador(descritor, 3) -> listaProcesso) && listaProcessosVazia(retornaProcessador(descritor, 4) -> listaProcesso))
		return 1;
	else
		return 0;
}

// Desenhos
#define X_MAX 150
#define LINHAH 205
#define LINHAV 186
#define BORDASE 201
#define BORDASD 187
#define BORDAIE 200
#define BORDAID 188

void retangulo(int x, int y, int BASERETANGULO, int ALTURARETANGULO) {
	gotoxy(x, y);
	printf("%c", BORDASE);
	for(int i = 0; i < BASERETANGULO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c\n", BORDASD);
	
	for(int i = 0; i < ALTURARETANGULO; i++) {
		gotoxy(x, ++y);
		printf("%c", LINHAV);
		for(int j = 0; j < BASERETANGULO; j++)
			printf(" ");
		printf("%c\n", LINHAV);
	}
	
	gotoxy(x, ++y);
	printf("%c", BORDAIE);
	for(int i = 0; i < BASERETANGULO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c", BORDAID);
}

void fprioridade(int prioridade) {
	if (prioridade == 1)
		textcolor(12);
		else if (prioridade == 2)
			textcolor(MAGENTA);
			else if (prioridade == 3)
				textcolor(6);
				else if (prioridade == 4)
					textcolor(BLUE);
					else if (prioridade == 5)
						textcolor(CYAN);
}

void exibeListaProcesso(tpProcesso *listaProcesso, int qtde, int processador) {
	int y = 7, x, qtde_max = 0;
	x = (processador - 1) * 30 + 6;
	while(listaProcesso && qtde_max < 5) {
		fprioridade(listaProcesso->reg.prioridade);
		retangulo(x, y, 21, 3);
		gotoxy(x+2, y+1);
		if (strlen(listaProcesso->reg.nomeArq) > 16) {
			for (int i = 0; i < 16; i++)
				printf("%c", listaProcesso->reg.nomeArq[i]);
			printf("...");	
		}
		else
			printf("%s", listaProcesso -> reg.nomeArq);
		gotoxy(x+8, y+3);
		printf("UT: %d", listaProcesso -> reg.ut);
		listaProcesso = listaProcesso->prox;
		y+=5;
		qtde_max++;
		Sleep(50);
	}
	if(qtde_max == 5) {
		gotoxy(x + 9, 33);
		printf("[...]");	
	}
	textcolor(WHITE);
}

void quadrado(int x, int y, int TAMANHOQUADRADO) {
	gotoxy(x, y);
	printf("%c", BORDASE);
	for(int i = 0; i < TAMANHOQUADRADO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c\n", BORDASD);
	
	for(int i = 0; i < TAMANHOQUADRADO / 2; i++) {
		gotoxy(x, ++y);
		printf("%c", LINHAV);
		for(int j = 0; j < TAMANHOQUADRADO; j++)
			printf(" ");
		printf("%c\n", LINHAV);
	}
	
	gotoxy(x, ++y);
	printf("%c", BORDAIE);
	for(int i = 0; i < TAMANHOQUADRADO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c", BORDAID);
}

void telacheia() {
	keybd_event ( VK_MENU, 0x38, 0, 0 );
	keybd_event ( VK_SPACE, 0x39, 0, 0 );
	keybd_event(0x58,0,0,0);
	keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
	keybd_event ( VK_SPACE, 0x39, KEYEVENTF_KEYUP, 0 );
	keybd_event(0x58,0,KEYEVENTF_KEYUP,0);
}

void proxprocesso(int qtdeBits){
	tpReg reg;
	
	FILE *ptrArqP = fopen("retomada.txt", "r+");
	if (ptrArqP == NULL) {
		fclose(ptrArqP);
		ptrArqP = fopen("listaProcessos.txt", "r+");
	}
	fseek(ptrArqP, qtdeBits, 0);
	fscanf(ptrArqP, "%d;%[^;];%[^;];%d", &reg.processador, &reg.nomeArq, &reg.nomeProcesso, &reg.ut);
	
	gotoxy(130, 31);
	textcolor(WHITE);
	if(!feof(ptrArqP)) {
		printf("Processador: %d", reg.processador);
		if(stricmp(reg.nomeProcesso, "Imprimir") == 0)
			fprioridade(5);
			else if(stricmp(reg.nomeProcesso, "Ler") == 0)
				fprioridade(4);
				else if(stricmp(reg.nomeProcesso, "Deletar") == 0)
					fprioridade(3);
					else if(stricmp(reg.nomeProcesso, "Gravar dispositivo externo") == 0)
						fprioridade(2);
							if(stricmp(reg.nomeProcesso, "Gravar dispositivo interno") == 0)
							fprioridade(1);
		retangulo(127, 32, 18, 3);
		gotoxy(129, 33);
		if (strlen(reg.nomeArq) > 13) {
				for (int i = 0; i < 13; i++)
					printf("%c", reg.nomeArq[i]);
				printf("...");	
			}
		else
			printf("%s", reg.nomeArq);
		gotoxy(133, 34);
		printf("UT: %d", reg.ut);
	}
	textcolor(WHITE);
	fclose(ptrArqP);
}

void tempo(int tempo) {
	int x = 136;
	textcolor(10);
	for(int i = 0; i < 11; i++) {
		gotoxy(x, 2);
		printf("%c", 219);
		x++;
		Sleep(tempo/11);
	}
}

void removido(int processador) {
	int x = (processador - 1) * 30 + 4;
	textcolor(RED);
	retangulo(x + 2, 2, 21, 3);
	gotoxy(x + 7, 4);
	printf("Processador %d", processador);
}

void desenhacaixaprocessador (int corcaixa, int processador) {
	int x = (processador - 1) * 30 + 4;
	textcolor(corcaixa);
	retangulo(x + 2, 2, 21, 3); // Processador 1
	gotoxy(x + 7, 4);
	printf("Processador %d", processador);
}

void desenhaprocessador(int corborda, int corcaixa, int processador) {
	int x = (processador - 1) * 30 + 4;
	textcolor(corborda);
	retangulo(x, 4, 25, 31); // Processador 1
	desenhacaixaprocessador(corcaixa, processador);
}

void proxprocessocaixa () {
	retangulo(125, 28, 22, 8); //Prox Processo
	gotoxy(128, 29);
	printf("Proximo processo: ");
}

void tempocaixa(int ut) {
	retangulo(125, 1, 22, 1); //Tempo
	gotoxy(127, 2);
	printf("UT: ");
	gotoxy(131, 2);
	printf("%d", ut);
}

void infoscaixa(tpDesc descritor) {
	textcolor(8);
	retangulo(125, 4, 22, 22); //Infos
	gotoxy(134, 5);
	textcolor(WHITE);
	printf("Ajuda: ");
	gotoxy(129, 7);
	textcolor(CYAN);
	printf("Ciano: ");
	gotoxy(136, 7);
	textcolor(WHITE);
	printf("Imprimir");
	
	gotoxy(130, 8);
	textcolor(BLUE);
	printf("Azul: ");
	gotoxy(136, 8);
	textcolor(WHITE);
	printf("Ler");
	
	gotoxy(127, 9);
	textcolor(6);
	printf("Laranja: ");
	gotoxy(136, 9);
	textcolor(WHITE);
	printf("Deletar");
	
	gotoxy(130, 10);
	textcolor(MAGENTA);
	printf("Roxo: ");
	gotoxy(136, 10);
	textcolor(WHITE);
	printf("Gravar Ext.");
	
	gotoxy(127, 11);
	textcolor(12);
	printf("Vermel.: ");
	gotoxy(136, 11);
	textcolor(WHITE);
	printf("Gravar Int.");
	
	gotoxy(130, 14);
	printf("Quantidades:");
	gotoxy(128, 15);
	textcolor(CYAN);
	printf("Impressoes: %d\n", descritor.quantI);
	gotoxy(128, 16);
	textcolor(BLUE);
	printf("Leituras: %d\n", descritor.quantL);
	gotoxy(128, 17);
	textcolor(6);
	printf("Deletados: %d\n", descritor.quantD);
	gotoxy(128, 18);
	textcolor(MAGENTA);
	printf("Gravar Ext.: %d\n", descritor.quantGDE);
	gotoxy(128, 19);
	textcolor(12);
	printf("Gravar Int.: %d\n", descritor.quantGDI);
	
	textcolor(WHITE);
	gotoxy(130, 21);
	printf("Processadores:");
	gotoxy(128, 22);
	printf("Processador 1: %d\n", retornaProcessador(descritor, 1) -> listaProcesso.quant);
	gotoxy(128, 23);
	printf("Processador 2: %d\n", retornaProcessador(descritor, 2) -> listaProcesso.quant);
	gotoxy(128, 24);
	printf("Processador 3: %d\n", retornaProcessador(descritor, 3) -> listaProcesso.quant);
	gotoxy(128, 25);
	printf("Processador 4: %d\n", retornaProcessador(descritor, 4) -> listaProcesso.quant);
}

void retangulofinal(int x, int y, int BASERETANGULO, int ALTURARETANGULO) {
	gotoxy(x, y);
	printf("%c", BORDASE);
	for(int i = 0; i < BASERETANGULO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c\n", BORDASD);
	
	for(int i = 0; i < ALTURARETANGULO; i++) {
		Sleep(1);
		gotoxy(x, ++y);
		printf("%c", LINHAV);
		for(int j = 0; j < BASERETANGULO; j++)
			printf(" ", 219);
		printf("%c\n", LINHAV);
	}
	
	gotoxy(x, ++y);
	printf("%c", BORDAIE);
	for(int i = 0; i < BASERETANGULO; i++) {
		printf("%c", LINHAH);
	}
	printf("%c", BORDAID);
	gotoxy(52, 17);
	printf("SIMULACAO ENCERRADA");
}

void moldurafinal (tpDesc descritor, int ut) {
	textcolor(10);
	tempocaixa(ut);
	textcolor(GREEN);
	proxprocessocaixa();
	tempo(1000);

	desenhaprocessador(10, 15, 1);
	Sleep(50);
	desenhaprocessador(10, 15, 2);
	Sleep(50);
	desenhaprocessador(10, 15, 3);
	Sleep(50);
	desenhaprocessador(10, 15, 4);
	
	Sleep(500);
	textcolor(10);
	retangulofinal(1, 1, 121, 35); // Bordas
	
	Sleep(150);
	infoscaixa(descritor);
	Sleep(100);
}
