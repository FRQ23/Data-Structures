//
// Created by Fernando Rosales on 4/10/24.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define null NULL
#define ACTIVATE 1
#define DEACTIVATE 0

typedef struct {
    char *name;
    char *author;
    int releaseYear;

} Song;

typedef struct Element {
    Song *song;
    struct Element *next;
    struct Element *previous;

} Element;

typedef struct {
    Element *start;
    Element *end;
    Element *current;

    int maxSize;
    int numElements;
    bool isLooped;
    bool isFirstIter;

} Queue;

void displayPlayback(Queue *playbackQueue);
void enqueue(Queue *queue, Song *song, int index);
void dequeue(Queue *queue, int index);
void initializeQueue(Queue *queue);
Element *allocateElement(Song *song);
void showPlaybackQueue(Queue *queue);
int showPlaylist(void);
void toggleLoop(Queue *queue, int activate);
bool isLooping(Queue *queue);

static Song originalPlaylist[15] = {
        {"Falling Away From Me", "Korn", 1999},
        {"Last Resort", "Papa Roach", 2000},
        {"Numb", "Linkin Park", 2003},
        {"Bodies", "Drowning Pool", 2001},
        {"Blind", "Korn", 1994},
        {"Chop Suey!", "System of a Down", 2001},
        {"Wait and Bleed", "Slipknot", 1999},
        {"Here to Stay", "Korn", 2002},
        {"Freak on a Leash", "Korn", 1998},
        {"My Own Summer (Shove It)", "Deftones", 1997},
        {"Bring Me to Life", "Evanescence", 2003},
        {"Crawling", "Linkin Park", 2001},
        {"Becoming the Bull", "Atreyu", 2007},
        {"Indestructible", "Disturbed", 2008},
        {"I Hate Everything About You", "Three Days Grace", 2003}};

void displayPlayback(Queue *playbackQueue) {
    if (playbackQueue->numElements == 0) {
        printf("La cola está vacía.\n");
        return;
    }

    if (playbackQueue->current == NULL) {
        printf("El elemento actual es NULL.\n");
        return;
    }

    if (playbackQueue->current->previous != NULL) {
        printf("%s - %s <<-- ", playbackQueue->current->previous->song->name,
               playbackQueue->current->previous->song->author);
    } else {
        printf("None <<-- ");
    }

    printf("%s - %s -->> ", playbackQueue->current->song->name,
           playbackQueue->current->song->author);

    if (playbackQueue->current->next != NULL) {
        printf("%s - %s\n", playbackQueue->current->next->song->name,
               playbackQueue->current->next->song->author);
    } else {
        printf("None\n");
    }
}
//push auxiliar y pop sobre la original

//respetar fifo
//

// Function to remove an element from the queue (dequeue)
void dequeue(Queue *queue, int index) {
    if (queue->numElements == 0) {
        printf("ERROR: underflow\n");
        return;
    }

    Element *current = queue->start;
    Element *previous = NULL;

    // Find the element at the index
    for (int i = 0; i < index && current != NULL; i++) {
        previous = current;
        current = current->next;
    }

    // If the index is beyond the end of the queue, print an error message
    if (current == NULL) {
        printf("ERROR: index out of bounds\n");
        return;
    }

    // If the element to be deleted is at the start of the queue
    if (current == queue->start) {
        queue->start = current->next;
        if (queue->start != NULL) {
            queue->start->previous = NULL;
        }
    } else {
        previous->next = current->next;
        if (current->next != NULL) {
            current->next->previous = previous;
        }
    }

    // If the element to be deleted is at the end of the queue
    if (current == queue->end) {
        queue->end = previous;
        if (queue->end != NULL) {
            queue->end->next = NULL;
        }
    }

    // If the deleted element was the current element, update the current pointer
    if (queue->current == current) {
        queue->current = previous;  // Set current to the previous song
    }

    // Decrease the element counter in the queue
    queue->numElements--;

    // Free the memory of the deleted element
    free(current);

    printf("\nSong removed from position %d\n", index);
}


void initializeQueue(Queue *queue) {
    queue->start = null;
    queue->end = null;
    queue->current = null;
    queue->maxSize = 0;
    queue->numElements = 0;
    queue->isLooped = true;
    queue->isFirstIter = true;

}

Element *allocateElement(Song *song) {
    Element *newElement = malloc(sizeof(Element));

    newElement->song = song;
    newElement->next = null;
    newElement->previous = null;

    return newElement;
}

void showPlaybackQueue(Queue *queue) {
    if (queue->numElements == 0) {
        printf("La cola está vacía.\n");
        return;
    }

    Element *current = queue->start;
    int n = 0;
    printf("\n");

    while (n < queue->numElements) {
        printf("%d) %s - %s\n", n, current->song->name, current->song->author);
        n++;
        current = current->next;
    }
}

int showPlaylist(void) {
    int selection;
    printf("\nAvailable songs: \n");
    for (int i = 0; i < 15; i++) {
        printf("%d) %s - %s\n", i, originalPlaylist[i].name,
               originalPlaylist[i].author);
    }

    printf("Choose a song\n> ");
    scanf("\n%d", &selection);

    return selection;
}

void toggleLoop(Queue *queue, int activate) {
    if (queue->numElements == 0) {
        return;
    }

    if (activate) {
        if (queue->start != NULL && queue->end != NULL) {
            queue->start->previous = queue->end;
            queue->end->next = queue->start;
        }
        queue->isLooped = true;
    } else {
        if (queue->start != NULL) {
            queue->start->previous = NULL;
        }
        if (queue->end != NULL) {
            queue->end->next = NULL;
        }
        queue->isLooped = false;
    }
}

