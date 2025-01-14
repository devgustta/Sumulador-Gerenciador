#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct direc{
    char name[50];
    int isFile; // 1 diretorio 2 arquivo
    struct Direc *firstChild; // Nó para o primeiro filho
    struct Direc *firstBro; // Nó para o primeiro irmão (Primeiro irmão apenas no diretorio pai, depois será o ponteiro para os proximos Bro)
}Direc;

typedef struct root{
    char nome[50];
    int isFile;
    Direc *child;
}Root;

char* infos(){
    static char nome[50];

    printf("Informe o nome: ");
    scanf("%s", &nome);

    return nome;
}

Direc* navegar(Direc **dir, Direc **atual) {
    char name[50];

    printf("Informe o nome da pasta que deseja navegar: ");
    scanf("%s", name);
    fflush(stdin);

    if ((*dir)->firstChild == NULL) { // Verifica se o diretório está vazio
        printf("Nenhum Arquivo neste diretório!!\n");
        return NULL;
    }

    Direc *aux = (*dir)->firstChild; // Começa no primeiro filho

    while (aux != NULL) {
        if (strcmp(aux->name, name) == 0) { // Verifica se o nome corresponde
            printf("Navegando para: %s\n", aux->name);
            *atual = aux; // Atualiza o diretório atual
            return aux;   // Retorna o novo diretório
        }
        aux = aux->firstBro; // Navega para o próximo irmão
    }

    printf("Pasta '%s' não encontrada.\n", aux->name);
    return NULL;
}


Direc* criando(Direc **arch, int op){
    Direc *novo = malloc(sizeof(Direc));
    if(novo){
        char *nome = infos();
        strcpy(novo->name, nome);
        novo->isFile = op;
        novo->firstChild = NULL;
        novo->firstBro = NULL;

        if (*arch == NULL) { // verificando se o topo , caso não esteja o else faz seu trabalho
            *arch = novo;   // arch nunca sera nulo, mas por questoes de segurança kkkkk, eu coloquei
        } else {
        Direc *aux = *arch;
        while (aux->firstBro != NULL) {
            aux = aux->firstBro;
        }
        aux->firstBro = novo;
        printf("Criado com sucesso");
        }

    }
}

// Inicializar a struct root

Direc dir = {"User", 1, NULL, NULL};
Root root1 = {"C:", 1, &dir};

int main(){
    Direc *atual = root1.child; // colocando o primeiro caminho no atual

    int op;
    // Criar uma variavel que armazena o caminho atual(armazena o ponteiro da pasta atual)
    do{
        printf("\n\t1 - Criar Diretorio \n\t2 - Criar Arquivo \n\t3 - Navegar \n\t4 - Excluir\n");
        scanf("%d", &op);
        fflush(stdin);

        switch(op){
        case 1:
            criando(&atual, 1);

        break;

        //case 2:

       // break;

        case 3:{
            int op;
            navegar(&dir, &atual); // variavel "atual" vai guardar o ponteiro da pasta em que estamos
            if (atual != NULL) {
                printf("Você está agora na pasta: %s\n", atual->name);
            } else {
                printf("Navegação falhou.\n");
            }
        }
        break;
        }

    }while(op != 0);

}
