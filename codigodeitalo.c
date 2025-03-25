#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura que representa uma música
typedef struct Musica {
    char titulo[100];
    char artista[100];
    int duracao;  // duração em segundos
    struct Musica *proxima;
} Musica;

// Função para criar uma nova música
Musica* criar_musica(const char *titulo, const char *artista, int duracao) {
    Musica *nova = (Musica *)malloc(sizeof(Musica));
    strcpy(nova->titulo, titulo);
    strcpy(nova->artista, artista);
    nova->duracao = duracao;
    nova->proxima = nova;  // Aponta para o próximo nó
    return nova;
}

// Função para adicionar música no final da playlist
void adicionar_musica(Musica **playlist, const char *titulo, const char *artista, int duracao) {
    Musica *nova = criar_musica(titulo, artista, duracao);

    if (*playlist == NULL) {
        *playlist = nova;
    } else {
        Musica *temp = *playlist; // Cria ponteiro auxiliar
        while (temp->proxima != *playlist) { // Percorre até encontrar o último nó
            temp = temp->proxima;
        }
        temp->proxima = nova; // O nó antigo passa a apontar para o novo
        nova->proxima = *playlist; // O novo nó aponta para a cabeça
    }
}

// Função para remover música por título
void remover_musica(Musica **playlist, const char *titulo) {
    if (*playlist == NULL) return;

    Musica *atual = *playlist; // Ponteiro auxiliar apontando pro topo
    Musica *anterior = NULL;

    // Caso a música a remover seja a cabeça da lista
    if (strcmp(atual->titulo, titulo) == 0) { // Verifica se a música escolhida é a cabeça
        if (atual->proxima == *playlist) {
            free(atual);
            *playlist = NULL; // Se só tem uma música a lista fica vazia
        } else {
            while (atual->proxima != *playlist) { // Percorre até encontrar o último nó
                atual = atual->proxima;
            }
            Musica *remover = *playlist; 
            atual->proxima = remover->proxima;  // O nó aponta agora para a música a seguir
            *playlist = remover->proxima; // Atualiza a cabeça da lista
            free(remover); // Libera memória
        }
        return;
    }

    anterior = *playlist;
    atual = (*playlist)->proxima; // O ponteiro atual começa no segundo nó
    while (atual != *playlist && strcmp(atual->titulo, titulo) != 0) { // Percorre a playlist
        anterior = atual; // Os dois nós percorrem a lista
        atual = atual->proxima; // 
    }

    if (atual == *playlist) return; // Não encontrou

	// Quando a música é encontrada
    anterior->proxima = atual->proxima; // O nó anterior agora aponta para o nó que está após ao atual
    free(atual); // Libera o nó removido
}

// Função para exibir toda a playlist
void exibir_playlist(Musica *playlist) {
    if (playlist == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    Musica *temp = playlist;
    printf("\n--- Playlist Atual ---\n");
    do {
        printf("Título: %s | Artista: %s | Duração: %d segundos\n", temp->titulo, temp->artista, temp->duracao);
        temp = temp->proxima;
    } while (temp != playlist); // Percorre todos os nós e para ao chegar á cabeça
    printf("-----------------------\n");
}


// Função principal de teste
int main() {
    setlocale(LC_ALL,"portuguese");

    Musica *playlist = NULL;

    adicionar_musica(&playlist, "Malevo", "Romeo Santos", 240);
    adicionar_musica(&playlist, "Futebol no Inferno", "Caju e Castanha", 200);
    adicionar_musica(&playlist, "Rap do Solitário", "MC Marcinho", 360);
    adicionar_musica(&playlist, "Tropa do Oruam", "Oruam", 180);
    adicionar_musica(&playlist, "Espresso", "Sabrina Carpenter", 180);

    exibir_playlist(playlist);

    remover_musica(&playlist, "Tropa do Oruam");
    printf("\nApós remover 'Oruam':\n");
    exibir_playlist(playlist);
	

    return 0;
}

