// Nome: Aurora Isabel Richaud Dominguez	Turma: 33C
// Matricula: 2311851

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOME 81
#define MAX_TEL 21
#define LETRAS 26
#define TRUE 1
#define FALSE 0

struct contato {
	char nome[MAX_NOME];
	char telefone[MAX_TEL];
	struct contato* prox;
};
typedef struct agenda {
	struct contato* vetor[LETRAS];
} Agenda;

/*[1] Escreva a função criaAgenda(void) que cria a agenda, alocando memória e inicializando o vetor (alocado estaticamente) com NULL. */
Agenda* criaAgenda(void) {
	Agenda* agenda = (Agenda*)malloc(sizeof(Agenda));
	if (agenda == NULL) return NULL;
	for (int i = 0; i < LETRAS; i++) {
		agenda->vetor[i] = NULL;
	}
	return agenda;
}

/*[2] Escreva a função insereOrd que recebe um novo contato e insere em ordem alfabética. Esta função retorna false (i.e., 0) se ocorrer problema de alocação de memória. */
int insereOrd(Agenda* lst, char* nome, char* telefone) {
	int pos = toupper(nome[0]) - 'A';
	struct contato* novo, * ant = NULL;

	novo = (struct contato*)malloc(sizeof(struct contato));
	if (novo == NULL) return FALSE;
	strcpy(novo->nome, nome);
	strcpy(novo->telefone, telefone);

	ant = lst->vetor[pos];
	if (ant == NULL)
	{
		novo->prox = NULL;
		lst->vetor[pos] = novo;
	}
	else if (strcmp(nome, ant->nome) == -1) {
		novo->prox = ant;
		lst->vetor[pos] = novo;
	}
	else {
		while (ant->prox != NULL && strcmp(nome, ant->prox->nome) != -1)
			ant = ant->prox;
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	return TRUE;
}

/*[3] Escreva a função listaLetra que, recebe a agenda e uma letra, e lista todos os contatos que começam com a letra dada.*/
void listaLetra(Agenda* lst, char letra) {
	int pos = toupper(letra) - 'A';
	struct contato* contatos = lst->vetor[pos];
	printf("\t[CONTATOS COM %c]\n", toupper(letra));
	if (contatos == NULL) printf("Sem contatos com a letra %c\n\n\n", toupper(letra));
	else {
		printf("Nome:\t\t\tTelefone:\n");
		while (contatos != NULL) {
			printf("%-20s\t%s\n", contatos->nome, contatos->telefone);
			contatos = contatos->prox;
		}
		printf("\n\n");
	}
}

/*[4] Escreva a função retira que retira um nome da agenda (se houver mais de um contato com o mesmo nome, a função retira apenas o primeiro).
Esta função recebe o nome e retorna false (i.e. 0) se o nome não existe na agenda. */
int retira(Agenda* agenda, char* nome) {
	int pos = toupper(nome[0]) - 'A';
	struct contato* contatos = agenda->vetor[pos], * temp;

	if (contatos == NULL) {
		printf("[ CONTATO %s INEXISTENTE ]\n\n\n", nome);
		return FALSE;
	}


	if (!strcmp(nome, contatos->nome)) {
		agenda->vetor[pos] = contatos->prox;
		free(contatos);
		printf("[ CONTATO %s FOI RETIRADO ]\n\n\n", nome);
		return TRUE;
	}

	while (contatos->prox != NULL) {
		if (!strcmp(nome, contatos->prox->nome)) {
			temp = contatos->prox;
			contatos->prox = temp->prox;
			free(temp);
			printf("[ CONTATO %s FOI RETIRADO ]\n\n\n", nome);
			return TRUE;
		}
		contatos = contatos->prox;
	}
	printf("[ CONTATO %s INEXISTENTE ]\n\n\n", nome);
	return FALSE;
}

/*[5] Escreva a função liberaCadastro que libera toda a memória alocada. */
void liberaCadastro(Agenda* lst) {
	struct contato* temp;
	for (int i = 0; i < LETRAS; i++) {
		while ((temp = lst->vetor[i]) != NULL) {
			lst->vetor[i] = lst->vetor[i]->prox;
			free(temp);
		}
	}
	free(lst);

	printf("\n[ MEMORIA LIBERADA ]\n\n\n");
}

int main(void) {
	Agenda* agenda = criaAgenda();

	insereOrd(agenda, "Maya Richaud", "(21) 91111-1111");
	insereOrd(agenda, "Megan Smith", "(21) 92222-2222");
	insereOrd(agenda, "Michael Johnson", "(21) 93333-3333");
	insereOrd(agenda, "Matthew Brown", "(21) 94444-4444");
	insereOrd(agenda, "Mia Martinez", "(21) 95555-5555");
	insereOrd(agenda, "Aurora Richaud Pinto", "(21) 96666-6666");
	insereOrd(agenda, "Alice Doe", "(21) 97777-7777");
	insereOrd(agenda, "Bob Wilson", "(21) 98888-8888");
	insereOrd(agenda, "David Rodriguez", "(21) 99999-9999");
	insereOrd(agenda, "Sophia Fernandez", "(21) 91112-2222");
	insereOrd(agenda, "Rose Pinto", "(21) 92222-2222");
	insereOrd(agenda, "Bruno Richaud Pinto", "(21) 93333-3333");
	insereOrd(agenda, "Olivia Torres", "(21) 91115-5555");
	insereOrd(agenda, "Noah Kim", "(21) 91116-6666");
	insereOrd(agenda, "Isabella Hernandez", "(21) 91117-7777");
	insereOrd(agenda, "Mateo Ramirez", "(21) 91118-8888");
	insereOrd(agenda, "Olivia Torres", "(21) 91119-9999");
	insereOrd(agenda, "Alexander Lopez", "(21) 92222-1111");
	insereOrd(agenda, "Valentina Kim", "(21) 93333-2222");

	listaLetra(agenda, 'M');
	listaLetra(agenda, 'B');
	listaLetra(agenda, 'O');
	listaLetra(agenda, 'x');

	retira(agenda, "Olivia Torres");
	listaLetra(agenda, 'O');

	retira(agenda, "Bob Wilson");
	listaLetra(agenda, 'B');

	liberaCadastro(agenda);

	return 0;
}
