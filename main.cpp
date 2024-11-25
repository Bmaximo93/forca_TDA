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

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define MAX_NOME 50
#define MAX_PALAVRA 50
#define MAX_USUARIOS 100

typedef struct {
    char nome[MAX_NOME];
    int pontuacao;
} Usuario;

void desenharMenu();
int validaUsuario();
const char* escolhePalavra();
bool atualizarLetrasAdivinhadas(char letrasAdivinhadas[], int *numAdivinhacoes, char letra);
int validaLetra(const char *palavra, int *erros, int *acertos);
void desenhaGraficos(const char *palavra, char letrasAdvinhadas[]);
int desenhaForca(int erros);
int rodarPartida();
bool checaVitoria(const char *palavra, char letrasAdivinhadas[]);
void exibirCreditos();
void cadastrarPalavra();
int palavraJaExiste(const char *palavra, const char *nomeArquivo);
int comparaUsuarios(const void *a, const void *b);
void exibeRanking();
void atualizaPontuacao(const char* arquivo, int indiceUsuario, int acertos, int erros, bool acertouPalavra);
void cpSleep(int segundos);
void cpClear();
void voltarMenu();

//
int acertouPalavra = 0, erros = 0, acertos = 0;
char letrasAdivinhadas[26] = {'\0'};
int numAdivinhacoes = 0;
int indiceUsuario = 0;

int main () {
	setlocale(0, "Portuguese");
	int opcao;
	
	
	do {

		//reinicia variaveis
		acertouPalavra = 0;
		erros = 0;
		acertos = 0;
		memset(letrasAdivinhadas, '\0', sizeof(letrasAdivinhadas));
		numAdivinhacoes = 0;

		desenharMenu();
		printf("Digite uma opção: ");

		scanf("%d", &opcao);
		fflush(stdin);
		switch (opcao) 
		{
			case 1: {
				indiceUsuario = validaUsuario();
				rodarPartida();
				}
				voltarMenu();
				break;
			case 2:
				cpClear();
				exibeRanking();
				voltarMenu();
				break;
			case 3:
				cpClear();
				cadastrarPalavra();
				voltarMenu();
				break;
			case 4:
				cpClear();
				exibirCreditos();
				voltarMenu();
				break;
			case 5:
				cpClear();
				printf("\n\nObrigado por jogar!\n\n");
				return 1;
				break;
			default:
				printf("Digite um valor válido: ");
		}
	} while(true);
	
	return 0;
}

int rodarPartida()
{
	
	const char* palavraEscolhida = escolhePalavra();

	while (!acertouPalavra && erros < 6) 
	{
		desenhaGraficos(palavraEscolhida, letrasAdivinhadas);
		validaLetra(palavraEscolhida, &erros, &acertos);
		acertouPalavra = checaVitoria(palavraEscolhida, letrasAdivinhadas);
	}
	if(acertouPalavra)
	{
		desenhaGraficos(palavraEscolhida, letrasAdivinhadas);
		printf("\n\nVoce Acertou :)\n\n");
		cpSleep(2);
	}
	else
	{
		desenhaGraficos(palavraEscolhida, letrasAdivinhadas);
		printf("\n\nVoce Fracassou :(\n\n");
		cpSleep(2);
	}
	atualizaPontuacao("usuarios.txt", indiceUsuario, acertos, erros, acertouPalavra);

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
		cpSleep(1);
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
		cpSleep(1);
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
				cpSleep(1);
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

int validaUsuario() {
    char nome[MAX_NOME];
    char restante[MAX_NOME];
    char nomeArquivo[MAX_NOME];
    int pontuacao;
    char resposta;
    int encontrado = 0;
    int linhaAtual = 0;  // Rastreador de linha

    FILE *arquivo;

    // Entrada do nome de usuário com validação
    do {
        printf("Digite o nome de usuário (apenas um nome, sem espaços): ");
        if (scanf("%s", nome) == 1) {
            // Verifica se há algo após o nome lido no buffer
            if (scanf("%[^\n]", restante) == 1) { // Lê qualquer coisa após o nome
                printf("Erro: Digite apenas um único nome, sem espaços.\n");
                // Limpa o buffer caso tenha sobrado entrada
                while (getchar() != '\n');
				cpSleep(1);
            } else {
                break; // Nome válido
            }
        } else {
            printf("Erro na leitura do nome. Tente novamente.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n');
			cpSleep(1);
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
            linhaAtual++;  // Incrementa o número da linha
        }
        fclose(arquivo);
    }

    if (encontrado) {
        // Se o usuário foi encontrado
        printf("Jogar como %s? (s/n): ", nome);
        scanf(" %c", &resposta);
        if (resposta == 's' || resposta == 'S') {
			cpClear();
            printf("\n\nBem-vindo de volta, %s! Sua pontuação atual é %d.\n\n", nome, pontuacao);
			cpSleep(3);
            return linhaAtual;  // Retorna o índice da linha do usuário
        } else {
            printf("Operação cancelada.\n");
			cpSleep(1);
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
				cpSleep(1);
                return linhaAtual; //retorna a linha do novo usuário
            } else {
                printf("Erro ao abrir o arquivo para cadastro.\n");
				cpSleep(1);
                exit(1);
            }
        } else {
            printf("Operação cancelada.\n");
			cpSleep(1);
            exit(1);
        }
    }
}

void exibeRanking() {
    FILE *arquivo;
    Usuario usuarios[MAX_USUARIOS];
    int totalUsuarios = 0;

    // Abrir o arquivo para leitura
    arquivo = fopen("usuarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: Não foi possível abrir o arquivo usuarios.txt\n");
		cpSleep(1);
        exit (1);
    }

    // Ler os dados do arquivo e armazenar no vetor
    while (fscanf(arquivo, "%s %d", usuarios[totalUsuarios].nome, &usuarios[totalUsuarios].pontuacao) == 2) {
        totalUsuarios++;
        if (totalUsuarios >= MAX_USUARIOS) {
            printf("Aviso: Número máximo de usuários excedido.\n");
			cpSleep(1);
            break;
        }
    }

    fclose(arquivo);

    // Ordenar o vetor em ordem decrescente de pontuação
    qsort(usuarios, totalUsuarios, sizeof(Usuario), comparaUsuarios);

    // Exibir o ranking
    printf("\n=== Ranking de Jogadores ===\n");
    for (int i = 0; i < totalUsuarios; i++) {
        printf("%s %d\n", usuarios[i].nome, usuarios[i].pontuacao);
    }
}

