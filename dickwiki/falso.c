#include <stdio.h>
#include <string.h>
#define tamTex 250
#define arquivo "falau.txt"

FILE *txt;
char aux[1000][251];
int opcao, carregados, i, j;

// busca palavras/frases no dicionario
void Buscar()
{
	system("cls");
	char word[tamTex + 1];
	int locate = 0;
	printf("Digite a palavra e aperte enter para buscar: ");
	fflush(stdin);
	gets(word);
	//system("cls");

	if (strlen(word) > 0)
	{
		for (i = 0; i <= carregados; i++)
		{
			if (strcmp(aux[i], word) == 0) //fun��o que faz a compara��o entre a quantidade de caracteres de duas strings, limita a quantidade de caracteres da palavra digitada.
			{
				locate++; //contabiliza que houve resultado encontrado

				if (i % 2 == 0) //Verifica se a palavra buscada está em português ou em inglês para retornar sua tradução.
				{
					printf("\nPalavra: %s\n", aux[i]);
					printf("Traducao: %s\n\n", aux[i + 1]);
					break;
				}
				else
				{
					printf("\nPalavra: %s\n", aux[i]);
					printf("Traducao: %s\n\n", aux[i - 1]);
					break;
				}
			}
		}
	}

	fflush(stdin);

	if (!locate)
		printf("\nPalavra nao localizada.\n");

	printf("Pressione enter para continuar.\n");
	getchar();
}
//Fun��o para o carregamento das palavras dentro do vetor
void Carregar()
{
	carregados = 0;

	txt = fopen(arquivo, "rb");

	if (txt == NULL)
		printf("Erro na leitura do arquivo!!! Entre em contato com o suporte tecnico!\n");
	else
	{
		while (!feof(txt)) //feof file end of file
		{
			fgets(aux[carregados], tamTex + 1, txt);
			aux[carregados][strcspn(aux[carregados], "\r\n")] = '\0'; //Conta a quantidade de caracteres apenas da palavra, removendo o parágrafo
			carregados++;
		}
	}
	fclose(txt);
}

void Inserir()
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

void Ordenar()
{
	char orgPalavra[251], orgTraducao[251];

	for (j = 0; j < carregados; j = j + 2)
	{
		for (i = 0; i < carregados - 2; i = i + 2)
		{
			if (strcmp(aux[i], aux[i + 2]) > 0)
			{
				strcpy(orgPalavra, aux[i]);
				strcpy(orgTraducao, aux[i + 1]);

				strcpy(aux[i], aux[i + 2]);
				strcpy(aux[i + 1], aux[i + 3]);

				strcpy(aux[i + 2], orgPalavra);
				strcpy(aux[i + 3], orgTraducao);
			}
		}
	}

	txt = fopen(arquivo, "wb"); // abre o dicionário em modo de adi��o/acrescentar mais palavras

	for (i = 0; i <= carregados; i++)
	{
		//printf("Palavra: %s\n", aux[i]);
		if (strlen(aux[i]) > 0)
			fprintf(txt, "%s\n", aux[i]);
	}

	fclose(txt); // fecha o dicionario

	fflush(stdin);
	printf("Dicionario reorganizado com sucesso\nPressione enter para voltar ao menu inicial.\n");
	getchar();
}

void Visualizar()
{
	system("cls"); //Limpa a tela no windows

	for (i = 0; i <= carregados; i++)
	{
		if (strcmp(aux[i], ""))
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
				printf("Palavra: %s", aux[i]);
			else
				printf("\nTraducao: %s\n\n", aux[i]);
		}
	}
	printf("\n\n\nFim\n\n\n");

	fflush(stdin); //Esvazia o buffer do teclado
	printf("Pressione enter para voltar ao menu inicial.\n");
	getchar(); //pausa para retornar ao menu inicial
}

int main()
{
	opcao = -1;
	while (opcao)
	{
		system("cls");
		fflush(stdin);

		printf("Carregando palavras do dicionario, por favor aguarde.");
		Carregar();
		//system("clear");
		system("cls");
		printf("Menu do Dicionario:\n\n");
		printf("************************\n");
		printf("Existem atualmente %d linhas no dicionario.", carregados);
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
		scanf("%d", &opcao);
		printf("\n");

		switch (opcao)
		{
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
				//Apagar();
				break;
			}
			case 5:
			{
				//Corrigir();
				break;
			}
			case 6:
			{
				Ordenar();
				break;
			}
			default:
			{
				break;
			}
		}
	}
}
