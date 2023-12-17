#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Structure for Song
typedef struct Song {
    char title[50];
    float minutes;
    struct Song *next;
} Song;


/*
// Structure for Album
typedef struct {
    char title[50];
    int releaseYear;
    int numSongs;
    Song *songs; // Ordered list of songs
} Album;

// Structure for Artist
typedef struct {
    char name[50];
    char style[30];
    int numAlbums;
    Album *albums; // Red-black tree of albums
} Artist;
*/

void listInitialize(Song **head);
void listInsert(Song **head, char *title, float minutes);
void listPrint(Song *head);
void listFree(Song *head);



//void treeInitialize(Node **root);
//void treeFree(Node *root);
//void insertArtist(Artist *library, int *numArtists, char name[], char style[]);
//void insertAlbum(Artist *artist, int *numAlbums, char title[], int releaseYear);
//void insertSong(Album *album, int *numSongs, char title[], int minutes);
//Artist* searchArtist(Artist *library, int numArtists, char name[]);
//Album* searchAlbum(Artist *artist, int numAlbums, char title[]);
//Song* searchSong(Album *album, int numSongs, char title[]);
//void removeSong(Album *album, int *numSongs, char title[]);
//void removeAlbum(Artist *artist, int *numAlbums, char title[]);
//void removeArtist(Artist *library, int *numArtists, char name[]);


int main() {
    // Initialize necessary variables and structures
    // Create the initial red-black tree
    // Implement the main loop for user interaction
    // Call functions based on user choices

    Song *head;
    listInitialize(&head);

    // Example: Insert songs into the list
    listInsert(&head, "Song3", 4.5);
    listInsert(&head, "Song1", 3.2);
    listInsert(&head, "Song2", 5.0);

    // Example: Print the list
    printf("Songs in the list: ");
    listPrint(head);
    listFree(head);

    return 0;
}


void listInitialize(Song **head){
    *head = NULL;
}

void listInsert(Song **head, char *title, float minutes) {
    Song *newSong = (Song *)malloc(sizeof(Song));
    strcpy(newSong->title, title);
    newSong->minutes = minutes;
    newSong->next = NULL;

    // If the list is empty or the new song comes before the current head
    if (*head == NULL || strcmp(title, (*head)->title) < 0) {
        newSong->next = *head;
        *head = newSong;
    } else {
        Song *current = *head;

        // Find the appropriate position for the new song
        while (current->next != NULL && strcmp(title, current->next->title) > 0) {
            current = current->next;
        }

        newSong->next = current->next;
        current->next = newSong;
    }
}

void listPrint(Song *head){
    if (head != NULL) 
    {
        printf("Title: %s, Duration: %.2f minutes\n", head->title, head->minutes);
        listPrint(head->next);
    }
}

void listFree(Song *head){
	if(head != NULL)
	{
		listFree(head->next);
		free(head);
	}
}

/*
void treeInitialize(artista **root)
{
    *root = NULL;
}

void treeFree(Node *root)
{
	if(root != NULL)
	{
		treeFree(root->left);
		treeFree(root->right);

		listFree(root->english);
		free(root);
	}
}
*/