int comparaUsuarios(const void *a, const void *b) {
    Usuario *usuarioA = (Usuario *)a;
    Usuario *usuarioB = (Usuario *)b;

    return usuarioB->pontuacao - usuarioA->pontuacao; // Decrescente
}

int validaLetra(const char *palavra, int *erros, int *acertos)
{
	char letra;
	
	//até que a letra inserida seja válida:
	//pede que o usuário insira uma letra, limpa o buffer para que apenas uma letra seja lida, registra a letra inserida em maiúscula
	do{

		printf("\ninsira uma letra: ");
		scanf(" %c", &letra);
		fflush(stdin);
		letra = toupper(letra);

	}while(!atualizarLetrasAdivinhadas(letrasAdivinhadas, &numAdivinhacoes, letra)); //verifica se letra inserida é válida
	
	//verifica se a letra inserida está na palavra, incrementa acertos e retorna o indice caso sim, caso não, incrementa a contagem de erros	
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
			printf("a letra %c já foi inserida!\n", letra);
			return false;
		}
		
	}
	letrasAdivinhadas[*numAdivinhacoes] = letra;
	(*numAdivinhacoes)++;
	return true;
}

void desenhaGraficos(const char *palavra, char letrasAdvinhadas[])
{
	
	//limpa o terminal
	cpClear();

	printf("\n\n");

	desenhaForca(erros);

	// insere as letras que foram encontradas pelo jogador, insere barra para letras que não foram encontradas
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

	//mostra ao jogador quais letras foram adivinhadas até agora
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
	else //caso o jogador tenha perdido o jogo, mostrar a palavra por completo
	{
		for (int i = 0; i < strlen(palavra); i++)
		{
			printf("%c ", palavra[i]);
		}
	}
	

}

int desenhaForca(int erros)
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

void cadastrarPalavra() {
    char palavra[MAX_PALAVRA];
    char palavraConvertida[MAX_PALAVRA];
    int valida = 1;

    printf("Digite a palavra que deseja cadastrar (sem acentos, sem cedilha, apenas letras): ");
    scanf("%s", palavra);

	if (strlen(palavra) < 6) {
        printf("Erro: A palavra deve ter pelo menos 6 letras.\n");
		cpSleep(1);
        exit(1);
    }

    // Validar a palavra
    for (int i = 0; palavra[i] != '\0'; i++) {
        if (!isalpha(palavra[i]) || strchr("çÇáàâãéèêíìîóòôõúùû", palavra[i]) != NULL) {
            valida = 0;
            break;
        }
    }

    if (!valida) {
        printf("Palavra inválida! Certifique-se de usar apenas letras sem acentos, sem cedilha e pelo menos 6 letras.\n");
		cpSleep(2);
        exit (1);
    }

    // Converter para maiúsculas
    for (int i = 0; palavra[i] != '\0'; i++) {
        palavraConvertida[i] = toupper(palavra[i]);
    }
    palavraConvertida[strlen(palavra)] = '\0';

	// Verificar se a palavra já existe no arquivo
    if (palavraJaExiste(palavraConvertida, "dict.txt")) {
        printf("Erro: A palavra \"%s\" já está cadastrada no sistema.\n", palavraConvertida);
		cpSleep(2);
        exit(1);
    }

    // Abrir o arquivo em modo de adição
    FILE *arquivo = fopen("dict.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo dict.txt para escrita.\n");
		cpSleep(2);
        exit(1);
    }

    // Escrever a palavra convertida no arquivo
    fprintf(arquivo, "%s\n", palavraConvertida);
    fclose(arquivo);

    printf("Palavra \"%s\" cadastrada com sucesso!\n", palavraConvertida);
	cpSleep(2);
}

