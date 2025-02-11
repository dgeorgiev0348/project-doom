#include <iostream>
#include "WADLoader.h"

int main()
{
    WADLoader wadLoader("/home/gushtera/Documents/project-doom-build/WAD/DOOM.WAD");
    wadLoader.LoadWAD();
    return 0;
}