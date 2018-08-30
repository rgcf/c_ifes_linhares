#include<stdio.h>
#define tamTex 250 
#define arquivo "falau.txt"

FILE *txt;
char aux[1000][251];
int carregados, i;

// insere palavras/frases no dicionario
void buscar()
{
	char word[tamTex + 1];
	int locate = 0;
	printf("Digite a palavra ou parte dela para buscar: ");
	fflush(stdin);
	gets(word);
	system("cls");

	int tamanho = strlen(word); //Contabilizando o tamanho da palavra que foi digitada para comparação da string

	for (i = 0; i <= carregados; i++)
	{
		if (strncmp(aux[i], word, tamanho) == 0) //função que faz a comparação entre a quantidade de caracteres de duas strings, limita a quantidade de caracteres da palavra digitada.
		{
			if (i % 2 == 0)
			{
				printf("Palavra: %s", aux[i]);
				printf("Traducao: %s\n\n", aux[i + 1]);
			}
			else
			{
				printf("Palavra: %s", aux[i]);
				printf("Traducao: %s\n\n", aux[i - 1]);
			}
			
			locate ++;
		}
	}

	fflush(stdin);

	if (!locate)
		printf("Palavra nao encontrada.\n\n\n");

	printf("Pressione enter para continuar.\n");
	getchar();
}

void carregar()
{
	carregados = 0;
	char palavra[tamTex + 1]; // considerar o '\0'

	txt = fopen(arquivo, "rb");

	if (txt == NULL)
		printf("Erro na leitura do Arquivo!!! Entre em contato com o suporte tecnico!\n");
	else
	{
		while (!feof(txt))
		{
			fgets(aux[carregados], tamTex + 1, txt);
			carregados++;
		}

		fclose(txt);
	}
	fclose(txt);
}

void inserir(void)
{
	char palavra[tamTex + 1]; // considerar o '\0'

	txt = fopen(arquivo, "rb"); // abre o dicionÃ¡rio 

	// erro caso nÃ£o encontre o arquivo de bd do dicionÃ¡rio
	if (txt == NULL)
	{
		printf("Erro, nao foi possivel abrir o banco de dados do dicionario.\n");
	}
	else
	{
		txt = fopen(arquivo, "ab"); // abre o dicionÃ¡rio em modo de adição/acrescentar mais palavras

		printf("Digite a palavra em ingles:\n");
		fflush(stdin); // usado no win para limpar o buffer do teclado
		//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
		fgets(palavra, tamTex, stdin); //stdin eh o teclado
		fprintf(txt, "%s", palavra); // salva a palavra o BD e quebra a linha

		//----------------------------//add tradução
		printf("Digite a traducao:\n");
		fflush(stdin); // usado no win para limpar o buffer do teclado
		//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
		fgets(palavra, tamTex, stdin); //stdin eh o teclado
		fprintf(txt, "%s", palavra); // salva a palavra o BD e quebra a linha
	}
	fclose(txt); // fecha o dicionario

	fflush(stdin); //Esvazia o buffer do teclado

	printf("Pressione enter para voltar ao menu inicial.\n");

	getchar(); //pausa para retornar ao menu inicial
}

void visualizar(void)
{
	system("cls"); //Limpa a tela no windows
	
	for (i = 0; i <= carregados; i++)
	{
		if (strcmp(aux[i], "") != 0)//Compara a string para o caso de ela estar vazia
		{
			if (i % 10 == 0 && i != 0)//Pausa a exibição a cada 5 palavras e seus significados
			{
				fflush(stdin);
				printf("\n\n\n");
				printf("Pressione enter para continuar.\n");
				getchar();
				system("cls");
			}
			//Organizando para melhor exibição
			if (i % 2 == 0)
				printf("\nPalavra: ");
			else
				printf("Traducao: ");

			printf("%s", aux[i]);
		}
		else
		{
			printf("\n\n\nFim\n\n\n");
			break;
		}
	}

	fflush(stdin); //Esvazia o buffer do teclado
	printf("Pressione enter para voltar ao menu inicial.\n");
	getchar(); //pausa para retornar ao menu inicial

}


int main()
{
	int opcao = 9;

	while (opcao)
	{
		system("cls");
		printf("Carregando palavras do dicionario, por favor aguarde.");
		carregar();
		//system("clear");
		system("cls");
		printf("Menu do Dicionario:\n\n");
		printf("************************\n");
		printf("Existem atualmente %d palavras com traducao no dicionario.", (carregados / 2));
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
