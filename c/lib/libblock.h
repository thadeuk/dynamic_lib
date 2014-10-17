#include <stdio.h>
#define MSG_CONNECT     1001
#define MSG_NETWORK     1002
#define MSG_POSITION    2001

typedef struct {
    int id;
    int myInt;
    char *myName;
} Block;

typedef struct {
    int eventType;
    void *content;
} Event;

//void init(Block *);
//void onEvent(Block *, Event *);
//void deleteData(Block *);
void sendAction(char *data) {
    printf("Sending data -> %s\n", data);
} 
