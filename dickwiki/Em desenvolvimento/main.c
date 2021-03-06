#include "funcoes.h"
int main()
{
	int opcao = -1;
	do
	{
		fflush(stdin);
		opcao = -1;
		system("cls");
		txt = fopen(arquivo, "rb");
		printf("Carregando palavras do dicionario, por favor aguarde.");
		Carregar();
		system("cls");
		printf("Menu do Dicionario:\n\n");
		printf("************************\n");
		printf("Existem atualmente %d palavras no dicionario.", carregados/2);
		printf("\n************************\n");
		printf("1. Visualizar\n");
		printf("2. Buscar\n");
		printf("3. Inserir\n");
		printf("4. Retirar\n");
		printf("5. Corrigir\n");
		printf("6. Ordenar\n");
		printf("7. Estudar\n");
		printf("0. Sair do Programa\n");
		printf("************************\n");
		printf("Opcao:\n");
		scanf("%d", &opcao);
		fflush(stdin);
		printf("\n");
		system("cls");
		switch (opcao)
		{
			case 0:
				exit(1);
			case 1:
			{
				Visualizar();
				break;
			}
			case 2:
			{
				
				Buscar();
				break;
			}
			case 3:
			{
				Inserir();
				break;
			}
			case 4:
			{
				RetirarPalavra();
				break;
			}
			case 5:
			{
				Corrigir();
				break;
			}
			case 6:
			{
				Ordenar();
				printf("Dicionario ordenado com sucesso!\n");
				FimFuncao();
				fflush(stdin);
				break;
			}
			case 7:
			{
				Estudar();
				break;
			}
			default:
			{
				printf("Opcao (%d) invalida, por favor, pressione enter para tentar novamente.", opcao);
				getchar();
				fflush(stdin);
				break;
			}
		}
	}while (opcao);
	return 0;
}
