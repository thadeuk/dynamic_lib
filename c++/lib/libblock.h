#include <stdio.h>
#define MSG_CONNECT     1001
#define MSG_NETWORK     1002
#define MSG_POSITION    2001

typedef struct {
    int id;
} Block;

typedef struct {
    int eventType;
} Event;

void sendAction(const char *data) {
    printf("Sending data -> %s\n", data);
} 

class AbstractBlock 
{
protected:
    Block *block;

public:
    AbstractBlock(Block *b): block(b) {};

    virtual void init() = 0;
    virtual void onEvent(Event *) = 0;
};
