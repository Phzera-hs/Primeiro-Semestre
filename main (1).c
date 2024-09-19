#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int max_users = 0;
bool ha_nome = true;
int userAdd = 0;

typedef struct{

	char nome[100];
	int idade;
	float altura;
	float peso;
	float imc;

}usuario;

void converteMinuscula(char *str) { //converte para minusculo
	for (int i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
}

void DigitaNomeParaBuscar(char *nome){

	if(max_users == 0){
		printf("Não há nenhum usuário!\n\n");
		return;
	}
	printf("Digite o nome que deseja buscar: ");
	scanf("%s", nome);
	ha_nome = true;

}
float IMCcalculo(usuario a[]){
	
	float imc;
	
	imc = a[max_users].peso / (a[max_users].altura*a[max_users].altura);
	
	return imc;
}

void lerUsuario(usuario a[]){ //Cria o usuário

	int i;
	
		printf("\n\n<<< Criar usuário >>>>\n");

		printf("Digite o nome do usuário: ");
		scanf("%s", a[max_users].nome);

		printf("Crie uma idade: ");
		scanf("%i", &a[max_users].idade);

		printf("Crie uma altura: ");
		scanf("%f", &a[max_users].altura);

		printf("Crie um peso: ");
		scanf("%f", &a[max_users].peso);

		a[max_users].imc = IMCcalculo(a);

		printf("\n\n");

		max_users++; //Adciona mais um usuario para laços de repetição percorrerem todas as strucs
		userAdd++;
}

void copiaMinuscula(usuario a[], char nomeMinusc[][100]){ //copia os users para uma matriz que sera armazenado em minusculo

	for(int i = 0; i < max_users; i++){
			strcpy(nomeMinusc[i], a[i].nome);
			converteMinuscula(nomeMinusc[i]);
		}
}

void imprimeunico(usuario a[], int i){

		printf("Nome: %s\n", a[i].nome);
		printf("Idade: %i\n", a[i].idade);
		printf("Altura: %.2f\n", a[i].altura);
		printf("Peso: %.2f\n", a[i].peso);
		printf("IMC: %.2f\n\n", a[i].imc);

}

int switchEscolha(usuario a[], int i){
	int num;

	printf("\n\t\t[1]Verificar todas as informações de %s\n\t\t[2] Verificar IMC de %s\n", a[i].nome, a[i].nome);
	printf("\t\t[3]Editar nome\n\t\t[4]Editar idade\n\t\t[5]Editar altura\n\t\t[6]Editar peso\n");
	printf("\t\t[7]Sair\n\t\tSua opção: ");
	scanf("%i", &num);

	return num;
}

void switchdeAcao(usuario a[], int numero, int i, char nomeMinusc[][100], char nome[]){

	do{	
		switch(numero){

			case 1:
				printf("\t\t");
				for(i = 0; i < max_users; i ++){

					if(strcmp(nomeMinusc[i], nome) == 0)
					break;	
				}	
				a[i].imc = IMCcalculo(a);
				imprimeunico(a, i);
			break;

			case 2:
				for(i = 0; i < max_users; i ++){

					if(strcmp(nomeMinusc[i], nome) == 0)
					break;	
				}	
				a[i].imc = IMCcalculo(a);
				printf("\t\tIMC de %s: %.2f\n", a[i].nome, a[i].imc);
			break;

			case 3:
				printf("\t\tEdite o nome de %s: ", a[i].nome);
				scanf("%s", a[i].nome);
				copiaMinuscula(a, nomeMinusc);
			break;

			case 4:
				printf("\t\tNova idade para %s: ", a[i].nome);
				scanf("%i", &a[i].idade);
			break;

			case 5:
				printf("\t\tNova altura para %s: ", a[i].nome);
				scanf("%f", &a[i].altura);
					IMCcalculo(a);
			break;

			case 6:
				printf("\t\tNovo peso para %s", a[i].nome);
				scanf("%f", &a[i].peso);
					IMCcalculo(a);
			break;

			case 7:
				printf("\t\tSaindo!\n\n");
			break;

			default:
				printf("\t\tOpção incorreta!\n");
			break;
		}
	}while(numero > 7 || numero < 1);	
}
void buscaUser(char nomeMinusc[][100], char nome[], usuario a[]){ 
	//busca o usuario conforme nome digitado
	int i, numero;
	char sim_nao[3];
	converteMinuscula(nome); //Agora tanto faz a forma que for digitado o nome

			for(i = 0; i < max_users; i ++){

				if(strcmp(nomeMinusc[i], nome) == 0){

					printf("Há o nome no servidor!\n");

					do{
						numero = switchEscolha(a, i);
						switchdeAcao(a, numero, i, nomeMinusc, nome);
						printf("\t\tContinuar visualizando esse usuario [Sim] | [Não]: ");
						scanf("%s", sim_nao);
					}while(sim_nao[0] == 's' || sim_nao[0] == 'S');	

				}
					else if(strcmp(nomeMinusc[i], nome) !=0){
						ha_nome = false;
					}
			}

	if(ha_nome = false){
		printf("Não há nome!\n\n");
		ha_nome = true;
	}
}


void imprimeUsers(usuario a[]){ //imprime todos os usuarios

	if(userAdd <= 0){
		printf("Não há usuário!\n\n");
		return;
	}
	else{
		for(int j = 0; j < max_users; j++){
			printf("\n\n--- Usuário %i ---\n", j+1);
			imprimeunico(a, j);
		}
	}	
	printf("\n\n");
}


void sistema(usuario a[], int num, char nomeMinusc[][100]){ //faz a funcao do switch

 char nome[50];

		switch(num){
			case 1:
			lerUsuario(a);
			copiaMinuscula(a, nomeMinusc);
			break;

			case 2:
			DigitaNomeParaBuscar(nome);
			buscaUser(nomeMinusc, nome, a);
			break;

			case 3:
			imprimeUsers(a);
			break;

			case 4:
			printf("Bye-bye!");
			break;

			default:
			printf("Código incorreto!\n");
			break;

		}
}	

int menuText(){ //apenas conteudo de texto e retorna o valor da opcao desejada

	int num;

	printf("----PORTAL USER----\n\n");
		printf("O que deseja fazer:\n[1] Adicionar usuário\n[2] Buscar usuário\n[3]Ver todos usuário\n[4] Encerrar\nSua opção: ");
		scanf("%i", &num);

	return num;

}

int main(void) {

	usuario a[100];
	int num;
	char nomeMinusc[100][100];
	
	do{
		num = menuText();

		sistema(a, num, nomeMinusc);
	}while(num != 4);

	return 0;
}
