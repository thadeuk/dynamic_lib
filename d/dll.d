import core.stdc.stdio;

extern (C) int dll()
{
    printf("dll()\n");
    return 42;
}

