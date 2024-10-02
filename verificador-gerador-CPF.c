#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int menu(){
	int opt;
	printf("====================\n");
	printf("\tCPF\n");
	printf("====================\n");
	printf("1 - VERIFICAR CPF\n");
	printf("2 - GERAR UM CPF VÁLIDO\n");
	scanf(" %d", &opt);
	
	return opt;
	
}

void verifica_cpf(){
	char cpf[11];
	int i=0;
	system("clear");
	printf("=================================\n");
	printf("\tVERIFICADOR DE CPF\n");
	printf("=================================\n");
	
	printf("Informe o CPF (apenas os números): ");
	scanf(" %s", cpf);
	
	system("clear");
	
	int confirmacao=0;
	
	//verificação do PRIMEIRO digito
	int tot=0, verif=10;
	for(i=0; i<9; i++){
		//coloco o - '0' para transformar um char em int
		int n = cpf[i] - '0';
		
		tot += verif*n;
		verif--;
		
	}
	int resto = tot%11;
	
	if(resto < 2 && cpf[9] - '0' == 0){
		confirmacao++;
	}else if(resto >= 2 && cpf[9] - '0' == 11-resto){
		confirmacao++;
	}
	
	
	//verificacao do SEGUNDO digito
	verif = 11;
	tot = 0;
	for(i=0; i<10; i++){
		int n = cpf[i] - '0';
		
		tot += verif*n;
		verif--;	
	}
	resto = tot % 11;
	
	if(resto < 2 && cpf[10] - '0' == 0){
		confirmacao++;
	}else if(resto >= 2 && cpf[10] - '0' == 11-resto){
		confirmacao++;
	}
	
	int tamanho = strlen(cpf);
	
	if(tamanho == 11){
		for(i=0; i<11; i++){
			printf("%c", cpf[i]);
			if(i == 2 || i == 5)
				printf(".");
			if(i == 8)
				printf("-");	
		}
	}else{
		printf("ERRO! Quantidade de números errada!\nUm CPF deve conter 11 números!");
		exit(0);
	}
	
	if(confirmacao == 2)
		printf("\nÉ UM CPF VÁLIDO!");
	else
		printf("\nNÃO É UM CPF VÁLIDO!");
}

//funcao de gerar cpf
void gerador_cpf(){
	char cpf[11];
	int n;
	
	for(int i=0; i<9; i++){
		n = 0 + rand()%(9-0+1);
		cpf[i] = n + '0';
	}
	
	//gerando primeiro digito
	int tot=0, verif=10;
	for(int i=0; i<9; i++){
		//coloco o - '0' para transformar um char em int
		int n = cpf[i] - '0';
		
		tot += verif*n;
		verif--;
		
	}
	int resto = tot%11;
	
	if(resto < 2){
		cpf[9] = '0';
	}else if(resto >= 2){
		cpf[9] = 11-resto + '0';
	}
	
	//gerando segundo digito
	tot=0;
	verif=11;
	for(int i=0; i<10; i++){
		//coloco o - '0' para transformar um char em int
		int n = cpf[i] - '0';
		
		tot += verif*n;
		verif--;
		
	}
	resto = tot%11;
	
	if(resto < 2){
		cpf[10] = '0';
	}else if(resto >= 2){
		cpf[10] = 11-resto + '0';
	}
	
	//mostrando o cpf gerado na tela
	system("clear");
	printf("CPF GERADO COM SUCESSO! \n\n");
	printf("Sem pontuação: ");
	for(int i=0; i<11; i++){
		printf("%c", cpf[i]);
	}
	printf("\nCom pontuação: ");
	for(int i=0; i<11; i++){
		printf("%c", cpf[i]);
		if(i==2 || i==5)
			printf(".");
		if(i==8)
			printf("-");
	}
	
}

int main(){
	srand(time(NULL));
	switch(menu()){
		case 1:
			verifica_cpf();
			break;
		case 2:
			gerador_cpf();
			break;
		
	}
	
	return 0;
}
