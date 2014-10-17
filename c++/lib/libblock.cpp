#include <cstdlib>
#include <iostream>
#include <cstring>
#include <sstream>
#include "libblock.h"

class MyBlock: public AbstractBlock
{
    int myInt;
    char *myName;

public:
    MyBlock(Block *block) : AbstractBlock(block) {}

    void init() {
        if (block->id == 1) {
            myInt = 30;
            myName = new char[60];
            strcpy(myName, "Master Block");
        }
        else {
            myInt = 80;
            myName = new char[60];
            strcpy(myName, "Child Block");
        }
    }

    void onEvent(Event *event) {
        if (event->eventType == MSG_CONNECT) {
            std::stringstream sstream;
            sstream << "connected " << myName << " " << myInt;
            sendAction(sstream.str().c_str());
        }
        else {
            std::stringstream sstream;
            sstream << "unrecognized event " << myName << " " << myInt;
            sendAction(sstream.str().c_str());
        }
    }

    ~MyBlock() {
        delete myName;
    }
};

extern "C" {
    MyBlock *getInstance(Block *block)
    {
        return new MyBlock(block);
    }
}
