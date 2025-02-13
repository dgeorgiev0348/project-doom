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
        WADLoader();
        void SetWADFilePath(std::string sWADFilePath);
        bool LoadWAD(); // Call other helper functions to open and load the WAD file
        bool LoadMapData(Map *pMap);

        ~WADLoader(); // Clean up

    protected:
        bool OpenAndLoad(); // Open the file and load it to memory
        bool ReadDirectories(); // A function what will iterate through the directory section
        bool ReadMapVertex(Map *pMap);
        bool ReadMapLinedef(Map *pMap);
        bool ReadMapThings(Map *pMap);
        int FindMapIndex(Map *pMap);

        std::string m_sWADFilePath; // Store the file name passed to the constructor
        std::ifstream m_WADFile; // the file stream that will pint to the WAD file
        std::vector<Directory> m_WADDirectories; // store all directories in thie vector
        uint8_t *m_WADData; // load the file and keep it memory
        WADReader m_Reader;
};