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
				printf("%s", palavraEscolhida);
				//while (!acertouPalavra && erros < 6) {
					// desenhaForca();
					// desenhaPalavra();
					// validaLetra();
				//}
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

