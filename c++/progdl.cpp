#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "lib/libblock.h"

using namespace std;

AbstractBlock *(*getBlockInstance)(Block *);

void load_functions(void *lib_handle){
    char *error;

    getBlockInstance = (AbstractBlock *(*)(Block *))dlsym(lib_handle, "getInstance");

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
    
    AbstractBlock *myBlock1 = getBlockInstance(&block1);
    AbstractBlock *myBlock2 = getBlockInstance(&block2);

    myBlock1->init();
    myBlock2->init();

    Event ev;
    ev.eventType = MSG_CONNECT;
    myBlock1->onEvent(&ev);
    myBlock2->onEvent(&ev);

    ev.eventType = MSG_POSITION;
    myBlock1->onEvent(&ev);
    myBlock2->onEvent(&ev);

    close_library(lib_handle);
    cout << "Unload library" << endl;

    return 0;
}
