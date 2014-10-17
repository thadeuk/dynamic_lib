#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libblock.h"

void init(Block *block)
{
    if (block->id == 1) {
        block->myInt = 30;
        block->myName = (char *) malloc(60 * sizeof(char));
        strcpy(block->myName, "Master Block");
    }
    else {
        block->myInt = 80;
        block->myName = (char *) malloc(60 * sizeof(char));
        strcpy(block->myName, "Child Block");
    }
}

void onEvent(Block *block, Event *event)
{
    if (event->eventType == MSG_CONNECT) {
        char str[80];
        sprintf(str, "connected | %s with ID %d", block->myName, block->myInt);
        sendAction(str);
    }
    else {
        char str[80];
        sprintf(str, "unrecognized event | %s with ID %d", block->myName, block->myInt);
        sendAction(str);
    }
}

void deleteData(Block *block)
{
    free(block->myName);
}
