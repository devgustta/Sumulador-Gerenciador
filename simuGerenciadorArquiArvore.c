#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct direc{
    char name[50];
    int isFile; // 1 diretorio 2 arquivo
    struct direc *firstChild; // Nó para o primeiro filho
    struct direc *firstBro; // Nó para o primeiro irmão (Primeiro irmão apenas no diretorio pai, depois será o ponteiro para os proximos Bro)
}Direc;

typedef struct root{
    char nome[50];
    int isFile;
    Direc *child;
}Root;

char infos(){
    char nome[50];

    printf("Informe o nome: ");
    scanf("%s", &nome);

    return nome;
}

Direc* navegar(Direc **dir, Direc **atual){
    char name[50];

    printf("Informe o nome da pasta que deseja navegar: ");
    scanf("%s", &name);

    if((*dir)->firstChild == NULL){
        printf("Nenhum Arquivo neste diretorio!!");
    }

    Direc *aux = *dir; // agora os dois apontam para o mesmo nó

    while(aux->firstChild != NULL){
        if(aux->name != name){
            aux->firstChild = aux->firstBro;
        }
        //aux = aux->firstChild;
    }

    *atual = *aux;
}

Direc* criando(Root **arch, int op){
    Direc *novo = malloc(sizeof(Direc));
    if(novo){
        char nome = infos();
        strcpy(novo->name, nome);
        novo->isFile = op;
        novo->firstChild = NULL;
        novo->firstBro = NULL;

        Direc *aux = *arch;
        while(aux->firstBro != NULL){
            aux = aux->firstBro;
        }
        aux->firstBro = novo; // alterando o nó que tanto aux quanto fila aponta
    }
}

// Inicializar a struct root

int main(){
    Direc dir = {"User", 1, NULL, NULL}, *atual;
    Root root1 = {"C:", 1, &dir};
    int op;
    // Criar uma variavel que armazena o caminho atual(armazena o ponteiro da pasta atual)
    do{
        printf("\n\t1 - Criar Diretorio \n\t 2 - Criar Arquivo \n\t3 - Navegar \n\t4 - Excluir");
        scanf("%d", &op);

        switch(op){
        case 1:
            criando(&dir, 1);

        break;

        case 2:

        break;

        case 3:{
            int op;
            navegar(&dir, &atual); // variavel "atual" vai guardar o ponteiro da pasta em que estamos
            printf("\n\t 1 - sub-pasta");
            scanf("%d", &op);
        }
        break;
        }

    }while(op != 0);


}

