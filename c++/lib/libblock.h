#include <iostream>
#define MSG_ASK_CONNECTION         1001
#define MSG_CONNECTION_ACCEPTED    1002
#define MSG_SEND_INT 1003
#define MSG_CLOSE_CONNECTION 1004

typedef struct {
    int eventType;
    void *msgData;
} Event;

class AbstractBlock 
{
protected:
    int _id;

public:
    AbstractBlock(int id): _id(id) {};

    virtual void init() = 0;
    virtual void onEvent(Event &) = 0;
    virtual const std::string get_name() = 0;
};

void sendAction(AbstractBlock &block, Event &event) {
    Event ev;
    switch (event.eventType) {

        case MSG_ASK_CONNECTION:
            std::cout << "Block " << block.get_name() << " -> Asking connection\n";
            ev.eventType = MSG_CONNECTION_ACCEPTED;
            block.onEvent(ev);
            break;
        case MSG_SEND_INT:
            std::cout << "Block " << block.get_name() << " -> Send int -> " << *(int*)(event.msgData) << std::endl;
            ev.eventType = MSG_CLOSE_CONNECTION;
            block.onEvent(ev);
            break;
        default:
            std::cout << "Undefined event type";

    } 
}

