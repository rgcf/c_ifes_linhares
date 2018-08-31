#include <stdio.h>
#include <string.h>
#define tamTex 250
#define arquivo "falau.txt"

FILE *txt;
char aux[1000][251];
int carregados, i;

// busca palavras/frases no dicionario
void buscar()
{
	system("cls");
	printf("Carregando palavras do dicionario, por favor aguarde.");
	carregar();
	system("cls");
	char word[tamTex + 1];
	int locate = 0;
	printf("Digite a palavra ou parte dela para buscar: ");
	fflush(stdin);
	gets(word);
	system("cls");

	int tamanho = strlen(word); //Contabilizando o tamanho da palavra que foi digitada para compara��o da string

	for (i = 0; i <= carregados; i++)
	{
		if (strncmp(aux[i], word, tamanho) == 0) //fun��o que faz a compara��o entre a quantidade de caracteres de duas strings, limita a quantidade de caracteres da palavra digitada.
		{
			if (i % 2 == 0)
			{
				printf("Palavra: %s\n", aux[i]);
				printf("Traducao: %s\n\n", aux[i + 1]);
			}
			else
			{
				printf("Palavra: %s\n", aux[i]);
				printf("Traducao: %s\n\n", aux[i - 1]);
			}

			locate++;
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
			aux[carregados][strcspn(aux[carregados], "\r\n")] = '\0';
			carregados++;
		}

		fclose(txt);
	}
	fclose(txt);
}

void inserir(void)
{
	char palavra[tamTex + 1]; // considerar o '\0'

	txt = fopen(arquivo, "rb"); // abre o dicionário

	// erro caso não encontre o arquivo de bd do dicionário
	if (txt == NULL)
	{
		printf("Erro, nao foi possivel abrir o banco de dados do dicionario.\n");
	}
	else
	{
		txt = fopen(arquivo, "ab"); // abre o dicionário em modo de adi��o/acrescentar mais palavras

		printf("Digite a palavra em ingles:\n");
		fflush(stdin); // usado no win para limpar o buffer do teclado
		//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
		fgets(palavra, tamTex, stdin); //stdin eh o teclado
		fprintf(txt, "%s", palavra);   // salva a palavra o BD e quebra a linha

		//----------------------------//add tradu��o
		printf("Digite a traducao:\n");
		fflush(stdin); // usado no win para limpar o buffer do teclado
		//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
		fgets(palavra, tamTex, stdin); //stdin eh o teclado
		fprintf(txt, "%s", palavra);   // salva a palavra o BD e quebra a linha
	}
	fclose(txt); // fecha o dicionario

	fflush(stdin); //Esvazia o buffer do teclado

	printf("Pressione enter para voltar ao menu inicial.\n");

	getchar(); //pausa para retornar ao menu inicial
}

void visualizar(void)
{
	system("cls");
	printf("Carregando palavras do dicionario, por favor aguarde.");
	carregar();
	system("cls"); //Limpa a tela no windows

	for (i = 0; i <= carregados; i++)
	{
		if (strcmp(aux[i], "") != 0) //Compara a string para o caso de ela estar vazia
		{
			if (i % 10 == 0 && i != 0) //Pausa a exibi��o a cada 5 palavras e seus significados
			{
				fflush(stdin);
				printf("\n\n\n");
				printf("Pressione enter para continuar.\n");
				getchar();
				system("cls");
			}
			//Organizando para melhor exibi��o
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
	/*
	Fun��o para exibir as letras das palavras que est�o salvas no dicion�rio hueeeeeeeeeeeee
		carregar();
	
		int j = 0,  k = 0, m;
		
		char teste;
		
		
		for (j = 0; j < carregados; j++)
		{
			m = strlen(aux[j]);
			for (k = 0; k < m; k++)
			{
				printf("Palavra: %d - Letra: %d.\n", j, k);
				printf("%c - %d\n\n", aux[j][k], (int)aux[j][k]);
				
				//aux[j][k]
			}
		}
		system("pause");
	*/

	int opcao = 9;

	while (opcao)
	{

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
