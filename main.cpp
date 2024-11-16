/*
* Criar dois arquivos: um para ranking e um para carregar as palavras
* Pedir credenciais de usuário
* Menu principal com créditos, ranking, cadastrar palavra, sair e jogar
*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

void desenharMenu();
const char* escolhePalavra();
int validaLetra(const char* palavra);
int atualizarLetrasAdivinhadas(char letrasAdvinhadas[], int *numAdvinhacoes, char letraAdvinhada);

int main () {
	setlocale(0, "Portuguese");
	int acertouPalavra = 0, erros = 0, opcao, numAdvinhacoes = 0;
	char letrasAdvinhadas[26] = {0};
	
	
	desenharMenu();
	printf("Digite uma opção: ");
	
	do {
		scanf("%d", &opcao);
		fflush(stdin);
		switch (opcao) {
			case 1: {
				// validaUsuario();
				const char* palavraEscolhida = escolhePalavra();
				while (!acertouPalavra && erros < 6) {
					// desenhaForca();
					// desenhaPalavra();
					validaLetra(palavraEscolhida);
				}
				// calculaPontuacao();
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

int validaLetra(const char *palavra)
{
	char letra;
	scanf(" %c", &letra);
	if(isalpha(letra))
	{
		for (int i = 0; i < strlen(palavra); i++)
		{
			if ( toupper(letra) == palavra[i])
			{
				
				return i;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{

	}
}

int atualizarLetrasAdivinhadas(char letrasAdvinhadas[], int *numAdvinhacoes, char letraAdvinhada)
{
	//verificar se letra ja foi inserida antes
	for (int i = 0; i < *numAdvinhacoes; i++) {
		if (letrasAdvinhadas[i] == letraAdvinhada) {
			printf("Essa letra já foi inserida");
			return;
		}

		letrasAdvinhadas[*numAdvinhacoes] = letraAdvinhada;
		(*numAdvinhacoes)++;
	}
}


/*]
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

void validaLetra() {

scanf()
	
}

void desenhaPalavra() {
	Mostra as palavras conhecidas e desconhecidas como _ _ A _ _ B _
}

void calculaPontuacao() {
	Calcula a pontuação com base nos erros do usuário. Cada acerto de letra dá 100 pontos e cada letra errada perde 50. Acertar a palavra completa dá 300 pontos.
}

void exibirRanking() {
	Exibe o ranking de pontos
}

void exibirCreditos() {
	Exibe os créditos
}
*/

const char* escolhePalavra() {
	// Pega uma palavra do arquivo .txt aleatoriamente (provavelmente usar o fread) e alocar dinamicamente
	return "teste";
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
