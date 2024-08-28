#include <stdio.h>
#include <stdlib.h>

/* Programa BEM SIMPLES que simula um menu de antendimento de uma 
 * Clinica Médica, fiz esse programa para treinar um pouco mais 
 * meu conhecimento em Lista Encadeada em Linguagem C. 
 * Nesse exemplo, uso Lista Simplesmente Encadeada.
 * Caso queira roda-lo no seu PC, recomendo que use 
 * uma distro Linux baseada em Debian*/

typedef struct Paciente{
	char nome[100], sexo;
	int idade, id;
	struct Paciente *prox;
	
}Paciente;

//funcao para imprimir avisos ao usuario
void imprimirAviso(char *aviso){
	system("clear");
	printf("%s\n", aviso);
	system("sleep 2");
	system("clear");
}

int menu(){
	int opt;
	system("clear");
	printf("  === GERENCIAMENTO DE PACIENTES ===\n\n");
	printf("1 - CADASTRAR NOVO PACIENTE\n");
	printf("2 - VER LISTA DE ORDEM DE ATENDIMENTO\n");
	printf("3 - ATENDER PROXIMO PACIENTE\n");
	printf("4 - PRIORIZAR ALGUM PACIENTE\n");
	printf("5 - EXCLUIR ALGUM PACIENTE DA FILA\n");
	
	printf("\n0 - SAIR DO PROGRAMA\n");
	scanf(" %d", &opt);
	
	return opt;
}


Paciente *setPaciente(Paciente *fim, int idPaciente){
	Paciente *novoPaciente = malloc(sizeof(Paciente));
	
	system("clear");
	printf("  === CADASTRO DE PACIENTE ===\n\n");
	printf("NOME: ");
	scanf(" %[^\n]s", novoPaciente->nome);
	printf("IDADE: ");
	scanf(" %d", &novoPaciente->idade);
	printf("SEXO: ");
	scanf(" %c", &novoPaciente->sexo);
	
	novoPaciente->id = idPaciente;
	
	/*Em uma lista encadeada do tipo FILA, caso haja um fim, o novo paciente ficará depois do fim, 
	* ou seja, o novo paciente será o novo fim. 
	* Caso não haja, significa que não tem ninguém na fila (logo, não existe fila), 
	* por isso há, na função main, uma condição que verifica se existe um fim ou não, caso não exista fim,
	*  o novo paciente (que será o único até então) será o fim e o inicio ao mesmo tempo*/
	if(fim) 
		fim->prox = novoPaciente;
		
	/*O novo paciente será o novo fim, certo? se ele é o final da fila, então
	não haverá ninguém depois dele*/
	novoPaciente->prox = NULL;
	
	imprimirAviso("Paciente cadastrado com sucesso!");
	
	return novoPaciente;
}

void showPacientes(Paciente *inicio){
	while(inicio){
		printf("NOME: %s\n", inicio->nome);
		printf("IDADE: %d\n", inicio->idade);
		printf("SEXO: %c\n", inicio->sexo);
		printf("ID: %04d\n", inicio->id);
		printf("=============\n");
		
		inicio = inicio->prox;
	}	
	
}

//Função que mostra os pacientes cadastrados para o usuário
void getPaciente(Paciente *inicio){
	system("clear");
	printf("  === PACIENTES A SEREM ATENDIDOS ===\n\n");
	showPacientes(inicio);
	
	char opt;
	printf("\nAperte qualquer letra/número e dê ENTER para voltar ao MENU PRINCIPAL.\n");
	scanf(" %c", &opt);
	if(opt)
		return;
	
}

//Função para excluir um paciente da lista (independente de onde ele esteja)
void removPaciente(Paciente **inicio, Paciente **fim){
	Paciente *atual = *inicio;
	Paciente *ant = NULL;
	int id_excluir, confExclusao=0;
	
	system("clear");
	printf("  === EXCLUSÃO DE PACIENTE ===\n\n");
	showPacientes(atual);
	
	printf("\nQual do ID paciente deseja excluir da lista? (Aperte 0 para cancelar) ");
	scanf(" %d", &id_excluir);
	
	if(id_excluir == 0){
		imprimirAviso("EXCLUSÃO CANCELADA! Nenhum paciente foi excluido da fila");
		return;
	}else{
		//Caso haja apenas 1 paciente na lista OU o paciente a ser excluido seja o primeiro da lista
		if((atual->prox == NULL && ant == NULL && atual->id == id_excluir) || (atual->prox != NULL && ant == NULL && atual->id == id_excluir)){
			*inicio = atual->prox;
			free(atual);
			system("clear");
			printf("Paciente de ID %d excluido da fila com sucessso!\n", id_excluir);
			system("sleep 2");
			system("clear");
			confExclusao=1;
			return;
		}
		
		//Caso o paciente a ser excluido nao seja o primeiro da fila, nem o único
		while(atual){
			if(atual->id == id_excluir){
				//se ele for o último
				if(atual == *fim){
					*fim = ant;
				}
				//se ele nao for o ultimo
				if(atual != *fim){
					ant->prox = atual->prox;
				}
				free(atual);
				system("clear");
				printf("Paciente de ID %d excluido da fila com sucessso!\n", id_excluir);
				system("sleep 2");
				system("clear");
				confExclusao=1;
				return;
			}
			ant = atual;
			atual = atual->prox;
		}
		
		//Caso não haja nenhum paciente com aquele ID
		if(!confExclusao){
			system("clear");
			printf("ERRO! Não há nenhum paciente com o ID %d cadastrado na fila.\n", id_excluir);
			system("sleep 2");
			system("clear");
		}
		
	}
}