int calculaPontuacao(int acertos, int erros, bool vitoria) {
	int pontuacaoTotal;
	int pontuacaoErros = 50 * erros;
	int pontuacaoAcertos = 100 * acertos;
	if(vitoria){
		pontuacaoTotal = (pontuacaoAcertos - pontuacaoErros) + 300;
	} else {
		pontuacaoTotal = pontuacaoAcertos - pontuacaoErros;
	}

	return pontuacaoTotal;
}

void atualizaPontuacao(const char* arquivo, int indiceUsuario, int acertos, int erros, bool acertouPalavra) {
    FILE* file = fopen(arquivo, "r+");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", arquivo);
		cpSleep(1);
        return;
    }

    char linha[100]; // Para armazenar linhas do arquivo
    char nome[50];
    int pontuacao;
    int linhaAtual = 0;
    int pontosAdicionais = calculaPontuacao(acertos, erros, acertouPalavra);

    // Cria um arquivo temporário para armazenar as alterações
    FILE* tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
		cpSleep(1);
        fclose(file);
        return;
    }

    // Lê o arquivo original linha por linha
    while (fgets(linha, sizeof(linha), file) != NULL) {
        // Analisa a linha para obter nome e pontuação
        if (sscanf(linha, "%s %d", nome, &pontuacao) == 2) {
            if (linhaAtual == indiceUsuario) {
                // Atualiza a pontuação se for a linha correta
                pontuacao += pontosAdicionais;
				if (pontuacao < 0)
				{
					pontuacao = 0;
				}
                fprintf(tempFile, "%s %d\n", nome, pontuacao);
                printf("Pontuação de %s atualizada com sucesso para %d pontos!\n", nome, pontuacao);
				cpSleep(1);
            } else {
                // Copia a linha sem alterações
                fprintf(tempFile, "%s %d\n", nome, pontuacao);
            }
        } else {
            // Copia linhas mal formatadas ou vazias sem alteração
            fprintf(tempFile, "%s", linha);
        }
        linhaAtual++;
    }

    fclose(file);
    fclose(tempFile);

    // Substitui o arquivo original pelo temporário
    remove(arquivo);
    rename("temp.txt", arquivo);
}

int palavraJaExiste(const char *palavra, const char *nomeArquivo) {
    char linha[MAX_PALAVRA];
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
		cpSleep(1);
        return 0;
    }

    while (fgets(linha, MAX_PALAVRA, arquivo) != NULL) {
        // Remover o caractere de nova linha (\n) ao final da linha
        linha[strcspn(linha, "\n")] = '\0';
        if (strcmp(linha, palavra) == 0) {
            fclose(arquivo);
            return 1; // Palavra encontrada
        }
    }

    fclose(arquivo);
    return 0; // Palavra não encontrada
}

void exibirCreditos() {
    printf("======================================================\n");
    printf("CRÉDITOS\n");
    printf("======================================================\n");
    printf("Desenvolvedores:\n");
    printf("- Pedro Madruga\n");
    printf("- Bruno Máximo\n");
    printf("- Thales Santana\n");
    printf("- Felipe Borras\n");
    printf("======================================================\n");
    printf("Objetivo do Trabalho:\n");
    printf("Desenvolver um jogo da forca funcional, utilizando\n");
    printf("a linguagem de programação C, com a possibilidade de\n");
    printf("cadastro de novas palavras, além de um sistema de\n");
    printf("cadastro de usuários e ranking entre os jogadores.\n");
    printf("======================================================\n");
    printf("Plataformas de Desenvolvimento:\n");
    printf("- Visual Studio Code (VSCode)\n");
    printf("- GitHub\n");
    printf("======================================================\n");
    printf("Este jogo foi desenvolvido para a disciplina:\n");
    printf("- Técnicas e Desenvolvimento de Algoritmos\n");
    printf("  Turma: C | Turno: Manhã\n");
    printf("  Professor: Walace S. Bonfim\n");
    printf("======================================================\n");
    printf("Obrigado por jogar!\n");
    printf("======================================================\n");
	cpSleep(2);
}

void cpSleep(int segundos)
{
#ifdef _WIN32
    Sleep(segundos * 1000); //caso o sistema seja WINDOWS
#else
    sleep(segundos); //caso o sistema seja LINUX/MACOS
#endif
}

void cpClear()
{
	#ifdef _WIN32
        system("cls");  //caso o sistema seja WINDOWS
    #else
        system("clear"); //caso o sistema seja LINUX/MACOS
    #endif
}

void voltarMenu() {
    char resposta;

    while (1) { // Loop para validar a entrada do usuário
        printf("\nDeseja voltar ao menu? (s/n): ");
        scanf(" %c", &resposta);

        resposta = toupper(resposta); 
        if (resposta == 'S') {
            // limpa o terminal e retorna normalmente, permitindo que o programa continue
			cpClear();
            return;
        } else if (resposta == 'N') {
            // Sai do programa
            printf("\nEncerrando o programa...\n");
			cpSleep(2);
            exit(0);
        } else {
            // Entrada inválida, solicita novamente
            printf("Entrada inválida. Por favor, digite 's' ou 'n'.\n");
        }
    }
}
