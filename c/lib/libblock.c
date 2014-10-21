#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libblock.h"

void init(Block *block, int id)
{
        if (id == 1) {
            block->myName = (char *) malloc(sizeof(char)*60);
            strcpy(block->myName, "Master Block");
        }
        else {
            block->myName = (char *) malloc(sizeof(char)*60);
            strcpy(block->myName, "Child Block");
        }
        block->id = id;

        Event e;
        e.eventType = MSG_ASK_CONNECTION;
        sendAction(block, e);
}

void onEvent(Block *block, Event event)
{
    Event ev;
    switch (event.eventType)
    {
        case MSG_CONNECTION_ACCEPTED:
            printf("Connection accepted\n");

            block->myInt = (int *) malloc(sizeof(int));
            *block->myInt = (block->id == 1) ? 35 : 79;

            ev.eventType = MSG_SEND_INT;
            ev.msgData = block->myInt;

            sendAction(block, ev);
            break;
        case MSG_CLOSE_CONNECTION:
            printf("Connection closed\n");
            free(block->myInt);
            break;
    }
}

void deleteData(Block *block)
{
    free(block->myName);
}
