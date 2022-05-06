#include "linkedList.h"

void print_playlist_menu(void)
{
    printf("\n\n---- Playlist Menu ---- \n");
    printf(" a : print all playlist \n");
    printf(" c : print current playlist\n");
    printf(" n : new playlist \n");
    printf(" d : delete playlist \n");
    printf(" > : next playlist \n");
    printf(" < : previous playlist \n");
    printf(" s : song menu \n");
    printf(" q : quit \n");
    return;
}

void print_song_menu(void)
{
    printf("\n\n---- Song Menu ---- \n");
    printf(" a : print all songs \n");
    printf(" c : print current song\n");
    printf(" n : add new song in playlist \n");
    printf(" d : delete current song \n");
    printf(" > : next song \n");
    printf(" < : previous song \n");
    printf(" b : quit \n");
    return;
}

int main(void)
{
    DPlaylistNode *head = NULL;
    Element buf;
    DPlaylistNode *currentPlaylist = NULL;
    DSongNode *currentSong = NULL;
    char menu, sub_menu;

    do
    {
        // printf("메뉴 선택");
        print_playlist_menu();
        printf("Select Menu : ");
        scanf(" %c", &menu);
        printf("--------------------------\n");
        printf("Selected playlist menu : %c \n", menu);
        switch (menu)
        {
        case 'a':
            print_aPlaylist(head, currentPlaylist);
            break;
        case 'c':
            printf("Current playlist : %s\n", currentPlaylist->playlistName.name);
            break;
        case 'n':
            printf("Playlist name : ");
            scanf("%s", &buf.name);
            insert_nPlaylist(&head, buf, &currentPlaylist);
            print_aPlaylist(head, currentPlaylist);
            break;
        case 'd':
            delete_dPlaylist(&head, &currentPlaylist);
            print_aPlaylist(head, currentPlaylist);
            break;
        case '<':
            change_cPlaylist(&currentPlaylist, 2);
            print_aPlaylist(head, currentPlaylist);
            break;
        case '>':
            change_cPlaylist(&currentPlaylist, 1);
            print_aPlaylist(head, currentPlaylist);
            break;
        case 's':
            if (currentPlaylist)
            {
                currentSong = currentPlaylist->songlist;
                do
                {
                    print_song_menu();
                    printf("Select Menu : ");
                    scanf(" %c", &sub_menu);
                    printf("Selected song menu : %c \n", sub_menu);
                    switch (sub_menu)
                    {
                    case 'a':
                        print_aSong(currentPlaylist, currentSong);
                        break;
                    case 'c':
                        printf("current song : %s\n", currentSong->songName.name);
                        break;
                    case 'n':
                        printf("Song name : ");
                        scanf("%s", &buf.name);
                        insert_nSongList(currentPlaylist, buf, &currentSong);
                        print_aSong(currentPlaylist, currentSong);
                        break;
                    case 'd':
                        delete_dSong(currentPlaylist, &currentSong);
                        print_aSong(currentPlaylist, currentSong);
                        break;
                    case '<':
                        change_cSong(&currentSong, 2);
                        print_aSong(currentPlaylist, currentSong);
                        break;
                    case '>':
                        change_cSong(&currentSong, 1);
                        print_aSong(currentPlaylist, currentSong);
                        break;
                    }
                } while (sub_menu != 'b');
            }
            break;
        }
    } while (menu != 'q');
    return 0;
}