bool isLooping(Queue *queue) {
    bool output = false;
    if (queue->start != NULL && queue->end != NULL) {
        output = queue->start->previous == queue->end && queue->end->next == queue->start;
    }
    return (output && queue->numElements > 0);
}

void enqueue(Queue *queue, Song *song, int index) {
    if (queue->maxSize > 0 && queue->numElements == queue->maxSize) {
        printf("\nERROR: overflow\n");
        return;
    }

    Element *newElement = allocateElement(song);

    if (queue->numElements == 0) {
        // If the queue is empty, add the element at the start
        newElement->next = queue->start;
        if (queue->start != NULL) {
            queue->start->previous = newElement;
        }
        queue->start = newElement;
        queue->end = newElement;
        queue->current = newElement;  // Set current to the inserted song
    } else if (index == 0) {
        // If index is 0, add the element after the current song
        newElement->next = queue->current->next;
        newElement->previous = queue->current;
        if (queue->current->next != NULL) {
            queue->current->next->previous = newElement;
        }
        queue->current->next = newElement;
        if (queue->current == queue->end) {
            queue->end = newElement;
        }
    } else {
        // Find the element currently at the index
        Element *current = queue->start;
        for (int i = 0; i < index - 1 && current != NULL; i++) {
            current = current->next;
        }

        // If the index is beyond the end of the queue, add the element at the end
        if (current == NULL || current == queue->end) {
            newElement->next = NULL;
            newElement->previous = queue->end;
            queue->end->next = newElement;
            queue->end = newElement;
        } else {
            // Otherwise, insert the element at the index
            newElement->next = current->next;
            newElement->previous = current;
            current->next = newElement;
        }
    }

    queue->numElements++;
}

int main(void) {
    int i, option, runProgram, index;

    runProgram = true;

    Queue playbackQueue;
    initializeQueue(&playbackQueue);

    while (runProgram) {
        //system("clear");
        printf("\n\r");
        displayPlayback(&playbackQueue);
        printf("\n\r");
        printf("\n\r [0] LOOP");
        printf("\n\r [1] PREVIOUS");
        printf("\n\r [2] NEXT");
        printf("\n\r [3] ADD SONG");
        printf("\n\r [4] SHOW PLAYBACK QUEUE");
        printf("\n\r [5] REMOVE SONG");
        printf("\n\r [6] RESTART PLAYBACK");
        printf("\n\r [7] END PROGRAM");

        printf("\n\r Choose an option: ");
        scanf("%d", &option);
        switch (option) {
            case 0:
                printf("[0] LOOP\n");

                if (playbackQueue.isLooped) {
                    toggleLoop(&playbackQueue, DEACTIVATE);

                } else {
                    toggleLoop(&playbackQueue, ACTIVATE);
                }

                break;
            case 1:
                printf("\n[1] PREVIOUS\n");

                // Check if there is a previous song
                if (playbackQueue.current != null && playbackQueue.current->previous != null) {
                    playbackQueue.current = playbackQueue.current->previous;
                } else {
                    printf("You are already at the first song, can't go to the previous.\n");
                }
                break;
            case 2:

                //en caso de que no haya canciones
                printf("\n[2] NEXT\n");

                if (playbackQueue.current != null && playbackQueue.current->next != null) {
                    playbackQueue.current = playbackQueue.current->next;
                } else {
                    printf("You are already at the last song, can't go to the next.\n");
                }

                break;
            case 3:
                printf("\n[3] Add song\n");

                i = showPlaylist();

                if (i < 0 || i > 15) {
                    break;
                }

                printf("\nShowing playback queue\n");
                showPlaybackQueue(&playbackQueue);
                printf("\nChoose a position to insert the song\n> ");
                scanf("\n%d", &index);

                enqueue(&playbackQueue, &originalPlaylist[i], index);

                if (playbackQueue.isFirstIter) {
                    toggleLoop(&playbackQueue, DEACTIVATE);
                    playbackQueue.isFirstIter = false;
                    break;
                }

                if (isLooping(&playbackQueue) && !playbackQueue.isLooped) {
                    toggleLoop(&playbackQueue, DEACTIVATE);
                }

                break;
            case 4:
                printf("\n[4] Showing playback queue\n");
                showPlaybackQueue(&playbackQueue);

                break;
            case 5:
                printf("\n[5] Remove song from the queue.\n");

                printf("\nShowing playback queue\n");
                showPlaybackQueue(&playbackQueue);
                printf("\nChoose a position to remove the song\n> ");
                scanf("\n%d", &index);

                dequeue(&playbackQueue, index);

                if (playbackQueue.numElements == 0) {
                    break;
                }

                if (isLooping(&playbackQueue) && !playbackQueue.isLooped) {
                    toggleLoop(&playbackQueue, DEACTIVATE);
                }



                break;
            case 6:
                printf("\n[6] RESTART PLAYBACK\n");

                if (playbackQueue.start != null) {
                    playbackQueue.current = playbackQueue.start;
                }

                printf("\nPlayback restarted.\n");



                break;
            case 7:
                printf("Utini!\n");
                runProgram = false;
                break;
            default:
                break;
        }
    }

    while (playbackQueue.numElements > 0) {
        dequeue(&playbackQueue, 0);
    }

    printf("\n\n\r");
    return 0;
}