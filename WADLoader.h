#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector> 

#include "DataTypes.h"
#include "WADReader.h"
#include "Map.h"

class WADLoader
{
    public: 
        WADLoader();                                    // constructor
        ~WADLoader();                                   // destructor that cleans up memory and closes the file
        
        void SetWADFilePath(std::string sWADFilePath);  // set the file path to the WAD file
        bool LoadWAD();                                 // call other helper functions to open and load the WAD file
        bool LoadMapData(Map *pMap);                    // load map-specific data from the WAD file

    protected:
        bool OpenAndLoad();                             // open the file and load it to memory
        bool ReadDirectories();                         // terate through the directory section
        bool ReadMapVertex(Map *pMap);                  // read vertex data from WAD file
        bool ReadMapLinedef(Map *pMap);                 // read linedef data from WAD file
        bool ReadMapThings(Map *pMap);                  // read things data from WAD file
        bool ReadMapNodes(Map *pMap);                   // read BSP node data from WAD file
        bool ReadMapSubsectors(Map *pMap);
        bool ReadMapSegs(Map *pMap);
        
        int FindMapIndex(Map *pMap);                    // find the index of a specific map

        std::string m_sWADFilePath;                     // store the file name passed to the constructor
        std::ifstream m_WADFile;                        // the file stream that will point to the WAD file
        std::vector<Directory> m_WADDirectories;        // store all directories in this vector
        uint8_t *m_WADData;                             // load the file and keep it memory
        WADReader m_Reader;
};