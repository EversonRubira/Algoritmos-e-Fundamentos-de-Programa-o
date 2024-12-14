#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir constantes simbólicas
#define MAX_VISITAS 1000
#define MAX_EMBAIXADORES 100

// Definição de estruturas
typedef struct {
    int numeroEstudante;
    char escola[20];
    char nome[50];
    char nif[10];
} Embaixador;

typedef struct {
    int idVisita;
    Embaixador embaixadores[9]; // Máximo de 9 embaixadores por visita
    int qtdEmbaixadores;
    char estado[20]; // Planeamento, autorizada, etc.
    char local[50];
    char data[11]; 
} Visita;

// Declaração de protótipos de funções
void exibirMenu();
void listarVisitas();
void listarEmbaixadores();
void consultarVisitaPorID();
void consultarEmbaixadorPorNumero();
void adicionarVisita();
void adicionarEmbaixador();
void autorizarVisita();
void sair();
void preencherDadosTeste(); 

// Vetores globais para armazenar os dados
Visita visitas[MAX_VISITAS];
Embaixador embaixadores[MAX_EMBAIXADORES];
int totalVisitas = 0;
int totalEmbaixadores = 0;

int main() {
    int opcao;

    preencherDadosTeste(); // Preencher dados fictícios

    do {
        exibirMenu();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                listarVisitas();
                break;
            case 2:
                listarEmbaixadores();
                break;
            case 3:
                consultarVisitaPorID();
                break;
            case 4:
                consultarEmbaixadorPorNumero();
                break;
            case 5:
                adicionarVisita();
                break;
            case 6:
                adicionarEmbaixador();
                break;
            case 7:
                autorizarVisita();
                break;    
            case 15:
                sair();
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 15);

    return 0;
}

// Funções do programa
void exibirMenu() {
    printf("\n=== Menu Principal ===");
    printf("\n1. Listar visitas e detalhes");
    printf("\n2. Listar embaixadores e detalhes");
    printf("\n3. Consultar visita por ID");
    printf("\n4. Consultar embaixador por numero de estudante");
    printf("\n5. Adicionar visita");
    printf("\n6. Adicionar embaixador");
    printf("\n7. Autorizar visita");
    printf("\n15. Sair da aplicacao");
}


void listarVisitas() {
    if (totalVisitas == 0) {
        printf("\nNao ha visitas cadastradas.\n");
        return;
    }

    printf("\n=== Lista de Visitas ===\n");
    for (int i = totalVisitas - 1; i >= 0; i--) { // Ordem decrescente
        printf("\nID da Visita: %d\n", visitas[i].idVisita);
        printf("Estado: %s\n", visitas[i].estado);
        printf("Local: %s\n", visitas[i].local);
        printf("Data: %s\n", visitas[i].data);
        printf("Numero de Embaixadores: %d\n", visitas[i].qtdEmbaixadores);
    }
}

void listarEmbaixadores() {
    if (totalEmbaixadores == 0) {
        printf("\nNao ha embaixadores cadastrados.\n");
        return;
    }

    for (int i = 0; i < totalEmbaixadores - 1; i++) {
        for (int j = 0; j < totalEmbaixadores - i - 1; j++) {
            if (strcmp(embaixadores[j].nome, embaixadores[j + 1].nome) > 0) {
                Embaixador temp = embaixadores[j];
                embaixadores[j] = embaixadores[j + 1];
                embaixadores[j + 1] = temp;
            }
        }
    }

    printf("\n=== Lista de Embaixadores ===\n");
    for (int i = 0; i < totalEmbaixadores; i++) {
        printf("\nNumero de Estudante: %d\n", embaixadores[i].numeroEstudante);
        printf("Escola: %s\n", embaixadores[i].escola);
        printf("Nome: %s\n", embaixadores[i].nome);
        printf("NIF: %s\n", embaixadores[i].nif);
    }
}

