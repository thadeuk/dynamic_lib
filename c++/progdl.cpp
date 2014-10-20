#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "lib/libblock.h"

using namespace std;

AbstractBlock *(*getBlockInstance)(int);

void load_functions(void *lib_handle){
    char *error;

    getBlockInstance = (AbstractBlock *(*)(int))dlsym(lib_handle, "getInstance");

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

    AbstractBlock *myBlock1 = getBlockInstance(1);
    AbstractBlock *myBlock2 = getBlockInstance(2);

    myBlock1->init();
    myBlock2->init();

    close_library(lib_handle);
    cout << "Unload library" << endl;

    return 0;
}
