#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define MAX_USUARIOS 100
#define MAX_FERRAMENTAS 100
#define MAX_EMPRESTIMOS 100

typedef struct {
    char nome[100];
    int cracha;
    char telefone[20];
    time_t dataCadastro;
} Usuario;

typedef struct {
    char nome[100];
    int numero;
    char marca[100];
    time_t dataCadastro;
} Ferramenta;

typedef struct {
    int crachaUsuario;
    int numeroFerramenta;
    time_t dataEmprestimo;
} Emprestimo;

Usuario usuarios[MAX_USUARIOS];
Ferramenta ferramentas[MAX_FERRAMENTAS];
Emprestimo emprestimos[MAX_EMPRESTIMOS];
int numUsuarios = 0;
int numFerramentas = 0;
int numEmprestimos = 0;

void salvarRelatorio() {
    FILE *arquivo = fopen("relatorio.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Escrever os usu�rios no arquivo
    fprintf(arquivo, "===== USU�RIOS CADASTRADOS =====\n");
    for (int i = 0; i < numUsuarios; i++) {
        fprintf(arquivo, "Nome: %s\n", usuarios[i].nome);
        fprintf(arquivo, "N�mero do Crach�: %d\n", usuarios[i].cracha);
        fprintf(arquivo, "Telefone: %s\n", usuarios[i].telefone);
        fprintf(arquivo, "Data do Cadastro: %s", ctime(&usuarios[i].dataCadastro));
        fprintf(arquivo, "\n");
    }

    // Escrever as ferramentas no arquivo
    fprintf(arquivo, "===== FERRAMENTAS CADASTRADAS =====\n");
    for (int i = 0; i < numFerramentas; i++) {
        fprintf(arquivo, "Nome: %s\n", ferramentas[i].nome);
        fprintf(arquivo, "N�mero: %d\n", ferramentas[i].numero);
        fprintf(arquivo, "Marca: %s\n", ferramentas[i].marca);
        fprintf(arquivo, "Data do Cadastro: %s", ctime(&ferramentas[i].dataCadastro));
        fprintf(arquivo, "\n");
    }

    // Escrever os empr�stimos no arquivo
    fprintf(arquivo, "===== EMPR�STIMOS REALIZADOS =====\n");
    for (int i = 0; i < numEmprestimos; i++) {
        fprintf(arquivo, "N�mero do Crach�: %d\n", emprestimos[i].crachaUsuario);
        fprintf(arquivo, "N�mero da Ferramenta: %d\n", emprestimos[i].numeroFerramenta);
        fprintf(arquivo, "Data do Empr�stimo: %s", ctime(&emprestimos[i].dataEmprestimo));
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    printf("Relat�rio salvo com sucesso.\n");
}

void lerRelatorio() {
    FILE *arquivo = fopen("relatorio.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linha[200];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
    }

    fclose(arquivo);
}

void cadastrarUsuario() {
    Usuario novoUsuario;

    printf("===== CADASTRO DE USU�RIO =====\n");
    printf("Nome: ");
    scanf(" %[^\n]", novoUsuario.nome);
    printf("N�mero do Crach�: ");
    scanf("%d", &novoUsuario.cracha);
    printf("Telefone: ");
    scanf(" %[^\n]", novoUsuario.telefone);
    novoUsuario.dataCadastro = time(NULL);

    usuarios[numUsuarios++] = novoUsuario;

    printf("Usu�rio cadastrado com sucesso.\n");
}

void cadastrarFerramenta() {
    Ferramenta novaFerramenta;

    printf("===== CADASTRO DE FERRAMENTA =====\n");
    printf("Nome: ");
    scanf(" %[^\n]", novaFerramenta.nome);
    printf("N�mero: ");
    scanf("%d", &novaFerramenta.numero);
    printf("Marca: ");
    scanf(" %[^\n]", novaFerramenta.marca);
    novaFerramenta.dataCadastro = time(NULL);

    ferramentas[numFerramentas++] = novaFerramenta;

    printf("Ferramenta cadastrada com sucesso.\n");
}

void emprestarFerramenta() {
    int crachaUsuario, numeroFerramenta;
    int usuarioEncontrado = 0, ferramentaEncontrada = 0;

    printf("===== EMPR�STIMO DE FERRAMENTA =====\n");
    printf("N�mero do Crach� do Usu�rio: ");
    scanf("%d", &crachaUsuario);
    printf("N�mero da Ferramenta: ");
    scanf("%d", &numeroFerramenta);

    // Verificar se o usu�rio existe
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].cracha == crachaUsuario) {
            usuarioEncontrado = 1;
            break;
        }
    }

    if (!usuarioEncontrado) {
        printf("Usu�rio n�o encontrado.\n");
        return;
    }

    // Verificar se a ferramenta existe
    for (int i = 0; i < numFerramentas; i++) {
        if (ferramentas[i].numero == numeroFerramenta) {
            ferramentaEncontrada = 1;
            break;
        }
    }

    if (!ferramentaEncontrada) {
        printf("Ferramenta n�o encontrada.\n");
        return;
    }

    // Verificar se a ferramenta j� est� emprestada
    for (int i = 0; i < numEmprestimos; i++) {
        if (emprestimos[i].numeroFerramenta == numeroFerramenta) {
            printf("A ferramenta j� est� emprestada.\n");
            return;
        }
    }

    Emprestimo novoEmprestimo;
    novoEmprestimo.crachaUsuario = crachaUsuario;
    novoEmprestimo.numeroFerramenta = numeroFerramenta;
    novoEmprestimo.dataEmprestimo = time(NULL);

    emprestimos[numEmprestimos++] = novoEmprestimo;

    printf("Ferramenta emprestada com sucesso.\n");
}

void devolverFerramenta() {
    int numeroFerramenta;
    int emprestimoEncontrado = 0;

    printf("===== DEVOLU��O DE FERRAMENTA =====\n");
    printf("N�mero da Ferramenta: ");
    scanf("%d", &numeroFerramenta);

    for (int i = 0; i < numEmprestimos; i++) {
        if (emprestimos[i].numeroFerramenta == numeroFerramenta) {
            emprestimoEncontrado = 1;
            for (int j = i; j < numEmprestimos - 1; j++) {
                emprestimos[j] = emprestimos[j + 1];
            }
            numEmprestimos--;
            break;
        }
    }

    if (emprestimoEncontrado) {
        printf("Ferramenta devolvida com sucesso.\n");
    } else {
        printf("Ferramenta n�o est� emprestada.\n");
    }
}

void exibirMenu() {
        printf("\n");
        printf("=======================================\n");
        printf("|         SISTEMA DE EMPR�STIMO        |\n");
        printf("|           DE FERRAMENTAS             |\n");
        printf("========================================\n");
        printf("|                                      |\n");
        printf("| 1 - Cadastrar Usu�rio                |\n");
        printf("| 2 - Cadastrar Ferramenta             |\n");
        printf("| 3 - Emprestar Ferramentas            |\n");
        printf("| 4 - Devolver Ferramentas             |\n");
        printf("| 5 - Salvar Relat�rio                 |\n");
        printf("| 6 - Ler Relat�rio                    |\n");
        printf("| 0 - Sair                             |\n");
        printf("|                                      |\n");
        printf("========================================\n");
        printf("Op��o: ");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarUsuario();
                break;
            case 2:
                cadastrarFerramenta();
                break;
            case 3:
                emprestarFerramenta();
                break;
            case 4:
                devolverFerramenta();
                break;
            case 5:
                salvarRelatorio();
                break;
            case 6:
                lerRelatorio();
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Op��o inv�lida.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
