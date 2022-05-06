#include "linkedList.h"

void print_aPlaylist(DPlaylistNode *playlist, DPlaylistNode *curList)
{
    printf("Playlist : ");
    if (!playlist)
        printf("(NULL)\n");
    else
    {
        DPlaylistNode *pos = playlist;
        do
        {
            if (pos == curList)
                printf("<-[*%s*]-> ", pos->playlistName.name);
            else
                printf("<-[%s]-> ", pos->playlistName.name);
            pos = pos->right;
        } while (pos != playlist);
    }
}

void insert_nPlaylist(DPlaylistNode **playlist, Element name, DPlaylistNode **curList)
{
    DPlaylistNode *newList = (DPlaylistNode *)malloc(sizeof(DPlaylistNode));
    strcpy(newList->playlistName.name, name.name);
    newList->left = NULL;
    newList->right = NULL;
    newList->songlist = NULL;

    if (!*playlist) // If playlist null
    {
        *playlist = newList;
        newList->left = newList;
        newList->right = newList;

        *curList = newList;
    }
    else // New playlist insert
    {
        // Last node link
        DPlaylistNode *pos = (*playlist)->left;
        pos->right = newList;
        newList->left = pos;

        // First node link
        pos = (*playlist);
        newList->right = pos;
        pos->left = newList;

        *curList = newList;
    }
}

void delete_dPlaylist(DPlaylistNode **playlist, DPlaylistNode **curList)
{
    if (*playlist)
        if (*playlist == (*playlist)->left) // Only one playlist exists
        {
            (*playlist) = NULL;

            // songlist 전부 삭제하는 함수 추가
            while ((*curList)->songlist)
                delete_dSong(*curList, &(*curList)->songlist);

            free(*curList);
            *curList = NULL;
        }
        else
        {
            DPlaylistNode *pos = (*curList)->left;
            pos->right = (*curList)->right;

            pos = (*curList)->right;
            pos->left = (*curList)->left;

            while ((*curList)->songlist)
                delete_dSong(*curList, &(*curList)->songlist);

            DPlaylistNode *delList = *curList;
            *curList = pos;
            free(delList);
        }
}

void change_cPlaylist(DPlaylistNode **curList, int select) // select - 1 : right  2 : left
{
    if (*curList)
        if (select == 1)
            *curList = (*curList)->right;
        else if (select == 2)
            *curList = (*curList)->left;
}

void print_aSong(DPlaylistNode *curList, DSongNode *curSong)
{
    printf("Song list : ");
    if (!curList->songlist)
        printf("(NULL)\n");
    else
    {
        DSongNode *pos = curList->songlist;
        do
        {
            if (pos == curSong)
                printf("<-[*%s*]-> ", pos->songName.name);
            else
                printf("<-[%s]-> ", pos->songName.name);
            pos = pos->right;
        } while (pos != curList->songlist);
    }
}

void insert_nSongList(DPlaylistNode *curList, Element name, DSongNode **curSong)
{
    DSongNode *newSong = (DSongNode *)malloc(sizeof(DSongNode));
    newSong->left = NULL;
    newSong->right = NULL;
    strcpy(newSong->songName.name, name.name);

    if (!curList->songlist)
    {
        curList->songlist = newSong;
        newSong->right = newSong;
        newSong->left = newSong;

        *curSong = newSong;
    }
    else
    {
        DSongNode *pos = curList->songlist->left;
        pos->right = newSong;
        newSong->left = pos;

        pos = curList->songlist;
        newSong->right = pos;
        pos->left = newSong;

        *curSong = newSong;
    }
}

void delete_dSong(DPlaylistNode *curList, DSongNode **curSong)
{
    if (*curSong)
        if (curList->songlist->left == curList->songlist)
        {
            curList->songlist = NULL;
            free(*curSong);
            *curSong = NULL;
        }
        else
        {
            DSongNode *pos = (*curSong)->left;
            pos->right = (*curSong)->right;

            pos = (*curSong)->right;
            pos->left = (*curSong)->left;

            DSongNode *delSong = *curSong;
            *curSong = pos;

            if (curList->songlist == delSong)
                curList->songlist = delSong->right;

            free(delSong);
        }
}

void change_cSong(DSongNode **curSong, int select)
{
    if (*curSong)
        if (select == 1)
            *curSong = (*curSong)->right;
        else if (select == 2)
            *curSong = (*curSong)->left;
}
