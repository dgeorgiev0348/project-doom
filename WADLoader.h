#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector> 

#include "DataTypes.h"

class WADLoader
{
    public: 
        WADLoader(std::string sWADFilePath); // Make sure WAD file is passed
        bool LoadWAD(); // Call other helper functions to open and load the WAD file

        ~WADLoader(); // Clean up

    protected:
        bool OpenAndLoad(); // Open the file and load it to memory
        bool ReadDirectories(); // A function what will iterate through the directory section

        std::string m_sWADFilePath; // Store the file name passed to the constructor
        std::ifstream m_WADFile; // the file stream that will pint to the WAD file
        uint8_t *m_WADData; // load the file and keep it memory
        std::vector<Directory> m_WADDirectories; // store all directories in thie vector
};