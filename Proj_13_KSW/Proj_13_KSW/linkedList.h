#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SIZE 50

typedef struct _Element
{
    char name[MAX_NAME_SIZE];
} Element;

typedef struct _DSongNode
{
    Element songName;
    struct _DSongNode *left;
    struct _DSongNode *right;
} DSongNode;

typedef struct _DPlaylistNode
{
    Element playlistName;
    DSongNode *songlist;
    struct _DPlaylistNode *left;
    struct _DPlaylistNode *right;
} DPlaylistNode;

void print_aPlaylist(DPlaylistNode *, DPlaylistNode *);
void insert_nPlaylist(DPlaylistNode **, Element, DPlaylistNode **);
void delete_dPlaylist(DPlaylistNode **, DPlaylistNode **);
void change_cPlaylist(DPlaylistNode **, int);

void print_aSong(DPlaylistNode *, DSongNode *);
void insert_nSongList(DPlaylistNode *, Element, DSongNode **);
void delete_dSong(DPlaylistNode *, DSongNode **);
void change_cSong(DSongNode **, int);

void delete_all_song(DPlaylistNode **);