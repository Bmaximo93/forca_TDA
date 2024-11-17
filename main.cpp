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

void desenharMenu();
const char* escolhePalavra();
bool atualizarLetrasAdivinhadas(char letrasAdivinhadas[], int *numAdivinhacoes, char letra);
int validaLetra(const char *palavra);
void desenhaPalavra(const char *palavra, char letrasAdvinhadas[]);

char letrasAdivinhadas[26] = {'\0'}; 
int numAdivinhacoes = 0;

int main () {
	setlocale(0, "Portuguese");
	int acertouPalavra = 0, erros = 0, opcao;
	
	desenharMenu();
	printf("Digite uma opção: ");
	
	do {
		scanf("%d", &opcao);
		fflush(stdin);
		switch (opcao) {
			case 1: {
				// validaUsuario();
				const char* palavraEscolhida = escolhePalavra();
				printf("\n%s\n\n", palavraEscolhida);
				while (!acertouPalavra && erros < 6) {
					// desenhaForca();
					desenhaPalavra(palavraEscolhida, letrasAdivinhadas);
					validaLetra(palavraEscolhida);
				}
				// calculaPontuacao();
				free((void*)palavraEscolhida);
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



int validaLetra(const char *palavra)
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
				
			return i;
		}

	}
	
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

void desenhaPalavra(const char *palavra, char letrasAdvinhadas[])
{
	

	#ifdef _WIN32
        system("cls");  // Windows-specific command
    #else
        system("clear");  // Unix/Linux/MacOS-specific command
    #endif

	printf("(teste: a palavra é %s)",palavra);
	printf("\n\n");

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



/*
void validaUsuario() {
	Pede o nome do usuário. Se não existir, opção de cadastrar. Se existir, confirmar entrada
}

void cadastrarPalavra() {
	Adiciona uma palavra ao arquivo .txt (provavelmente usar fopen e fwrite)
}

void desenhaForca(erros) {
	Alterar o desenho de acordo com a quantidade de erros
  +---+
  |   |
  O   |
 /|\  |
 /\   |
      |
=========
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

