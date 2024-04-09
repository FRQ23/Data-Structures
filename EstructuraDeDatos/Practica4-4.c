//
// Created by Fertronic on 4/9/24.
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
void dequeue(Queue *queue, int position);
void enqueue(Queue *queue, Song *song, int position);
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
    if (playbackQueue->current == null) {
        printf("None <<-- None -->> None\n");
        return;
    }

    if (playbackQueue->current->previous != null) {
        printf("%s - %s <<-- ", playbackQueue->current->previous->song->name,
               playbackQueue->current->previous->song->author);

    } else {

        printf("None <<-- ");
    }

    printf("%s - %s -->> ", playbackQueue->current->song->name,
           playbackQueue->current->song->author);

    if (playbackQueue->current->next != null) {
        printf("%s - %s\n", playbackQueue->current->next->song->name,
               playbackQueue->current->next->song->author);

    } else {

        printf("None\n");
    }

    return;
}


//push auxiliar y pop sobre la original

//respetar fifo
//
void dequeue(Queue *queue, int position) {
    if (queue->numElements == 0) {
        printf("ERROR: underflow\n");
        return;
    }

    if (position < 0 || position >= queue->numElements) {
        printf("\nERROR: invalid position\n");
        return;
    }

    Element *deletedElement = null;
    Song *songOut = null;

    if (position == 0) {
        deletedElement = queue->start;
        songOut = deletedElement->song;

        if (queue->numElements == 1) {
            queue->start = null;
            queue->end = null;
        } else {
            queue->start = queue->start->next;
            queue->start->previous = queue->end;
            queue->end->next = queue->start;
        }
    } else if (position == queue->numElements - 1) {
        deletedElement = queue->end;
        songOut = deletedElement->song;

        queue->end = queue->end->previous;
        queue->end->next = queue->start;
        queue->start->previous = queue->end;
    } else {
        Element *current = queue->start;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }

        deletedElement = current;
        songOut = deletedElement->song;

        current->previous->next = current->next;
        current->next->previous = current->previous;
    }

    queue->numElements--;

    if (queue->numElements == 0) {
        queue->current = null;
    } else if (queue->current == deletedElement && queue->numElements != 0) {
        if (queue->current->next != null) {
            queue->current = queue->current->next;

        } else {
            queue->current = queue->start;
        }
    }

    free(deletedElement);
    printf("\nSong removed: %s\n", songOut->name);

    return;
}

//
void enqueue(Queue *queue, Song *song, int position) {
    if (queue->maxSize > 0 && queue->numElements == queue->maxSize) {
        printf("\nERROR: overflow\n");
        return;
    }

    if (position < 0 || position > queue->numElements) {
        printf("\nERROR: invalid position\n");
        return;
    }

    Element *newElement = allocateElement(song);

    if (queue->numElements == 0) {
        queue->start = newElement;
        queue->end = newElement;
        newElement->next = newElement;
        newElement->previous = newElement;
    } else {
        if (position == 0) {
            newElement->next = queue->start;
            newElement->previous = queue->end;
            queue->start->previous = newElement;
            queue->end->next = newElement;
            queue->start = newElement;
        } else if (position == queue->numElements) {
            newElement->next = queue->start;
            newElement->previous = queue->end;
            queue->end->next = newElement;
            queue->start->previous = newElement;
            queue->end = newElement;
        } else {
            Element *current = queue->start;
            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }

            newElement->next = current->next;
            newElement->previous = current;
            current->next->previous = newElement;
            current->next = newElement;
        }
    }

    queue->numElements++;

    if (queue->numElements == 1) {
        queue->current = queue->start;
    }

    return;
}

void initializeQueue(Queue *queue) {
    queue->start = null;
    queue->end = null;
    queue->current = null;
    queue->maxSize = 0;
    queue->numElements = 0;
    queue->isLooped = true;
    queue->isFirstIter = true;

    return;
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

    return;
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
    // If the queue is empty, exit to avoid segmentation fault
    if (queue->numElements == 0) {
        return;
    }

    if (activate) {
        queue->start->previous = queue->end;
        queue->end->next = queue->start;
        queue->isLooped = true;
    } else {
        queue->start->previous = null;
        queue->end->next = null;
        queue->isLooped = false;
    }
}

bool isLooping(Queue *queue) {
    bool output =
            queue->start->previous == queue->end && queue->end->next == queue->start;

    return (output && queue->numElements > 0);
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

                if (playbackQueue.current != null) {
                    playbackQueue.current = playbackQueue.current->previous;
                }

                break;
            case 2:

                //en dado que sea nulo la ultima, no deberia de dejar hacer la siguiente
                printf("\n[2] NEXT\n");

                if (playbackQueue.current != null) {
                    playbackQueue.current = playbackQueue.current->next;
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