void consultarVisitaPorID() {
    if (totalVisitas == 0) {
        printf("\nNao ha visitas cadastradas.\n");
        return;
    }

    int idProcurado;
    printf("\nDigite o ID da visita que deseja consultar: ");
    scanf("%d", &idProcurado);

    for (int i = 0; i < totalVisitas; i++) {
        if (visitas[i].idVisita == idProcurado) {
            printf("\n=== Detalhes da Visita ===\n");
            printf("ID da Visita: %d\n", visitas[i].idVisita);
            printf("Estado: %s\n", visitas[i].estado);
            printf("Local: %s\n", visitas[i].local);
            printf("Data: %s\n", visitas[i].data);
            printf("Numero de Embaixadores: %d\n", visitas[i].qtdEmbaixadores);
            return;
        }
    }

    printf("\nVisita com ID %d nao encontrada.\n", idProcurado);
}

void consultarEmbaixadorPorNumero() {
    if (totalEmbaixadores == 0) {
        printf("\nNão há embaixadores cadastrados.\n");
        return;
    }

    int numeroProcurado;
    printf("\nDigite o numero do estudante que deseja consultar: ");
    scanf("%d", &numeroProcurado);

    // Procurar o embaixador pelo número do estudante
    for (int i = 0; i < totalEmbaixadores; i++) {
        if (embaixadores[i].numeroEstudante == numeroProcurado) {
            printf("\n=== Detalhes do Embaixador ===\n");
            printf("Numero de Estudante: %d\n", embaixadores[i].numeroEstudante);
            printf("Escola: %s\n", embaixadores[i].escola);
            printf("Nome: %s\n", embaixadores[i].nome);
            printf("NIF: %s\n", embaixadores[i].nif);
            return;
        }
    }

    // Caso o número não seja encontrado
    printf("\nEmbaixador com o numero %d não encontrado.\n", numeroProcurado);
}

void adicionarVisita() {
    if (totalVisitas >= MAX_VISITAS) {
        printf("\nLimite de visitas atingido. Nao e possivel adicionar mais visitas.\n");
        return;
    }

    Visita novaVisita;
    novaVisita.idVisita = totalVisitas + 1; // Gerar ID automaticamente
    strcpy(novaVisita.estado, "Planeamento"); // Estado inicial

    printf("\nDigite o local da visita: ");
    fgets(novaVisita.local, sizeof(novaVisita.local), stdin);
    novaVisita.local[strcspn(novaVisita.local, "\n")] = '\0'; // Remover quebra de linha

    printf("Digite a data da visita (DD/MM/AAAA): ");
    fgets(novaVisita.data, sizeof(novaVisita.data), stdin);
    novaVisita.data[strcspn(novaVisita.data, "\n")] = '\0'; // Remover quebra de linha

    novaVisita.qtdEmbaixadores = 0; // Inicialmente sem embaixadores

    // Adicionar a nova visita ao vetor global
    visitas[totalVisitas] = novaVisita;
    totalVisitas++;

    printf("\nVisita adicionada com sucesso!\n");
    printf("ID da Visita: %d\n", novaVisita.idVisita);
}

