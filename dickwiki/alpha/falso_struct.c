#include<stdio.h>
#define tamText 250 
#define arquivo "falau.txt"

FILE *txt;
char aux[1000][tamText + 1];
int carregados;

struct dicionario {
	char palavra[tamText + 1];
	char traducao[tamText + 1];
} dic[1000];

//busca palavras no dicionario
void buscar()
{
	int i;
	char word[tamText + 1];
	printf("Digite a palavra que deseja encontrar o significado: ");
	fflush(stdin);

	gets(word);
	system("cls");

	printf("%s\n", word);

	for (i = 0; i <= carregados; i++)
	{
		printf("%d\n", i);
		printf("%s\n", dic[i].palavra);

		if (strcmp(dic[i].palavra+"\n", word) == 0)
		{
			if (i % 2 == 0)
			{

				printf("Palavra: %s\n", aux[i]);
				printf("Traducao: %s", aux[i + 1]);
			}
			else
			{
				printf("Palavra: %s\n", aux[i]);
				printf("Traducao: %s", aux[i - 1]);
			}
			printf("\n\n\nPressione enter para continuar.\n");
			getchar();
			return;
		}
	}
	printf("Palavra nao encontrada.\n\n\n");
	printf("Pressione enter para continuar.\n");
	getchar();
}

//carrega as palavras do dicionario
void carregar()
{
	carregados = 0;
	char palavra[tamText + 1]; // considerar o '\0'

	txt = fopen(arquivo, "rb");

	if (txt == NULL)
		printf("Erro na leitura do Arquivo!!! Entre em contato com o suporte tecnico!\n");
	else
	{
		while (fgets(aux[carregados], tamText + 1, txt) != NULL) carregados++; // copia palavra para um vetor

		fclose(txt);
	}
	fclose(txt);
}

//exibi as palavras do dicionario
void imprimir()
{
	int i;

	for (i = 0; i <= carregados; i++)
	{
		//Compara a string para o caso de ela estar vazia
		if (strcmp(aux[i], "") != 0)
		{
			//Pausa a exibição a cada 5 palavras e seus significados
			if (i % 10 == 0 && i != 0)
			{
				fflush(stdin);
				printf("\n\n\n");
				printf("Pressione enter para continuar.\n");
				getchar();
				system("cls");
			}
			printf("%s", aux[i]);
		}
		else
		{
			printf("\n\n\nFim\n\n\n");
			break;
		}
	}
}

//insere palavras no dicionario
void inserir()
{
	txt = fopen(arquivo, "ab"); // abre o dicionÃ¡rio 

	// erro caso nÃ£o encontre o arquivo de bd do dicionÃ¡rio
	if (txt == NULL)
	{
		printf("Erro, nao foi possivel abrir o banco de dados do dicionario.\n");
	}
	else
	{
		printf("Digite a palavra em ingles:\n");
		fflush(stdin); // usado no win para limpar o buffer do teclado
		//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
		fgets(dic.palavra, tamText, stdin); //stdin eh o teclado
		fprintf(txt, "%s", dic.palavra); // salva a palavra o BD e quebra a linha

		//----------------------------//add tradução
		printf("Digite a traducao:\n");
		fflush(stdin); // usado no win para limpar o buffer do teclado
		//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
		fgets(dic.traducao, tamText, stdin); //stdin eh o teclado
		fprintf(txt, "%s", dic.traducao); // salva a palavra o BD e quebra a linha
	}
	fclose(txt); // fecha o dicionario
}


// visualizar palavras no dicionario
void visualizar()
{
	carregar(); //função que carrega na memória os valores que estão inseridos no arquivo

	system("cls"); //Limpa a tela no windows

	imprimir(); //exibe os valores armazenados

	fflush(stdin); //Esvazia o buffer do teclado

	printf("Pressione enter para voltar ao menu inicial.\n");

	getchar(); //pausa para retornar ao menu inicial

}

int main()
{
	int opcao = 9;
	inserir();

	while (opcao)
	{
		//carregar();
		//system("clear");
		system("cls");
		printf("Menu do Dicionario:\n\n");
		printf("************************\n");
		printf("Existem atualmente %d palavras com traducao atualmente no dicionario.", (carregados / 2));
		printf("\n************************\n");
		printf("1. Visualizar\n");
		printf("2. Buscar\n");
		printf("3. Inserir\n");
		printf("4. Retirar\n");
		printf("5. Corrigir\n");
		printf("6. Ordenar\n");
		printf("0. Sair do Programa\n");
		printf("************************\n");
		printf("Opcao:\n");
		fflush(stdin);
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
			case 1:
			{
				visualizar();
				break;
			}
			case 2:
			{
				buscar();
				break;
			}
			case 3:
			{
				inserir();
				break;
			}
			case 4:
			{
				//apagar();
				break;
			}
			case 5:
			{
				//corrigir();
				break;
			}
			case 6:
			{
				//ordenar();
				break;
			}
			default:
			{
				break;
			}
		}
	}
	
}
