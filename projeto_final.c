#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MAX_PLYLST 200
#define TAM_NOME 50
#define TAM_LOGIN 15
#define TAM_SENHA 15
#define TAM_PLAYLIST 100
#define TAM_TITULO 50
#define TAM_MUSICAS 100

struct Musica {
    int codigo;
    char titulo[TAM_TITULO];
    char artista[TAM_NOME];
};

struct Playlist {
    int codigo;
    int codUsuario;
    char titulo[TAM_TITULO];
    int qtdMusicas;
    int musicas[TAM_MUSICAS];
};

struct Usuario {
    int codigo;
    char nome[TAM_NOME];
    char login[TAM_LOGIN];
    char senha[TAM_SENHA];
    int qtdPlaylists;
    struct Playlist playlists[TAM_PLAYLIST];
    int qtdPlaylistsFav;
    int playlistsFav[TAM_PLAYLIST];
};

struct Usuario usuarios[TAM_MAX_PLYLST];
struct Musica musicas[TAM_MAX_PLYLST];
int usuarioCount = 0;
int musicaCount = 0;
int playlistCount = 0;

void generate_sample_data();
void display_main_menu();
void handle_admin_menu();
void handle_user_menu(struct Usuario *user);
int login_admin();
struct Usuario* login_user();
struct Usuario* register_user();
void list_users();
void consult_user();
void change_user_password();
void register_song();
void list_songs();
void consult_song();
void modify_song();
void delete_song();
void list_playlists();
void consult_playlist();
void listar_dados_usuario(struct Usuario *user);
void alterar_nome_usuario(struct Usuario *user);
void alterar_login_usuario(struct Usuario *user);
void alterar_senha_usuario(struct Usuario *user);
void listar_usuarios();
void consultar_usuarios();
void create_playlist();
void listar_suas_playlists(struct Usuario *user);
void listar_todas_playlists();
void consultar_playlists(struct Usuario *user);
void add_song_to_playlist(struct Usuario *user);
void delete_song_from_playlist(struct Usuario *user);
void delete_playlist(struct Usuario *user);
void favorite_playlist(struct Usuario *user);

int main() {
   generate_sample_data();
    while (1) {
        display_main_menu();
        int choice;
        scanf("%d", &choice);
        if (choice == 1) {
            if (login_admin()) {
                handle_admin_menu();
            }
        } else if (choice == 2) {
                struct Usuario *user = login_user();
            if (user == NULL) {
                printf("Usuário não encontrado. Deseja cadastrar um novo usuário? (s/n): ");
                char resposta;
                scanf(" %c", &resposta);
                if (resposta == 's' || resposta == 'S') {
                    user = register_user();
                }
            }
            if (user != NULL) {
                handle_user_menu(user);
            }
        } else if (choice == 3) {
            break;
        } else {
            printf("Opção inválida.\n");
        }
    }
    return 0;
}

void generate_sample_data() {
   strcpy(usuarios[0].nome, "Admin User");
    strcpy(usuarios[0].login, "admin");
    strcpy(usuarios[0].senha, "admin");
    usuarios[0].codigo = 1;
    usuarios[0].qtdPlaylists = 0;
    usuarios[0].qtdPlaylistsFav = 0;

    usuarioCount = 1;

    // Sample songs
    strcpy(musicas[0].titulo, "Lugar ao Sol");
    strcpy(musicas[0].artista, "Charlie Brown Jr.");
    musicas[0].codigo = 1;

    strcpy(musicas[1].titulo, "Routines In The Night");
    strcpy(musicas[1].artista, "Twenty One Pilots");
    musicas[1].codigo = 2;
    
    strcpy(musicas[2].titulo, "Billie Jean");
    strcpy(musicas[2].artista, "Michael Jackson");
    musicas[2].codigo = 3;

    strcpy(musicas[3].titulo, "Louca por Ti");
    strcpy(musicas[3].artista, "Calcinha Preta");
    musicas[3].codigo = 4;

    musicaCount = 4;
}

void display_main_menu() {
    printf("1. Administrador\n");
    printf("2. Usuário\n");
    printf("3. Sair\n");
    printf("Escolha uma opção: \n");
}

