#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

// Definir uma estrutura para armazenar os dados dos clientes
typedef struct
{
	int idade;
	float salario;
	char sexo;
} Cliente;

Cliente *clientes = NULL; // Ponteiro para alocar dinamicamente os clientes
int total_clientes = 0;		// Contador para o número de clientes cadastrados

// Função para posicionar o cursor em um determinado ponto da tela
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = (short)x;
	coord.Y = (short)y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Função para construir a tela padrão
void tela()
{
	int lin;
	int col;

	system("cls");

	for (lin = 1; lin < 25; lin++)
	{
		gotoxy(1, lin);
		printf("|");
		gotoxy(79, lin);
		printf("|");
	}

	for (col = 1; col < 80; col++)
	{
		gotoxy(col, 1);
		printf("-");
		gotoxy(col, 4);
		printf("-");
		gotoxy(col, 22);
		printf("-");
		gotoxy(col, 24);
		printf("-");
	}

	gotoxy(1, 1);
	printf("+");
	gotoxy(79, 1);
	printf("+");

	gotoxy(1, 4);
	printf("+");
	gotoxy(79, 4);
	printf("+");

	gotoxy(1, 22);
	printf("+");
	gotoxy(79, 22);
	printf("+");

	gotoxy(3, 2);
	printf("UNICV");
	gotoxy(60, 2);
	printf("Estrutura de Dados | ");
	gotoxy(3, 3);
	printf("SISTEMA DE CADASTRO DE CLIENTES");
	gotoxy(62, 3);
	printf("Matheus Moreira  | ");
	gotoxy(2, 23);
	printf("MSG");
}

// Função para consultar e exibir os dados dos clientes cadastrados
void consultar()
{
	tela();
	gotoxy(30, 6);
	if (total_clientes == 0)
	{
		printf("Nenhum cliente cadastrado.");
	}
	else
	{
		printf("Clientes cadastrados: %d", total_clientes);
		for (int i = 0; i < total_clientes; i++)
		{
			gotoxy(10, 8 + i * 3);
			printf("Cliente %d:", i + 1);
			gotoxy(10, 9 + i * 3);
			printf("Idade: %d, Salario: %.2f, Sexo: %c", clientes[i].idade, clientes[i].salario, clientes[i].sexo);
		}
	}
	gotoxy(7, 23);
	printf("Pressione qualquer tecla para voltar ao menu...");
	getch();
}

// Programa principal
int main()
{
	int opcao;
	int idade;
	float salario;
	char sexo;

	system("color 0A");

	do
	{
		tela();

		gotoxy(30, 10);
		printf("1 - Cadastrar");
		gotoxy(30, 12);
		printf("2 - Consultar");
		gotoxy(30, 14);
		printf("3 - Sair");

		gotoxy(2, 23);
		printf("Digite sua opcao:");
		scanf("%d", &opcao);
		gotoxy(2, 23);
		printf("                        ");

		switch (opcao)
		{
		case 1: // Opção de Cadastrar
			do
			{
				tela();
				gotoxy(7, 23);
				printf("Cadastrando...");

				// Limpa a mensagem de cadastro
				gotoxy(2, 23);
				printf("                        ");

				// Mostra os dados a serem lidos na tela
				gotoxy(28, 10);
				printf("Digite a Idade.....: ");
				gotoxy(28, 12);
				printf("Digite o Salario...: ");
				gotoxy(28, 14);
				printf("Digite o Sexo......: ");

				// Leitura e validação da idade
				do
				{
					gotoxy(48, 10);
					printf("     ");
					gotoxy(48, 10);
					scanf("%d", &idade);
					if (idade < 18)
					{
						gotoxy(7, 23);
						printf("Idade Invalida. Tente Novamente.");
						getch();
						gotoxy(7, 23);
						printf("                                    ");
					}

				} while (idade < 18);

				// Leitura e validação do salário
				do
				{
					gotoxy(48, 12);
					printf("        ");
					gotoxy(48, 12);
					scanf("%f", &salario);
					if (salario < 2000)
					{
						gotoxy(7, 23);
						printf("Salario Invalido. Tente Novamente.");
						getch();
						gotoxy(7, 23);
						printf("                                    ");
					}
				} while (salario < 2000);

				// Leitura e validação do sexo
				do
				{
					gotoxy(48, 14);
					printf("        ");
					gotoxy(48, 14);
					scanf(" %c", &sexo);
					if (sexo != 'M' && sexo != 'F')
					{
						gotoxy(7, 23);
						printf("Sexo Invalido. Tente Novamente.");
						getch();
						gotoxy(7, 23);
						printf("                                    ");
					}
				} while (sexo != 'M' && sexo != 'F');

				// Realocar memória para um novo cliente
				clientes = (Cliente *)realloc(clientes, (total_clientes + 1) * sizeof(Cliente));
				if (clientes == NULL)
				{
					gotoxy(7, 23);
					printf("Erro ao alocar memória.");
					exit(1);
				}

				// Armazena os dados do novo cliente
				clientes[total_clientes].idade = idade;
				clientes[total_clientes].salario = salario;
				clientes[total_clientes].sexo = sexo;
				total_clientes++;

				gotoxy(7, 23);
				printf("1 = Cadastrar outro | 2 = Voltar ao menu ");
				scanf("%d", &opcao);

			} while (opcao == 1);
			break;

		case 2: // Opção de Consultar
			consultar();
			break;

		case 3: // Sair do programa
			gotoxy(7, 23);
			printf("Saindo do programa...");
			getch();
			break;

		default: // Caso o usuário digite uma opção inválida
			gotoxy(7, 23);
			printf("Opcao Invalida. Tente Novamente.");
			getch();
			break;
		}
	} while (opcao != 3);

	// Liberar a memória alocada
	free(clientes);

	return 0;
}