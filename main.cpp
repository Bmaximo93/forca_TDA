/*
* Criar dois arquivos: um para ranking e um para carregar as palavras
* Pedir credenciais de usu�rio
* Menu principal com cr�ditos, ranking, cadastrar palavra, sair e jogar
*/

#include <stdio.h>
#include <locale.h>
#include <ctype.h>

void desenharMenu() {
	printf("====================\n");
	printf("1. Jogar\n");
	printf("2. Ver Ranking\n");
	printf("3. Cadastrar Palavra\n");
	printf("4. Cr�ditos\n");
	printf("5. Sair\n");
	printf("====================\n\n");
}

const char* escolhePalavra() {
	// Pega uma palavra do arquivo .txt aleatoriamente (provavelmente usar o fread) e alocar dinamicamente
	return "teste";
}

int main () {
	setlocale(0, "Portuguese");
	int acertouPalavra = 0, erros = 0, opcao;
	
	desenharMenu();
	printf("Digite uma op��o: ");
	
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
					// validaLetra();
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
				printf("Digite um valor v�lido: ");
		}
	} while (opcao < 1 || opcao > 5);
	
	return 0;
}



/*]
void validaUsuario() {
	Pede o nome do usu�rio. Se n�o existir, op��o de cadastrar. Se existir, confirmar entrada
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
	Verifica se a letra escolhida est� presente na palavra misteriosa e exibe as letras que j� foram usadas. Impedir que a mesma letra seja usada
}

void desenhaPalavra() {
	Mostra as palavras conhecidas e desconhecidas como _ _ A _ _ B _
}

void calculaPontuacao() {
	Calcula a pontua��o com base nos erros do usu�rio. Cada acerto de letra d� 100 pontos e cada letra errada perde 50. Acertar a palavra completa d� 300 pontos.
}

void exibirRanking() {
	Exibe o ranking de pontos
}

void exibirCreditos() {
	Exibe os cr�ditos
}
*/