void handle_admin_menu() {
    int choice;
    do {
        printf("\nAdmin Menu:\n");
        printf("1. Listar usuários\n");
        printf("2. Consultar usuário\n");
        printf("3. Alterar senha de usuário\n");
        printf("4. Cadastrar novas músicas\n");
        printf("5. Listar todas as músicas\n");
        printf("6. Consultar músicas\n");
        printf("7. Alterar dados de músicas\n");
        printf("8. Excluir músicas\n");
        printf("9. Listar todas as playlists\n");
        printf("10. Consultar playlists\n");
        printf("11. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: list_users(); break;
            case 2: consult_user(); break;
            case 3: change_user_password(); break;
            case 4: register_song(); break;
            case 5: list_songs(); break;
            case 6: consult_song(); break;
            case 7: modify_song(); break;
            case 8: delete_song(); break;
            case 9: list_playlists(); break;
            case 10: consult_playlist(); break;
            case 11: printf("Saindo do menu do administrador.\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (choice != 11);
}

void handle_user_menu(struct Usuario *user) {
    int choice;
    do {
        printf("\nUser Menu:\n");
        printf("1. Listar dados\n");
        printf("2. Alterar nome\n");
        printf("3. Alterar login\n");
        printf("4. Alterar senha\n");
        printf("5. Listar usuários\n");
        printf("6. Consultar usuários\n");
        printf("7. Listar todas as músicas\n");
        printf("8. Consultar músicas\n");
        printf("9. Listar suas playlists\n");
        printf("10. Listar todas as playlists\n");
        printf("11. Consultar playlists\n");
        printf("12. Cadastrar playlist\n");
        printf("13. Inserir música na playlist\n");
        printf("14. Excluir música da playlist\n");
        printf("15. Excluir playlist\n");
        printf("16. Favoritar playlist\n");
        printf("17. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: listar_dados_usuario(user); break;
            case 2: alterar_nome_usuario(user); break;
            case 3: alterar_login_usuario(user); break;
            case 4: alterar_senha_usuario(user); break;
            case 5: list_users(); break;
            case 6: consult_user(); break;
            case 7: list_songs(); break;
            case 8: consult_song(); break;
            case 9: listar_suas_playlists(user); break;
            case 10: list_playlists(); break;
            case 11: consult_playlist(user); break;
            case 12: create_playlist(user); break;
            case 13: add_song_to_playlist(user); break;
            case 14: delete_song_from_playlist(user); break;
            case 15: delete_playlist(user); break;
            case 16: favorite_playlist(user); break;
            case 17: printf("Saindo do menu do usuário.\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (choice != 17);
}

int login_admin() {
   char senha[TAM_SENHA];
    printf("Digite a senha do administrador: ");
    scanf("%s", senha);
    if (strcmp(senha, "m@st3r2024") == 0) {
        return 1; 
    } else {
        printf("Senha incorreta, digite novamente!\n");
        return 0; 
    }
}

struct Usuario* login_user() {
    char login[TAM_LOGIN], senha[TAM_SENHA];

    printf("Login: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%s", senha);

    for (int i = 0; i < usuarioCount; i++) {
        if (strcmp(usuarios[i].login, login) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            return &usuarios[i];
        }
    }
    printf("Usuário ou senha incorretos.\n");
    return NULL;
}



struct Usuario* register_user() {
   if (usuarioCount >= TAM_MAX_PLYLST) {
        printf("Limite máximo de usuários alcançado.\n");
        return NULL;
    }

    struct Usuario newUser;
    newUser.codigo = usuarioCount + 1;

    printf("Nome: ");
    scanf("%s", newUser.nome);
    printf("Login: ");
    scanf("%s", newUser.login);

    char senha[TAM_SENHA], confirmacao[TAM_SENHA];
    do {
        printf("Senha: ");
        scanf("%s", senha);
        printf("Confirmação da senha: ");
        scanf("%s", confirmacao);

        if (strcmp(senha, confirmacao) != 0) {
            printf("As senhas não coincidem. Tente novamente.\n");
        }
    } while (strcmp(senha, confirmacao) != 0);

    strcpy(newUser.senha, senha);
    newUser.qtdPlaylists = 0;
    newUser.qtdPlaylistsFav = 0;

    usuarios[usuarioCount++] = newUser;

    printf("Usuário cadastrado com sucesso!\n");
    return &usuarios[usuarioCount - 1];
}

    void list_users() {
    printf("\nLista de Usuários:\n");
    for (int i = 0; i < usuarioCount; i++) {
        printf("Código: %d, Nome: %s, Login: %s\n", usuarios[i].codigo, usuarios[i].nome, usuarios[i].login);
    }
}


void consult_user() {
   char query[TAM_NOME];
    printf("Digite o código, login ou parte do nome do usuário: ");
    scanf("%s", query);

    for (int i = 0; i < usuarioCount; i++) {
        if (strstr(usuarios[i].nome, query) != NULL || strstr(usuarios[i].login, query) != NULL || usuarios[i].codigo == atoi(query)) {
            printf("Código: %d, Nome: %s, Login: %s\n", usuarios[i].codigo, usuarios[i].nome, usuarios[i].login);
        }
    }
}

void change_user_password() {
    int codigo;
    char senha[TAM_SENHA], confirmacao[TAM_SENHA];

    printf("Digite o código do usuário: ");
    scanf("%d", &codigo);

    for (int i = 0; i < usuarioCount; i++) {
        if (usuarios[i].codigo == codigo) {
            do {
                printf("Nova senha: ");
                scanf("%s", senha);
                printf("Confirmação da senha: ");
                scanf("%s", confirmacao);

                if (strcmp(senha, confirmacao) != 0) {
                    printf("As senhas não coincidem. Tente novamente.\n");
                }
            } while (strcmp(senha, confirmacao) != 0);

            strcpy(usuarios[i].senha, senha);
            printf("Senha alterada com sucesso!\n");
            return;
        }
    }
    printf("Usuário não encontrado.\n");
}

void register_song() {
   if (musicaCount >= TAM_MAX_PLYLST) {
        printf("Limite máximo de músicas alcançado.\n");
        return;
    }

    struct Musica newSong;
    newSong.codigo = musicaCount + 1;

    printf("Título: ");
    scanf("%s", newSong.titulo);
    printf("Artista: ");
    scanf("%s", newSong.artista);

    musicas[musicaCount++] = newSong;
    printf("Música cadastrada com sucesso!\n");
}

void list_songs() {
    printf("\nLista de Músicas:\n");
    for (int i = 0; i < musicaCount; i++) {
        printf("Código: %d, Título: %s, Artista: %s\n", musicas[i].codigo, musicas[i].titulo, musicas[i].artista);
    }
}

void consult_song() {
  char query[TAM_TITULO];
    printf("Digite o código, parte do título ou parte do nome do artista: ");
    scanf(" %[^\n]%*c", query); 

    int found = 0;
    printf("\nResultados da Consulta:\n");
    for (int i = 0; i < musicaCount; i++) {
        if (strstr(musicas[i].titulo, query) != NULL || strstr(musicas[i].artista, query) != NULL || musicas[i].codigo == atoi(query)) {
            printf("Código: %d, Título: %s, Artista: %s\n", musicas[i].codigo, musicas[i].titulo, musicas[i].artista);
            found = 1;
        }
    }
    if (!found) {
        printf("Nenhuma música encontrada.\n");
    }
}

void modify_song() {
    int codigo;
    printf("Digite o código da música: ");
    scanf("%d", &codigo);

    for (int i = 0; i < musicaCount; i++) {
        if (musicas[i].codigo == codigo) {
            printf("Novo título: ");
            scanf("%s", musicas[i].titulo);
            printf("Novo artista: ");
            scanf("%s", musicas[i].artista);
            printf("Música alterada com sucesso!\n");
            return;
        }
    }
    printf("Música não encontrada.\n");
}

void delete_song() {
     int codigo;
    printf("Digite o código da música: ");
    scanf("%d", &codigo);

    for (int i = 0; i < musicaCount; i++) {
        if (musicas[i].codigo == codigo) {
            for (int j = i; j < musicaCount - 1; j++) {
                musicas[j] = musicas[j + 1];
            }
            musicaCount--;
            printf("Música excluída com sucesso!\n");
            return;
        }
    }
    printf("Música não encontrada.\n");
}

void list_playlists() {
   for (int i = 0; i < usuarioCount; i++) {
        for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
            struct Playlist *playlist = &usuarios[i].playlists[j];
            printf("Código: %d, Título: %s, Criador: %s\n", playlist->codigo, playlist->titulo, usuarios[i].nome);
            for (int k = 0; k < playlist->qtdMusicas; k++) {
                struct Musica *musica = NULL;
                for (int l = 0; l < musicaCount; l++) {
                    if (musicas[l].codigo == playlist->musicas[k]) {
                        musica = &musicas[l];
                        break;
                    }
                }
                if (musica != NULL) {
                    printf("    Código: %d, Título: %s, Artista: %s\n", musica->codigo, musica->titulo, musica->artista);
                }
            }
        }
    }
}
    void listar_suas_playlists(struct Usuario *user) {
    printf("\nSuas Playlists:\n");
    for (int i = 0; i < user->qtdPlaylists; i++) {
        struct Playlist *playlist = &user->playlists[i];
        printf("Código: %d, Título: %s\n", playlist->codigo, playlist->titulo);
        for (int j = 0; j < playlist->qtdMusicas; j++) {
            struct Musica *musica = NULL;
            for (int k = 0; k < musicaCount; k++) {
                if (musicas[k].codigo == playlist->musicas[j]) {
                    musica = &musicas[k];
                    break;
                }
            }
            if (musica != NULL) {
                printf("    Código: %d, Título: %s, Artista: %s\n", musica->codigo, musica->titulo, musica->artista);
            }
        }
    }
}


void consult_playlist() {
    char query[TAM_TITULO];
    printf("Digite o código da playlist, parte do título ou código da música: ");
    scanf("%s", query);

    for (int i = 0; i < usuarioCount; i++) {
        for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
            struct Playlist *playlist = &usuarios[i].playlists[j];
            if (strstr(playlist->titulo, query) != NULL || playlist->codigo == atoi(query)) {
                printf("Código: %d, Título: %s, Criador: %s\n", playlist->codigo, playlist->titulo, usuarios[i].nome);
                for (int k = 0; k < playlist->qtdMusicas; k++) {
                    struct Musica *musica = NULL;
                    for (int l = 0; l < musicaCount; l++) {
                        if (musicas[l].codigo == playlist->musicas[k]) {
                            musica = &musicas[l];
                            break;
                        }
                    }
                    if (musica != NULL) {
                        printf("    Código: %d, Título: %s, Artista: %s\n", musica->codigo, musica->titulo, musica->artista);
                    }
                }
            }
        }
    }
}

void create_playlist(struct Usuario *user) {
   if (user->qtdPlaylists >= TAM_PLAYLIST) {
        printf("Limite máximo de playlists alcançado.\n");
        return;
    }

    struct Playlist newPlaylist;
    newPlaylist.codigo = ++playlistCount;
    newPlaylist.codUsuario = user->codigo;

    printf("Título da playlist: ");
    scanf("%s", newPlaylist.titulo);

    newPlaylist.qtdMusicas = 0;

    user->playlists[user->qtdPlaylists++] = newPlaylist;
    printf("Playlist criada com sucesso!\n");
}

void add_song_to_playlist(struct Usuario *user) {
    int playlistCodigo;
    printf("Digite o código da playlist: ");
    scanf("%d", &playlistCodigo);

    struct Playlist *playlist = NULL;
    for (int i = 0; i < user->qtdPlaylists; i++) {
        if (user->playlists[i].codigo == playlistCodigo) {
            playlist = &user->playlists[i];
            break;
        }
    }

    if (playlist == NULL) {
        printf("Playlist não encontrada.\n");
        return;
    }

    while (playlist->qtdMusicas < TAM_MUSICAS) {
        int musicaCodigo;
        printf("Digite o código da música (ou 0 para sair): ");
        scanf("%d", &musicaCodigo);

        if (musicaCodigo == 0) break;

        int found = 0;
        for (int i = 0; i < musicaCount; i++) {
            if (musicas[i].codigo == musicaCodigo) {
                playlist->musicas[playlist->qtdMusicas++] = musicaCodigo;
                found = 1;
                printf("Música adicionada à playlist.\n");
                break;
            }
        }

        if (!found) {
            printf("Música não encontrada.\n");
        }
    }
}

void delete_song_from_playlist(struct Usuario *user) {
     int playlistCodigo;
    printf("Digite o código da playlist: ");
    scanf("%d", &playlistCodigo);

    struct Playlist *playlist = NULL;
    for (int i = 0; i < user->qtdPlaylists; i++) {
        if (user->playlists[i].codigo == playlistCodigo) {
            playlist = &user->playlists[i];
            break;
        }
    }

    if (playlist == NULL) {
        printf("Playlist não encontrada.\n");
        return;
    }

    while (1) {
        printf("Músicas na playlist:\n");
        for (int i = 0; i < playlist->qtdMusicas; i++) {
            struct Musica *musica = NULL;
            for (int j = 0; j < musicaCount; j++) {
                if (musicas[j].codigo == playlist->musicas[i]) {
                    musica = &musicas[j];
                    break;
                }
            }
            if (musica != NULL) {
                printf("Código: %d, Título: %s, Artista: %s\n", musica->codigo, musica->titulo, musica->artista);
            }
        }

        int musicaCodigo;
        printf("Digite o código da música para excluir (ou 0 para sair): ");
        scanf("%d", &musicaCodigo);

        if (musicaCodigo == 0) break;

        int found = 0;
        for (int i = 0; i < playlist->qtdMusicas; i++) {
            if (playlist->musicas[i] == musicaCodigo) {
                for (int j = i; j < playlist->qtdMusicas - 1; j++) {
                    playlist->musicas[j] = playlist->musicas[j + 1];
                }
                playlist->qtdMusicas--;
                found = 1;
                printf("Música removida da playlist.\n");
                break;
            }
        }

        if (!found) {
            printf("Música não encontrada na playlist.\n");
        }
    }
}

void delete_playlist(struct Usuario *user) {
     int playlistCodigo;
    printf("Digite o código da playlist: ");
    scanf("%d", &playlistCodigo);

    for (int i = 0; i < user->qtdPlaylists; i++) {
        if (user->playlists[i].codigo == playlistCodigo) {
            printf("Playlist: %s\n", user->playlists[i].titulo);
            for (int j = 0; j < user->playlists[i].qtdMusicas; j++) {
                struct Musica *musica = NULL;
                for (int k = 0; k < musicaCount; k++) {
                    if (musicas[k].codigo == user->playlists[i].musicas[j]) {
                        musica = &musicas[k];
                        break;
                    }
                }
                if (musica != NULL) {
                    printf("    Código: %d, Título: %s, Artista: %s\n", musica->codigo, musica->titulo, musica->artista);
                }
            }

            char confirmacao;
            printf("Deseja realmente excluir esta playlist? (s/n): ");
            scanf(" %c", &confirmacao);

            if (confirmacao == 's') {
                for (int j = i; j < user->qtdPlaylists - 1; j++) {
                    user->playlists[j] = user->playlists[j + 1];
                }
                user->qtdPlaylists--;
                printf("Playlist excluída com sucesso!\n");
            }
            return;
        }
    }
    printf("Playlist não encontrada.\n");
}

void favorite_playlist(struct Usuario *user) {
    int playlistCodigo;
    printf("Digite o código da playlist: ");
    scanf("%d", &playlistCodigo);

    for (int i = 0; i < usuarioCount; i++) {
        if (usuarios[i].codigo != user->codigo) {
            for (int j = 0; j < usuarios[i].qtdPlaylists; j++) {
                if (usuarios[i].playlists[j].codigo == playlistCodigo) {
                    user->playlistsFav[user->qtdPlaylistsFav++] = playlistCodigo;
                    printf("Playlist favoritada com sucesso!\n");
                    return;
                }
            }
        }
    }
    printf("Playlist não encontrada ou pertence ao próprio usuário.\n");
}
void listar_dados_usuario(struct Usuario *user) {
    printf("Código: %d\n", user->codigo);
    printf("Nome: %s\n", user->nome);
    printf("Login: %s\n", user->login);
    printf("Quantidade de Playlists: %d\n", user->qtdPlaylists);
    printf("Quantidade de Playlists Favoritadas: %d\n", user->qtdPlaylistsFav);
}
void alterar_nome_usuario(struct Usuario *user) {
    char senha[TAM_SENHA];
    printf("Digite sua senha atual: ");
    scanf("%s", senha);

    if (strcmp(user->senha, senha) == 0) {
        printf("Digite o novo nome: ");
        scanf(" %[^\n]%*c", user->nome);
        printf("Nome alterado com sucesso!\n");
    } else {
        printf("Senha incorreta!\n");
    }
}
void alterar_login_usuario(struct Usuario *user) {
    char senha[TAM_SENHA];
    printf("Digite sua senha atual: ");
    scanf("%s", senha);

    if (strcmp(user->senha, senha) == 0) {
        printf("Digite o novo login: ");
        scanf("%s", user->login);
        printf("Login alterado com sucesso!\n");
    } else {
        printf("Senha incorreta!\n");
    }
}
void alterar_senha_usuario(struct Usuario *user) {
    char senhaAtual[TAM_SENHA];
    char novaSenha[TAM_SENHA];
    char confirmacao[TAM_SENHA];

    printf("Digite sua senha atual: ");
    scanf("%s", senhaAtual);

    if (strcmp(user->senha, senhaAtual) == 0) {
        do {
            printf("Digite a nova senha: ");
            scanf("%s", novaSenha);
            printf("Confirme a nova senha: ");
            scanf("%s", confirmacao);

            if (strcmp(novaSenha, confirmacao) != 0) {
                printf("As senhas não coincidem. Tente novamente.\n");
            }
        } while (strcmp(novaSenha, confirmacao) != 0);

        strcpy(user->senha, novaSenha);
        printf("Senha alterada com sucesso!\n");
    } else {
        printf("Senha atual incorreta!\n");
    }
}


