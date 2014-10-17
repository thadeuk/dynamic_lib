#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "lib/libblock.h"

using namespace std;

void (*block_init)(Block *);
void (*block_onEvent)(Block *, Event *);
void (*block_deleteData)(Block *);

void load_functions(void *lib_handle){
    char *error;

    block_init = (void (*)(Block *))dlsym(lib_handle, "init");
    block_onEvent = (void (*)(Block *, Event *))dlsym(lib_handle, "onEvent");
    block_deleteData = (void (*)(Block *))dlsym(lib_handle, "deleteData");

    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

}

void *load_library(const char *library_path) {
    void *lib_handle;

    lib_handle = dlopen(library_path, RTLD_LAZY);

    if (!lib_handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }
    printf("Load %s\n", library_path);

    return lib_handle;
}

void close_library(void *lib_handle)
{
    dlclose(lib_handle);
}

int
main(int argc, char **argv)
{
    string LIB_PATH= "./lib/libblock.so.1.0";
    void *lib_handle = load_library(LIB_PATH.c_str());
    load_functions(lib_handle);

    Block block1;
    Block block2;

    block1.id = 1;
    block2.id = 3;

    block_init(&block1);
    block_init(&block2);

    cout << "First block name = " << block1.myName << endl;
    cout << "Second block name = " <<  block2.myName << endl;

    Event ev;
    ev.eventType = MSG_CONNECT;
    block_onEvent(&block1, &ev);
    block_onEvent(&block2, &ev);

    ev.eventType = MSG_POSITION;
    block_onEvent(&block1, &ev);
    block_onEvent(&block2, &ev);

    block_deleteData(&block1);
    block_deleteData(&block2);
    cout << "Memory free" << endl;
    
    close_library(lib_handle);
    cout << "Unload library" << endl;

    return 0;
}
