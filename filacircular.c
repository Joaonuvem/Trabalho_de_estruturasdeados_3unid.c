#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//declaração de uma variavel do tipo NOssa
typedef struct NOssa {
    int valor;
    //aponta para o proximo NO.
    struct NOssa* prox; 
} NOssa;

//criação de um nó
NOssa* criarNo(int valor) {
    //alocação dinamica
    NOssa* novo = (NOssa*)malloc(sizeof(NOssa));
    //teste de erro de alocação de memoria
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    //o novo Nó recebe o valor e armazena NOssa seu valor
    novo->valor = valor;
    //aponta para si mesmo.
    novo->prox = novo; 
    return novo;
}
//inserir um item  fim da lista.
void inserirFim(NOssa** cabeca, int valor) {
    // cria um NOssa
    NOssa* novo = criarNo(valor);
    //confere se a lista esta vazia
    if (!(*cabeca)) {
        //atribui oo novo NOssa a cabeça.
        *cabeca = novo; 
        return;
    }
    //Percorre a lista até chegar Nossa último nó, que aponta de volta para a cabeça.
    NOssa* temp = *cabeca;
    while (temp->prox != *cabeca) {
        temp = temp->prox;
    }
    // faz o ultimo Nossa apontar para o novo nó.
    temp->prox = novo;
    // faz o ultimo Nossa apontar para o Nó inicial
    novo->prox = *cabeca; 
}
//remove um NOssa
void removerNo(NOssa** cabeca, int valor) {
  //confere se a lista está vazia,
    if (!(*cabeca)) return;
    
    NOssa* atual = *cabeca, *anterior = NULL;
    /*o atual percorre a lista e o anterior serve como uma variavel auxiliar
    o do while sera executado até voltar ao inicio da lista*/
    do {
        if (atual->valor == valor) { 
            //se for o unico Nossa da lista, a lista fica vazia
            if (atual == *cabeca && atual->prox == *cabeca) { 
                free(atual);
                *cabeca = NULL;
                return;
            }
            //se formos remover a cabeça, então a cabeça deve ser atualizada.
            if (atual == *cabeca) { 
                NOssa* temp = *cabeca;
                //percorre até achar o útlimo Nó
                while (temp->prox != *cabeca) temp = temp->prox;
                //atualiza a cabeça da lista para o proximo Nó
                *cabeca = atual->prox;
                //Atualiza o ponteiro prox do último nó para apontar para a nova cabeça, mantendo a circularidade.
                temp->prox = *cabeca;
            // caso não, apenas segue o baile
            } else {
                anterior->prox = atual->prox;
            }
            //libera da memoria o atual 
            free(atual);
            return;
        }
        //atualiza atual mas mantendo o controle de seu anterior
        anterior = atual;
        atual = atual->prox;
    } while (atual != *cabeca);
    
    printf("Valor %d não encontrado!\n", valor);
}
//função simples de exibição
void exibirLista(NOssa* cabeca) {
    if (!cabeca) {
        printf("Lista vazia!\n");
        return;
    }
    
    NOssa* temp = cabeca;
    do {
        printf("%d -> ", temp->valor);
        temp = temp->prox;
    } while (temp != cabeca);
    printf("(volta ao início)\n");
}

int main() {
    setlocale(LC_ALL,"portuguese");
    
    NOssa* lista = NULL;
    int n = 0;
    printf("Digite o primeiro valor da pilha: ");
    scanf("%d", &n);
    inserirFim(&lista, n);
    printf("Digite mais um valor para a pilha: ");
    scanf("%d", &n);
    inserirFim(&lista, n);
    printf("Mais um valor ai, pfvr: ");
    scanf("%d", &n);;
    inserirFim(&lista, n);
    
    printf("Lista circular:");
    exibirLista(lista);
    
    printf("Digite o valor que você deseja remover: ");
    scanf("%d",&n);
    removerNo(&lista, n);

    printf("Após remover 20:\n");
    exibirLista(lista);

    printf("Adicione so mais um valor a pilha, é o útilmo, eu prometo: ");
    scanf("%d", &n);
    inserirFim(&lista, n);

    printf("Após o novo valor ser acrescentado a lista:\n");
    exibirLista(lista);

    printf("\n\n");
    printf("----------------------------------------------------------------------------------------------\n");
    printf("A vida é uma mentira, somos marionetes de um sistem que nos torna escravos de nossos trabalhos\nGoverno são uma farsa usadas para manipular nossas vidas, FUJA,FUJA PELA SUA VIDA.\n");
    printf("----------------------------------------------------------------------------------------------");
    printf("\n\n");
    
    return 0;
}
