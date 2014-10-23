#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "libblock.h"

typedef struct {
    int *myInt;
    char *myName;
} MyBlock;

void init(Block *block, int id)
{
    block->id = id;
    block->myBlock = (MyBlock *) malloc(sizeof(MyBlock));
    MyBlock *myBlock = (MyBlock *)block->myBlock;

    if (id == 1) {
        myBlock->myName = (char *) malloc(sizeof(char)*60);
        strcpy(myBlock->myName, "Master Block");
    }
    else {
        myBlock->myName = (char *) malloc(sizeof(char)*60);
        strcpy(myBlock->myName, "Child Block");
    }

    Event e;
    e.eventType = MSG_ASK_CONNECTION;
    sendAction(block, e);
}

void onEvent(Block *block, Event event)
{
    MyBlock *myBlock = (MyBlock *)block->myBlock;
    Event ev;
    switch (event.eventType)
    {
        case MSG_CONNECTION_ACCEPTED:
            printf("Connection accepted\n");

            myBlock->myInt = (int *) malloc(sizeof(int));
            *myBlock->myInt = (block->id == 1) ? 35 : 79;

            ev.eventType = MSG_SEND_INT;
            ev.msgData = myBlock->myInt;

            sendAction(block, ev);
            break;
        case MSG_CLOSE_CONNECTION:
            printf("Connection closed %s\n", myBlock->myName);
            free(myBlock->myInt);
            break;
    }
}

void deleteData(Block *block)
{
    free(((MyBlock *)block->myBlock)->myName);
    free(block->myBlock);
}
