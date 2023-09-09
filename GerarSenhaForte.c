#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 8
#define MAX 16

int main(){
	srand(time(NULL));
	system("Cls");
	
	char senha[20];
	int contSenhas=0;

	do{
		int t = MIN + rand()%(MAX-MIN+1);
		
		//geração dos caracteres
		for(int i=0; i<t; i++)
			senha[i] = '!' + rand()%('~'-'!'+1);	
		senha[t] = 0;

		int validacoes =0;
		
		//validacoes
		//caractere especial
		for(int i=0; i<t; i++)
			if (senha[i]>='!' && senha[i]<='/'){
				validacoes++;
				break;
			}
		
		if(validacoes==0)
			continue;
		
		//numerico
		for(int i=0; i<t; i++)
			if (senha[i]>='0' && senha[i]<='9'){
				validacoes++;
				break;
			}
		
		if(validacoes==1)
			continue;

		//minusculo
		for(int i=0; i<t; i++)
			if (senha[i]>='a' && senha[i]<='z'){
				validacoes++;
				break;
			}
		
		if(validacoes==2)
			continue;

		//maiusculo
		for(int i=0; i<t; i++)
			if (senha[i]>='A' && senha[i]<='Z'){
				validacoes++;
				break;
			}
		
		if(validacoes==3)
			continue;

		printf("Senha: %s\n",senha);
		contSenhas++;

	}while(contSenhas < 10);
	
}
