#include <stdio.h>
#define MSG_ASK_CONNECTION         1001
#define MSG_CONNECTION_ACCEPTED    1002
#define MSG_SEND_INT 1003
#define MSG_CLOSE_CONNECTION 1004

typedef struct {
    int eventType;
    void *msgData;
} Event;

typedef struct {
    int id;
    int *myInt;
    char *myName;
} Block;

void (*init_)(Block *, int id);
void (*onEvent_)(Block *, Event);
void (*deleteData_)(Block *);

void sendAction(Block *block, Event event) {
    Event ev;
    switch (event.eventType) {

        case MSG_ASK_CONNECTION:
            printf("Block %s -> Asking connection\n", block->myName) ;
            ev.eventType = MSG_CONNECTION_ACCEPTED;
            onEvent_(block, ev);
            break;
        case MSG_SEND_INT:
            printf("Block %s -> Send int -> %d\n", block->myName, *(int *)(event.msgData)) ;
            ev.eventType = MSG_CLOSE_CONNECTION;
            onEvent_(block, ev);
            break;
        default:
            printf("Undefined event type");

    } 
}
