#include <iostream>
#include "WADLoader.h"

int main()
{
    WADLoader wadLoader("/home/gushtera/Documents/project-doom-build/WAD/DOOM.WAD");
    wadLoader.LoadWAD();

    Map map("E1M1");
    wadLoader.LoadMapData(map);
    
    return 0;
}