void atendePaciente(Paciente **inicio){
	Paciente *aux = *inicio; //Ponteiro auxiliar que aponta para o inicio da fila
	
	*inicio = (*inicio)->prox; //Ponteiro *inicio aponta para o segundo elemento da fila
	system("clear");
	printf("O paciente %s foi atendido e liberado!\n", aux->nome);
	system("sleep 2");
	system("clear");
	
	free(aux); /*Libera o primeiro elemento da lista, que estava sendo apontado pelo ponteiro auxiliar 'aux'.
	*Ou seja, a primeira pessoa da lista é atendida e excluida da lista*/
	
}

/*Função para priorizar algum paciente, ou seja, pegar algum paciente (elemento da lista) 
 de qualquer posição da lista e manda-lo para o inicio (fazendo-o ser o primeiro elemento da lista)*/
void priorizaPaciente(Paciente **inicio, Paciente **fim){
	Paciente *atual = *inicio;
	Paciente *ant = NULL;
	int id_priorizar;
	
	system("clear");
	printf("  === PRIORIZAR PACIENTE ===\n\n");
	showPacientes(*inicio);
	
	printf("\nQual do ID paciente deseja priorizar? (Aperte 0 para cancelar) ");
	scanf(" %d", &id_priorizar);
	
	if(id_priorizar != 0){
		while(atual){
			if(atual->id == id_priorizar){
				
				/*Condição que verifica se o paciente já é o primeiro da lista, se ele for,
				não faz sentido prioriza-lo.*/
				if(ant == NULL){
					imprimirAviso("OPS! Esse paciente já é o primeiro da lista!");
					return;
				}
				
				/*Condição que verifica se o paciente a ser priorizado é último da fila, caso seja,
				não podemos fazer com que o ponteiro *fim simplesmente aponte para o que está depois
				*  do paciente a ser priorizado, pois pense bem, se o ele é o último, o que está depois
				* dele é NULL, então o ponteiro *fim acabaria apontando para NULL, isso faria ocorrer um 
				* problema na hora de cadastrar um novo paciente. (Olha: Isso é uma fila, certo? então e eu cadastro
				* um novo paciente sempre no final, se o final for NULL, então meu novo paciente ficaria cadastrado
				*  depois de NULL, exemplo: Maria->João->NULL->Clebson
				* Isso traria muitos problemas, pois tudo que tivesse depois de NULL seria ignorado pelo meu programa.
				* 
				* Caso o paciente a ser priorizado seja realmente o último, basta fazer com que o ponteiro *fim aponte
				* para quem esta atrás do último (que é o penultimo)  */
				if(atual->prox){
					ant->prox = atual->prox;
				}else{
					*fim = ant;
					ant->prox = NULL;
				}
				atual->prox = *inicio;
				*inicio = atual;
				system("clear");
				printf("Paciente [%s (ID: %d)] priorizado com sucesso!\n", atual->nome, atual->id);
				system("sleep 3");
				system("clear");
				return;
				
			}
			ant = atual;
			atual = atual->prox;
		}
		
		imprimirAviso("ERRO! Não há nenhum paciente com esse ID na lista!");
		
	}else{
		imprimirAviso("AÇÃO CANCELADA! Nenhum paciente foi priorizado na fila.");
		return;
	}
	
}

// FUNÇÃO MAIN
int main(){
	int idPaciente=0; 
	/*Variavel que atribui um ID a cada paciente cadastrado,
	 * cada paciente novo cadastrado receberá um ID que será, basicamente,
	 * o ID do último paciente cadastrado, acrescido de 1.
	 * Ou seja, se o último paciente a ser CADASTRADO (preste atenção nessa frase)
	 * tiver o ID 6, o novo paciente a ser cadastrad terá o ID 7.
	 * Porém, mesmo se houver a exclusão de algum paciente da lista, essa regra continuará
	 * O NOVO PACIENTE SEMPRE TERÁ O ID DO ÚLTIMO PACIENTE CADASTRADO, ACRESCIDO DE 1.
	 * Isso facilitará (e muito) na busca de pacientes para excluir, priorizar etc.
	*/
	Paciente *fim = NULL;
	Paciente *inicio = NULL;
	
	do{
		switch(menu()){
			case 1:
				idPaciente++;
				fim = setPaciente(fim, idPaciente);
				if(!inicio)
					inicio = fim;
				break;
				
			case 2:
				if(inicio){
					getPaciente(inicio);
					if(!fim)
						fim = inicio;
				}else
					imprimirAviso("OPSS! Não há nenhum paciente na fila.");
				break;
				
			case 3:
				if(inicio)
					atendePaciente(&inicio);
				else
					imprimirAviso("OPSS! Não há nenhum paciente na fila.");
				break;
				
			case 4:
				if(inicio)
					priorizaPaciente(&inicio, &fim);
				else
					imprimirAviso("OPSS! Não há nenhum paciente na fila.");
				break;
				
			case 5:
				if(inicio)
					removPaciente(&inicio, &fim);
				else
					imprimirAviso("OPSS! Não há nenhum paciente na fila.");
				break;
				
			case 0:
				while(inicio){
					Paciente *aux = inicio;
					inicio = inicio->prox;
					free(aux);
				}
				imprimirAviso("Saindo...");
				return 1;
				
			default:
				imprimirAviso("ERRO! Escolha uma opção válida!");
				break;
		}
	}while(1);
	
	return 0;
}
