/**********************************************************************************************************
Esta é a biblioteca de funções do dicionario feito em 'C'.

************************************************************************************************************/
#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#define tamTex 251
#define arquivo "falau.txt"

FILE *txt;
char aux[1000][tamTex], word[tamTex];
int carregados, i, j;
// busca palavras/frases no dicionario

void Buscar()
{
	system("cls");
	// system("clear");
	int locate = 0;
	printf("Digite a palavra e aperte enter para buscar: ");
	fflush(stdin); // usado no win para limpar o buffer do teclado
	//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
	gets(word);
	//system("cls");
	//word[strcspn(aux[carregados], "\r\n")] = '\0';
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

	fflush(stdin); // usado no win para limpar o buffer do teclado
	// __fpurge(stdin); // usado no linux para limpar o buffer do teclado

	if (!locate)
		printf("\nPalavra nao localizada.\n");

	printf("Pressione enter para continuar.\n");
	getchar();
}

int CriarArquivo()
{
	txt = fopen(arquivo, "wb");
	if (!txt)
	{
		printf("Erro ao criar o arquivo, entre em contato com o suporte tecnico.");
		exit(1);
	}
	else
	{
		printf("Arquivo criado com sucesso");
		return 1;
	}
}

//Fun��o para o carregamento das palavras dentro do vetor
void Carregar()
{
	carregados = 0;

	txt = fopen(arquivo, "rb");

	if (!txt)
	{
		system("cls");
		printf("Erro ao abrir a base de dados, deseja criar um novo arquivo de dados?\n");

		char criarTxt = ' ';
		int arquivoCriado = 0;

		do
		{
			printf("Digite:\n \"S\" - para criar um novo arquivo;\n \"N\" - para encerrar o programa\n\n");
			fflush(stdin);
			scanf("%c", &criarTxt);
			switch (criarTxt)
			{
				case 's':
				{
					arquivoCriado = CriarArquivo();
					break;
				}
				case 'S':
				{
					arquivoCriado = CriarArquivo();
					break;
				}
				case 'n':
					exit(1);
				case 'N':
					exit(1);
				default:
				system("cls");
				printf("Valor invalido invalido, por favor, tente novamente.\n\n");
			}
		}while (!arquivoCriado);
	}
	else
	{
		while (!feof(txt)) //feof file end of file
		{
			fgets(aux[carregados], tamTex, txt);
			aux[carregados][strcspn(aux[carregados], "\r\n")] = '\0'; //Conta a quantidade de caracteres apenas da palavra, removendo o parágrafo, no windows o parágrafo é '\r\n', no linux apenas \n, quando salva.
			carregados++;
		}
	}
	fclose(txt);
}

int Confirma()
{
	int conf = 1;
	printf("\nDigite \"0\" para sim ou \"1\" para nao:\n");
	scanf("%d", &conf);
	return conf;
}

void Corrigir()
{
	
}


//Função para inclusão de novas palavras
void Inserir()
{
	system("cls");
	
	char palavra[tamTex]; // considerar o '\0'

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
		// __fpurge(stdin);			   // usado no linux para limpar o buffer do teclado
		fgets(palavra, tamTex, stdin); //stdin eh o teclado
		fprintf(txt, "%s", palavra);   // salva a palavra o BD e quebra a linha

		//----------------------------//add tradu��o
		printf("Digite a traducao:\n");
		fflush(stdin); // usado no win para limpar o buffer do teclado
		// __fpurge(stdin);			   // usado no linux para limpar o buffer do teclado
		fgets(palavra, tamTex, stdin); //stdin eh o teclado
		fprintf(txt, "%s", palavra);   // salva a palavra o BD e quebra a linha
	}
	fclose(txt); // fecha o dicionario

	fflush(stdin); // usado no win para limpar o buffer do teclado
	// __fpurge(stdin); // usado no linux para limpar o buffer do teclado
	printf("Pressione enter para voltar ao menu inicial.\n");

	getchar(); //pausa para retornar ao menu inicial
}
//Função que ordena as palavras e remove os espaços vazios ao salvar no arquivo
void Ordenar()
{
	char orgPalavra[tamTex], orgTraducao[tamTex];

	for (j = 0; j < carregados; j = j + 2)
	{
		for (i = 0; i <= carregados - 4; i = i + 2)
		{
			if (strcmp(aux[i], aux[i + 2]) == 0) //removendo os valores repetidos, estando em branco ou n�o apenas teste extra
			{
				strcpy(aux[i], "");
				strcpy(aux[i + 1], "");
			}
			else if (strcmp(aux[i], aux[i + 2]) > 0)
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

	txt = fopen(arquivo, "wb"); // abre o dicionário em modo de adicao para acrescentar mais palavras
	
	for (i = 0; i <= carregados; i++)
	{
		if (strlen(aux[i]) > 0)			  //remove os valores vazios q continuarem salvos dentro do vetor
			fprintf(txt, "%s\n", aux[i]); //grava os valores dentro do arquivo txt
	}

	fclose(txt); // fecha o dicionario

	fflush(stdin); // usado no win para limpar o buffer do teclado
	// __fpurge(stdin); // usado no linux para limpar o buffer do teclado
	printf("Dicionario reorganizado com sucesso\nPressione enter para voltar ao menu inicial.\n");
	getchar();
}

void RetirarPalavra()
{
	printf("Digite a palavra que deseja retirar: ");
	fflush(stdin); // usado no win para limpar o buffer do teclado
	//__fpurge(stdin); // usado no linux para limpar o buffer do teclado
	gets(word);
	//system("cls");

	if (strlen(word) > 0)
	{
		for (i = 0; i <= carregados; i++)
		{
			if (strcmp(aux[i], word) == 0) //fun��o que faz a compara��o entre a quantidade de caracteres de duas strings, limita a quantidade de caracteres da palavra digitada.
			{	
				char exibePalavra[tamTex];
				if (i % 2 == 0) //Verifica se a palavra buscada está em português ou em inglês para retornar sua tradução.
				{
					printf("Confirma a exclusao da palavra \"%s\" e sua traducao?", aux[i]);
					if(Confirma())
						break;
					strcpy(aux[i], "");
					strcpy(aux[i + 1], "");

					break;
				}
				else
				{
					printf("Confirma a exclusao da palavra \"%s\" e sua traducao?", aux[i]);
					if(Confirma())
						break;
					strcpy(aux[i], "");
					strcpy(aux[i - 1], "");
					break;
				}
			}
		}
		
	txt = fopen(arquivo, "wb"); // abre o dicionário em modo de adicao para acrescentar mais palavras

	for (i = 0; i <= carregados; i++)
	{
		if (strlen(aux[i]) > 0)			  //remove os valores vazios q continuarem salvos dentro do vetor
			fprintf(txt, "%s\n", aux[i]); //grava os valores dentro do arquivo txt
	}

	fclose(txt); // fecha o dicionario
	}
}

void Visualizar()
{
	system("cls"); //Limpa a tela no Linux
	if (carregados > 1)
		{
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
		}
	else
		printf("Dicionario vazio, insira novas palavras.\n\n");

	fflush(stdin); //Esvazia o buffer do teclado
	printf("Pressione enter para voltar ao menu inicial.\n");
	getchar(); //pausa para retornar ao menu inicial
}
