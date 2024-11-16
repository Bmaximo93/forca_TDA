/*
* Criar dois arquivos: um para ranking e um para carregar as palavras
* Pedir credenciais de usuário
* Menu principal com créditos, ranking, cadastrar palavra, sair e jogar
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

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
				printf("%s", palavraEscolhida);
				//while (!acertouPalavra && erros < 6) {
				// desenhaForca();
				// desenhaPalavra();
					validaLetra(palavraEscolhida);
					// validaLetra();
				
				// calculaPontuacao();
				//}
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

/*int validaLetra(const char *palavra)
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
		return;
	}
}*/

/*int atualizarLetrasAdivinhadas(char letrasAdvinhadas[], int *numAdvinhacoes, char letraAdvinhada)
{
	//verificar se letra ja foi inserida antes
	for (int i = 0; i < *numAdvinhacoes; i++) {
		if (letrasAdvinhadas[i] == letraAdvinhada) {
			printf("Essa letra já foi inserida");
			return 0;
		}

		letrasAdvinhadas[*numAdvinhacoes] = letraAdvinhada;
		(*numAdvinhacoes)++;
	}
}*/



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

void validaLetra() {

scanf()
	
	Verifica se a letra escolhida está presente na palavra misteriosa e exibe as letras que já foram usadas. Impedir que a mesma letra seja usada
}

void desenhaPalavra() {
	Mostra as palavras conhecidas e desconhecidas como _ _ A _ _ B _
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

