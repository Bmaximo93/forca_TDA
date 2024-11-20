/*
* Criar dois arquivos: um para ranking e um para carregar as palavras
* Pedir credenciais de usuário
* Menu principal com créditos, ranking, cadastrar palavra, sair e jogar
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#define MAX_NOME 50

void desenharMenu();
void validaUsuario();
const char* escolhePalavra();
bool atualizarLetrasAdivinhadas(char letrasAdivinhadas[], int *numAdivinhacoes, char letra);
int validaLetra(const char *palavra, int *erros, int *acertos);
void desenhaGraficos(const char *palavra, char letrasAdvinhadas[]);
int desenhaForca(int erros);
int rodarPartida();
bool checaVitoria(const char *palavra, char letrasAdivinhadas[]);

int acertouPalavra = 0, erros = 0, acertos = 0;
char letrasAdivinhadas[26] = {'\0'}; 
int numAdivinhacoes = 0;


int main () {
	setlocale(0, "Portuguese");
	int opcao;
	
	desenharMenu();
	printf("Digite uma opção: ");
	
	do {
		scanf("%d", &opcao);
		fflush(stdin);
		switch (opcao) {
			case 1: {
				validaUsuario();
				rodarPartida();
				}
				break;
			case 2:
				// Exibir Ranking
				break;
			case 3:
				// cadastrarPalavra()
				break;
			case 4:
				// exibirCreditos()
				break;
			case 5:
				printf("\n\nObrigado por jogar!");
				return 1;
				break;
			default:
				printf("Digite um valor válido: ");
		}
	} while (opcao < 1 || opcao > 5);
	
	return 0;
}

int rodarPartida()
{
	
	const char* palavraEscolhida = escolhePalavra();

	while (!acertouPalavra && erros < 6) 
	{
		desenhaGraficos(palavraEscolhida, letrasAdivinhadas);
		validaLetra(palavraEscolhida, &erros, &acertos);
		if (checaVitoria(palavraEscolhida, letrasAdivinhadas))
		{
			acertouPalavra = true; // da pra otimizar isso, o acertouPalavra poderia ser definido direto na função checaVitoria sem precisar dessa condicional .BM
		}
	}
	if(acertouPalavra) //professor se voce estiver vendo isso me desculpe
	{
		desenhaGraficos(palavraEscolhida, letrasAdivinhadas);
		printf("\n\nVoce Acertou :)\n\n");
	}
	else
	{
		desenhaGraficos(palavraEscolhida, letrasAdivinhadas);
		printf("\n\nVoce Fracassou :(\n\n");
	}
	// calculaPontuacao();
	free((void*)palavraEscolhida);
	return 0;
}

void desenharMenu() {
	printf("====================\n");
	printf("1. Jogar\n");
	printf("2. Ver Ranking\n");
	printf("3. Cadastrar Palavra\n");
	printf("4. Créditos\n");
	printf("5. Sair\n");
	printf("====================\n\n");
}

const char* escolhePalavra() {
    FILE* arquivo_palavras = fopen("dict.txt", "r");
    if (!arquivo_palavras) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    int total_palavras = 0;
    char buffer[100];
    while (fscanf(arquivo_palavras, "%99s", buffer) == 1) {
        total_palavras++;
    }

    if (total_palavras == 0) {
        printf("Arquivo vazio ou sem palavras válidas.\n");
        fclose(arquivo_palavras);
        return NULL;
    }

    srand(time(NULL));
    int indice_aleatorio = rand() % total_palavras;

    rewind(arquivo_palavras);

    int contador = 0;
    char* palavra_escolhida = NULL;
    while (fscanf(arquivo_palavras, "%99s", buffer) == 1) {
        if (contador == indice_aleatorio) {
            palavra_escolhida = (char*)malloc(strlen(buffer) + 1);
            if (!palavra_escolhida) {
                printf("Erro de alocação de memória.\n");
                fclose(arquivo_palavras);
                return NULL;
            }
            strcpy(palavra_escolhida, buffer);
            break;
        }
        contador++;
    }

    fclose(arquivo_palavras);
    return palavra_escolhida;
}

void validaUsuario() {
    char nome[MAX_NOME];
	char restante[MAX_NOME];
    char nomeArquivo[MAX_NOME];
    int pontuacao;
    char resposta;
    int encontrado = 0;

    FILE *arquivo;

    do {
        printf("Digite o nome de usuário (apenas um nome, sem espaços): ");
        if (scanf("%s", nome) == 1) {
            // Verifica se há algo após o nome lido no buffer
            if (scanf("%[^\n]", restante) == 1) { // Lê qualquer coisa após o nome
                printf("Erro: Digite apenas um único nome, sem espaços.\n");
                // Limpa o buffer caso tenha sobrado entrada
                while (getchar() != '\n');
            } else {
                break; // Nome válido
            }
        } else {
            printf("Erro na leitura do nome. Tente novamente.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n');
        }
    } while (1);

    // Abrir o arquivo para leitura
    arquivo = fopen("usuarios.txt", "r");

    if (arquivo != NULL) {
        // Procurar o nome do usuário no arquivo
        while (fscanf(arquivo, "%s %d", nomeArquivo, &pontuacao) != EOF) {
            if (strcmp(nome, nomeArquivo) == 0) {
                encontrado = 1;
                break;
            }
        }
        fclose(arquivo);
    }

    if (encontrado) {
        // Se o usuário foi encontrado
        printf("Jogar como %s? (s/n): ", nome);
        scanf(" %c", &resposta);
        if (resposta == 's' || resposta == 'S') {
            printf("Bem-vindo de volta, %s! Sua pontuação atual é %d.\n", nome, pontuacao);
        } else {
            printf("Operação cancelada.\n");
			exit(1);
        }
    } else {
        // Se o usuário não foi encontrado
        printf("Usuário não encontrado. Deseja cadastrar? (s/n): ");
        scanf(" %c", &resposta);
        if (resposta == 's' || resposta == 'S') {
            // Abrir o arquivo para adicionar um novo usuário
            arquivo = fopen("usuarios.txt", "a");
            if (arquivo != NULL) {
                fprintf(arquivo, "%s 0\n", nome); // Novo usuário começa com pontuação 0
                fclose(arquivo);
                printf("Usuário %s cadastrado com sucesso!\n", nome);
            } else {
                printf("Erro ao abrir o arquivo para cadastro.\n");
				exit(1);
            }
        } else {
            printf("Operação cancelada.\n");
			exit(1);
        }
    }
}

int validaLetra(const char *palavra, int *erros, int *acertos)
{
	char letra;

	do{

		printf("\ninsira uma letra: ");
		scanf(" %c", &letra);
		letra = toupper(letra);

	}while(!atualizarLetrasAdivinhadas(letrasAdivinhadas, &numAdivinhacoes, letra));
	
		
	for (int i = 0; i < strlen(palavra); i++)
	{

		if (letra == palavra[i])
		{
			(*acertos)++;	
			return i;
		}

	}
	
	(*erros)++;
	return -1;
}

bool atualizarLetrasAdivinhadas(char letrasAdivinhadas[], int *numAdivinhacoes, char letra)
{
	//verificar se o que foi inserido foi uma letra
	if (!isalpha(letra))
	{
		return false;
	}
	//verificar se letra ja foi inserida antes
	for (int i = 0; i < 26; i++) 
	{

		if (letrasAdivinhadas[i] == letra)
		{
			printf("\na letra %c já foi inserida\n", letra);
			return false;
		}
		
	}
	letrasAdivinhadas[*numAdivinhacoes] = letra;
	(*numAdivinhacoes)++;
	return true;
}

void desenhaGraficos(const char *palavra, char letrasAdvinhadas[])
{
	

	#ifdef _WIN32
        system("cls");  
    #else
        system("clear"); 
    #endif

	printf("(teste: a palavra é %s)\n",palavra);
	printf("(teste: n de erros %i)", erros);
	printf("\n\n");

	desenhaForca(erros);
	if (erros < 6)
	{
	for (int i = 0; i < strlen(palavra); i++)
	{
		bool letraEncontrada = false;

		for (int j = 0; letrasAdvinhadas[j] != '\0'; j++)
		{
			if (palavra[i] == letrasAdvinhadas[j])
			{
				printf("%c", palavra[i]);
				letraEncontrada = true;
				break;
			}
		}
		
		if (!letraEncontrada)
		{
			printf("_");
		}

		printf(" ");
	}

	printf("\n");
	if(letrasAdivinhadas[0] != '\0')
	{
	printf("\nletras inseridas: ");
	for(int i = 0; i < letrasAdivinhadas[i] != '\0'; i++)
	{
		printf("%c ", letrasAdivinhadas[i]);
	}
	}
	}
	else
	{
		for (int i = 0; i < strlen(palavra); i++)
		{
			printf("%c ", palavra[i]);
		}
	}
	

}

int desenhaForca(int erros) //passar erros como parametro? talvez não seja necessário, discutir
{
	printf("  +---+\n");
	printf("  |   |\n");
	printf("  %s   |\n", (erros >= 1) ? "O":" " );
	printf(" %s%s%s  |\n", (erros >= 2) ? "/":" ",(erros >= 3) ? "|":" ",(erros >= 4) ? "\\":" " );
	printf("  %s%s  |\n", (erros >= 5) ? "/":" ",(erros >= 6) ? "\\":" ");
	printf("      |\n");
	printf("=========   ");
	return 0;
}

bool checaVitoria(const char *palavra, char letrasAdivinhadas[])
{
	int letrasCorretas = 0;
	int lenPalavra = strlen(palavra);
	for (int i = 0; i < lenPalavra; i++)
	{
		for(int j = 0; j < 26; j++)
		{
			if (palavra[i] == letrasAdivinhadas[j])
			{
				letrasCorretas++;
			}
		}
	}
	if (letrasCorretas == lenPalavra)
	{
		return true;
	}
	else
	{
		return false;
	}

}
/*
void validaUsuario() {
	Pede o nome do usuário. Se não existir, opção de cadastrar. Se existir, confirmar entrada
}

void cadastrarPalavra() {
	Adiciona uma palavra ao arquivo .txt (provavelmente usar fopen e fwrite)
}

void calculaPontuacao() {
	Calcula a pontuação com base nos erros do usu�rio. Cada acerto de letra dá 100 pontos e cada letra errada perde 50. Acertar a palavra completa dá 300 pontos.
}

void exibirRanking() {
	Exibe o ranking de pontos
}

void exibirCreditos() {
	Exibe os créditos
}
*/