void adicionarEmbaixador() {
    if (totalEmbaixadores >= MAX_EMBAIXADORES) {
        printf("\nLimite de embaixadores atingido. Nao e possivel adicionar mais embaixadores.\n");
        return;
    }

    Embaixador novoEmbaixador;

    // Inserir o número do estudante
    printf("\nDigite o numero do estudante: ");
    scanf("%d", &novoEmbaixador.numeroEstudante);
    getchar(); // Limpar o buffer do teclado

    // Verificar se o número já existe
    for (int i = 0; i < totalEmbaixadores; i++) {
        if (embaixadores[i].numeroEstudante == novoEmbaixador.numeroEstudante) {
            printf("\nErro: Ja existe um embaixador com o numero %d.\n", novoEmbaixador.numeroEstudante);
            return;
        }
    }

    // Inserir o nome do embaixador
    printf("Digite o nome completo: ");
    fgets(novoEmbaixador.nome, sizeof(novoEmbaixador.nome), stdin);
    novoEmbaixador.nome[strcspn(novoEmbaixador.nome, "\n")] = '\0'; // Remover quebra de linha

    // Inserir a escola do embaixador
    printf("Digite a escola: ");
    fgets(novoEmbaixador.escola, sizeof(novoEmbaixador.escola), stdin);
    novoEmbaixador.escola[strcspn(novoEmbaixador.escola, "\n")] = '\0'; // Remover quebra de linha

    // Inserir o NIF
    printf("Digite o NIF: ");
    fgets(novoEmbaixador.nif, sizeof(novoEmbaixador.nif), stdin);
    novoEmbaixador.nif[strcspn(novoEmbaixador.nif, "\n")] = '\0'; // Remover quebra de linha

    // Adicionar o novo embaixador ao vetor global
    embaixadores[totalEmbaixadores] = novoEmbaixador;
    totalEmbaixadores++;

    printf("\nEmbaixador adicionado com sucesso!\n");
}

void autorizarVisita() {
    if (totalVisitas == 0) {
        printf("\nNao ha visitas cadastradas.\n");
        return;
    }

    int idProcurado;
    printf("\nDigite o ID da visita que deseja autorizar: ");
    scanf("%d", &idProcurado);

    for (int i = 0; i < totalVisitas; i++) {
        if (visitas[i].idVisita == idProcurado) {
            if (strcmp(visitas[i].estado, "Planeamento") != 0) {
                printf("\nErro: Apenas visitas em 'Planeamento' podem ser autorizadas.\n");
                return;
            }
            if (visitas[i].qtdEmbaixadores < 2) {
                printf("\nErro: A visita precisa ter pelo menos 2 embaixadores atribuídos.\n");
                return;
            }

            strcpy(visitas[i].estado, "Autorizada");
            printf("\nVisita com ID %d autorizada com sucesso!\n", idProcurado);
            return;
        }
    }

    printf("\nVisita com ID %d nao encontrada.\n", idProcurado);
}


void sair() {
    printf("\nEncerrando o programa. Ate mais!\n");
}

void preencherDadosTeste() {
    visitas[0].idVisita = 1;
    strcpy(visitas[0].estado, "Planeamento");
    strcpy(visitas[0].local, "Escola Secundaria A");
    strcpy(visitas[0].data, "10/12/2024");
    visitas[0].qtdEmbaixadores = 2;
    totalVisitas++;

    visitas[1].idVisita = 2;
    strcpy(visitas[1].estado, "Autorizada");
    strcpy(visitas[1].local, "Escola Secundaria B");
    strcpy(visitas[1].data, "12/12/2024");
    visitas[1].qtdEmbaixadores = 3;
    totalVisitas++;

    embaixadores[0].numeroEstudante = 1;
    strcpy(embaixadores[0].escola, "Instituto Politecnico de Setubal - IPS");
    strcpy(embaixadores[0].nome, "Joao Silva");
    strcpy(embaixadores[0].nif, "123456789");
    totalEmbaixadores++;

    embaixadores[1].numeroEstudante = 2;
    strcpy(embaixadores[1].escola, "Instituto Politecnico de Setubal - IPS");
    strcpy(embaixadores[1].nome, "Maria Santos");
    strcpy(embaixadores[1].nif, "987654321");
    totalEmbaixadores++;

    embaixadores[2].numeroEstudante = 3;
    strcpy(embaixadores[2].escola, "Instituto Politecnico de Setubal - IPS");
    strcpy(embaixadores[2].nome, "Pedro Oliveira");
    strcpy(embaixadores[2].nif, "456123789");
    totalEmbaixadores++;

    printf("\nDados de teste preenchidos.\n");
}
