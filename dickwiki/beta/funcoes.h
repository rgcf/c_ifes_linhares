/**********************************************************************************************************
Esta é a biblioteca de funções do dicionario feito em 'C'.
************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define tamTex 251       //tamanho do texto que pode ser utilizado
#define arquivo "db.txt" //definição do nome do arquivo de dados

FILE *txt;
//Variaveis globais
char aux[1000][tamTex], word[tamTex];
int carregados, i, j;

//Função que solicita uma ação do usuário para continuar
void FimFuncao()
{
    fflush(stdin); //Esvazia o buffer do teclado
    printf("Pressione enter para voltar ao menu inicial.\n");
    getchar(); //pausa para retornar ao menu inicial
}

//Função para confirmar, retornando 1 para sim e 0 para não
int Confirma()
{
    char conf = ' ';
    do
    {
        printf("Digite \"S\" para sim ou \"N\" para nao:\n");
        scanf("%c", &conf);
        fflush(stdin);
        switch (conf)
        {
        case 's':
            return 1;
        case 'S':
            return 1;
        case 'n':
            return 0;
        case 'N':
            return 0;
        default:
            printf("\nValor invalido, por favor, tente novamente.\n");
        }
    } while (1);
}

//Fun��o que ordena as palavras e remove os espa�os vazios ao salvar no arquivo
void Ordenar()
{
    char orgPalavra[tamTex], orgTraducao[tamTex];

    for (j = 0; j < carregados - 2; j = j + 2)
    {
        if (strcmp(aux[j], aux[j + 2]) == 0) //removendo os valores repetidos, estando em branco ou não
        {
            strcpy(aux[j + 2], "");
            strcpy(aux[j + 3], "");
        }
        for (i = 0; i <= carregados - 4; i = i + 2)
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

    txt = fopen(arquivo, "wb"); // abre o dicion�rio em modo de adicao para acrescentar mais palavras

    for (i = 0; i <= carregados; i++)
    {
        if (strlen(aux[i]) > 0)           //ignora os valores vazios q continuarem salvos dentro do vetor
            fprintf(txt, "%s\n", aux[i]); //grava os valores dentro do arquivo txt
    }

    fclose(txt); // fecha o dicionario
}
// busca palavras/frases no dicionario
void Buscar()
{

    int locate = 0;
    printf("Digite a palavra e aperte enter para buscar: ");
    fflush(stdin); // usado no win para limpar o buffer do teclado
    gets(word);
    if (strlen(word) > 0)
    {
        for (i = 0; i <= carregados; i++)
        {
            if (strcmp(aux[i], word) == 0) //função que faz a compara??o entre a quantidade de caracteres de duas strings, limita a quantidade de caracteres da palavra digitada.
            {
                locate++; //contabiliza que houve resultado encontrado

                if (i % 2 == 0) //Verifica se a palavra buscada est� em portugu�s ou em ingl�s para retornar sua tradu��o.
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

    if (!locate)
        printf("\nPalavra nao localizada.\n");

    FimFuncao();
}

//Fun��o para o carregamento das palavras dentro do vetor
void Carregar()
{
    //Função para zerar o vetor caso tenha sido carregado antes, evitando qualquer tipo de erro com as palavras
    if (carregados != 0)
        for (i = 0; i < 1000; i++)
            strcpy(aux[i], "");
    //Final da função que zera o vetor

    carregados = 0; //Zerando o contador de palavras carregadas

    txt = fopen(arquivo, "rb"); // Abrindo o arquivo de dados

    //Verificando se o arquivo de dados existe ou não
    //Caso não exista, é permitido que o usuário crie um novo ou encerre o programa
    if (!txt)
    {
        system("cls");
        printf("Erro ao abrir o arquivo de dados.\n");

        //Verificando a opção do usuário e testando para verificar se é valida ou não
        printf("Deseja criar um novo arquivo?\n");

        if (Confirma())
        {
            txt = fopen(arquivo, "wb");
            if (!txt)
            {
                printf("Erro ao criar o arquivo, entre em contato com o suporte tecnico.");
                exit(1);
            }
            else
                printf("Arquivo criado com sucesso");
        }
        else
        {
            system("cls");
            printf("\nO programa sera encerrado, por favor configure uma base de dados ou crie uma nova.");
            exit(0);
        }
    }
    else
    {
        while (!feof(txt)) //feof lendo todas as linhas do arquivo, até a ultima (end of file)
        {
            fgets(aux[carregados], tamTex, txt);
            aux[carregados][strcspn(aux[carregados], "\r\n")] = '\0'; //Conta a quantidade de caracteres apenas da palavra, removendo o parágrafo, no windows o parágrafo é '\r\n', no linux apenas \n, quando salva.
            carregados++;
        }
    }
    fclose(txt);
}

void Corrigir()
{
    char corrigeDicionario[tamTex];
    int escolhaCorrecao;
    j = 0;

    printf("Digite a palavra que deseja corrigir e pressione enter:\n");
    fflush(stdin); // usado no win para limpar o buffer do teclado
    gets(word);

    if (strlen(word) > 0)
    {
        for (i = 0; i <= carregados; i++)
        {
            if (strcmp(aux[i], word) == 0) //fun??o que faz a compara??o entre a quantidade de caracteres de duas strings, limita a quantidade de caracteres da palavra digitada.
            {

                if (i % 2 == 0) //Apenas exibe palavras em inglês.
                {
                    printf("\nPalavra: %s\n", aux[i]);
                    printf("Traducao: %s\n\n", aux[i + 1]);
                    fflush(stdin);
                    printf("O que deseja corrigir?\n");
                    printf("Digite:\n1 para corrigir a palavra\n2 para corrigir o significado:\n");
                    scanf("%d", &escolhaCorrecao);
                    fflush(stdin);
                    if (escolhaCorrecao == 1)
                    {
                        printf("Digite a nova palavra:\n");
                        gets(corrigeDicionario);
                        fflush(stdin);
                        if (strlen(corrigeDicionario) > 0)
                        {
                            strcpy(aux[i], corrigeDicionario);
                            j++; //contabiliza que houve resultado encontrado e alterado
                        }
                        else
                        {
                            printf("\nValor invalido!\n");
                            FimFuncao();
                            return;
                        }
                        break;
                    }
                    else
                    {
                        printf("Digite o novo significado:\n");
                        gets(corrigeDicionario);
                        fflush(stdin);
                        if (strlen(corrigeDicionario) > 0)
                        {
                            strcpy(aux[i + 1], corrigeDicionario);
                            j++; //contabiliza que houve resultado encontrado e alterado
                        }
                        else
                        {
                            printf("\nValor invalido!\n");
                            FimFuncao();
                            return;
                        }
                        break;
                    }
                }
            }
        }
        //Faz a verificação se houve ou não alteração na palavra ou significado, para poder salvar no arquivo de dados
        if (j)
        {
            txt = fopen(arquivo, "wb"); // abre o dicionï¿½rio em modo de adicao para acrescentar mais palavras

            for (i = 0; i <= carregados; i++)
            {
                if (strlen(aux[i]) > 0)           //ignora os valores vazios q continuarem salvos dentro do vetor
                    fprintf(txt, "%s\n", aux[i]); //grava os valores dentro do arquivo txt
            }

            fclose(txt); // fecha o dicionario
            printf("\nDados alterados com sucesso!\n");
        }
        else
            printf("\nPalavra nao localizada.\n");
    }
    else
    {
        printf("\nValor invalido!\n");
    }
    FimFuncao();
}

void Estudar()
{
    int cont = 0; //variavel auxiliar
    i = 0;

    do
    {
        system("cls");

        if (cont != (carregados - 1) / 2)
        {
            srand(time(NULL)); //faz com que se gere novos numeros caso crie outra matriz ou compile novamente
            do
            {
                i = rand() % (carregados - 1); //preenche randomicamente com numeros aleatorios
                if (i % 2 != 0)
                    i--;
            } while (strcmp(aux[i], aux[i + 1]) == 0);

            fflush(stdin);
            printf("**************************************");
            printf("\nPalavra:  %s", aux[i]);
            printf("\n**************************************");
            printf("\n\nPressione enter para exibir a traducao.\n");

            getchar();
            fflush(stdin);
            printf("\n**************************************");
            printf("\nTraducao:  %s", aux[i + 1]);
            printf("\n**************************************");
            printf("\n\nTeve dificuldade?\n");

            if (!Confirma())
            {
                strcpy(aux[i], "");
                strcpy(aux[i + 1], "");
                cont++;
            }
        }
        else
        {
            printf("\n \t !!!!!! Parabens, voce completou o Dicionario !!!!!!\n\n");
            FimFuncao();
            return;
        }

        printf("\nDeseja continuar estudando?\n");
    } while (Confirma());
}

//Fun��o para inclus�o de novas palavras
void Inserir()
{
    char palavra[tamTex]; // considerar o '\0'
    do
    {
        txt = fopen(arquivo, "rb"); // abre o dicion�rio

        // erro caso n�o encontre o arquivo de bd do dicion�rio
        if (txt == NULL)
        {
            printf("Erro, nao foi possivel abrir o banco de dados do dicionario.\n");
        }
        else
        {
            txt = fopen(arquivo, "ab"); // abre o dicionário em modo de adição/acrescentar mais palavras

            printf("Digite a palavra em ingles:\n");
            fflush(stdin);                 // usado no win para limpar o buffer do teclado
            fgets(palavra, tamTex, stdin); //stdin eh o teclado
            fprintf(txt, "%s", palavra);   // salva a palavra o BD e quebra a linha

            //----------------------------//add tradução
            printf("Digite a traducao:\n");
            fflush(stdin);                 // usado no win para limpar o buffer do teclado
            fgets(palavra, tamTex, stdin); //stdin eh o teclado
            fprintf(txt, "%s", palavra);   // salva a palavra o BD e quebra a linha
        }
        fclose(txt); // fecha o dicionario
        printf("\nPalavra inserida com sucesso.\nDeseja inserir outra palavra?");
    } while (Confirma());

    FimFuncao();
}

void RetirarPalavra()
{
    j = 0;
    do
    {

        printf("Digite a palavra que deseja retirar: ");
        fflush(stdin); // usado no win para limpar o buffer do teclado
        gets(word);
        //system("cls");

        if (strlen(word) > 0) //conta o tamanho da palavra e verifica se ela é maior que 0
        {
            for (i = 0; i <= carregados; i++)
            {
                if (strcmp(aux[i], word) == 0) //fun??o que faz a compara??o entre a quantidade de caracteres de duas strings, limita a quantidade de caracteres da palavra digitada.
                {
                    j++;
                    if (i % 2 == 0) //Verifica se a palavra buscada est� em portugu�s ou em ingl�s para retornar sua tradu��o.
                    {
                        printf("Confirma a exclusao da palavra \"%s\" e sua traducao?", strupr(aux[i]));
                        if (!Confirma())
                        {
                            printf("\nA palavra nao foi retirada do dicionario.\nPressione enter para retornar ao menu principal.\n");
                            fflush(stdin);
                            getchar();
                            return;
                        }
                        strcpy(aux[i], "");
                        strcpy(aux[i + 1], "");
                        break;
                    }
                    else
                    {
                        printf("Confirma a exclusao da palavra \"%s\" e sua traducao?", strupr(aux[i]));
                        if (!Confirma())
                        {
                            printf("\nA palavra nao foi retirada do dicionario.\nPressione enter para retornar ao menu principal.\n");
                            fflush(stdin);
                            getchar();
                            return;
                        }
                        strcpy(aux[i], "");
                        strcpy(aux[i - 1], "");
                        break;
                    }
                }
            }
            if (!j)
            {
                printf("\nPalavra nao localizada.\n");
                printf("\nDeseja buscar novamente?\n");
                if (!Confirma())
                    return;
            }
            else
            {
                txt = fopen(arquivo, "wb"); // abre o dicion�rio em modo de adicao para acrescentar mais palavras

                for (i = 0; i <= carregados; i++)
                {
                    if (strlen(aux[i]) > 0)           //remove os valores vazios q continuarem salvos dentro do vetor
                        fprintf(txt, "%s\n", aux[i]); //grava os valores dentro do arquivo txt
                }

                fclose(txt); // fecha o dicionario
                printf("\nPalavra retirada do dicionario com sucesso!.");
                FimFuncao();
                return;
            }
        }
        else
        {
            printf("\nNenhuma palavra digitada, tente novamente. \n");
        }
    } while (1);
}

void Visualizar()
{
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

    FimFuncao();
}
