#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>
#include "libblock.h"

class MyBlock: public AbstractBlock
{
    int *myInt;
    char *myName;

public:
    MyBlock(int id) : AbstractBlock(id) {}

    void init() {
        if (_id == 1) {
            myName = new char[60];
            strcpy(myName, "Master Block");
        }
        else {
            myName = new char[60];
            strcpy(myName, "Child Block");
        }

        Event e;
        e.eventType = MSG_ASK_CONNECTION;
        sendAction(*this, e);
    }

    void onEvent(Event &event) {
        Event ev;
        switch (event.eventType)
        {
            case MSG_CONNECTION_ACCEPTED:
                std::cout << "Connection accepted" << std::endl;

                myInt = new int;
                *myInt = (_id == 1) ? 35 : 79;

                ev.eventType = MSG_SEND_INT;
                ev.msgData = myInt;

                sendAction(*this, ev);
                break;
            case MSG_CLOSE_CONNECTION:
                std::cout << "Connection closed" << std::endl;
                delete myInt;
                break;
        }
    }


    ~MyBlock() {
        delete myName;
    }

    const std::string get_name() {
        return myName;
    }
};

extern "C" {
    AbstractBlock *getInstance(int id)
    {
        return new MyBlock(id);
    }
}
