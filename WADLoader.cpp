#include "WADLoader.h"

#include <iostream>

using namespace std;

// constructor that initializes the WADLoaded and sets the m_WADData to NULL
WADLoader::WADLoader() : m_WADData(NULL)
{
}

// destructor that cleans up dynamically allocated memory for the WAD data
WADLoader::~WADLoader()
{
    delete[] m_WADData;
}

// set the file path to the WAD file
void WADLoader::SetWADFilePath(std::string sWADFilePath)
{
    m_sWADFilePath = sWADFilePath;
}

// loads the WAD file
bool WADLoader::LoadWAD()
{
    if (!OpenAndLoad())     // open and load the WAD file into memory
    {
        return false;
    }

    if (!ReadDirectories()) // read directory structure of the WAD file
    {
        return false;
    }

    return true;
}

// open the WAD file, read its contents into memory and close it
bool WADLoader::OpenAndLoad()
{
    std::cout << "Info: Loading WAD file: " << m_sWADFilePath << endl;

    m_WADFile.open(m_sWADFilePath, ifstream::binary);   // open file in binary mode
    if (!m_WADFile.is_open())
    {
        cout << "Error: Failed to open WAD file" << m_sWADFilePath << endl;
        return false;
    }
    
    // determine file size
    m_WADFile.seekg(0, m_WADFile.end);  
    size_t length = m_WADFile.tellg();

    // free any previously allocated memory before allocating new space
    if (m_WADData)
    {
        delete[] m_WADData;
    }

    // allocate memory for storing WAD data
    m_WADData = new uint8_t[length];
    if (m_WADData == NULL)
    {
        cout << "Error: Failed alocate memory for WAD file of size " << length << endl;
        return false;
    }

    // read WAD file int memory
    m_WADFile.seekg(ifstream::beg);
    m_WADFile.read((char *)m_WADData, length);

    m_WADFile.close();  // close the file

    cout << "Info: Loading complete." << endl;

    return true;
}

// reads and stores directory information from the WAD file
bool WADLoader::ReadDirectories()
{
    Header header;
    m_Reader.ReadHeaderData(m_WADData, 0, header);  // read header information

    Directory directory;

    // iterate through the directory section and store all entries
    for (unsigned int i = 0; i < header.DirectoryCount; ++i)
    {
        m_Reader.ReadDirectoryData(m_WADData, header.DirectoryOffset + i * 16, directory);
        m_WADDirectories.push_back(directory);
    }

    return true;
}

// load map-specific data
bool WADLoader::LoadMapData(Map *pMap)
{
    std::cout << "Info: Parsing Map: " << pMap->GetName() << endl;

    std::cout << "Info: Processing Map Vertex" << endl;
    if (!ReadMapVertex(pMap))
    {
        cout << "Error: Failed to load map vertex data MAP: " << pMap->GetName() << endl;
        return false;
    }

    std::cout << "Info: Processing Map Linedef" << endl;
    if (!ReadMapLinedef(pMap))
    {
        cout << "Error: Failed to load map linedef data MAP: " << pMap->GetName() << endl;
        return false;
    }

    std::cout << "Info: Processing Map Things" << endl;
    if (!ReadMapThings(pMap))
    {
        cout << "Error: Failed to load map thing data MAP: " << pMap->GetName() << endl;
        return false;
    }

    std::cout << "Info: Processing Map Nodes" << endl;
    if (!ReadMapNodes(pMap))
    {
        cout << "Error: Failed to load map node data MAP: " << pMap->GetName() << endl;
        return false;
    }

    return true;
}

// find the index of the specified map in the WAD directory
int WADLoader::FindMapIndex(Map *pMap)
{
    if (pMap->GetLumpIndex() > -1)  // check if the map already has a stored index
    {
        return pMap->GetLumpIndex();
    }

    // iterate through the WAD directories to find the map by name
    for (size_t i = 0; i < m_WADDirectories.size(); ++i)
    {
        if (m_WADDirectories[i].LumpName == pMap->GetName())
        {
            pMap->SetLumpIndex(i);
            return i; // return map index
        }
    }

    return -1; // map nout found
}

// read vertex data from the WAD file and store it in the map
bool WADLoader::ReadMapVertex(Map *pMap)
{
    int iMapIndex = FindMapIndex(pMap); // find map index in directory list

    // check if map index is valid
    if (iMapIndex == -1)
    {
        return false;
    }

    // move to the vertex lump in the WAD directory
    iMapIndex += EMAPLUMPSINDEX::eVERTEXES;

    // verify the lump name matches
    if (strcmp(m_WADDirectories[iMapIndex].LumpName, "VERTEXES") != 0)
    {
        return false;
    }

    // calculate the number of vertices by dividing the lump size by the size of a single vertex structure
    int iVertexSizeInBytes = sizeof(Vertex);
    int iVertexesCount = m_WADDirectories[iMapIndex].LumpSize / iVertexSizeInBytes;

    // temporary vertex object to hold data while reading
    Vertex vertex;
    for (int i = 0; i < iVertexesCount; ++i)
    {
        m_Reader.ReadVertexData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iVertexSizeInBytes, vertex); // Read vertex data from WAD file into the temporary vertex object
        pMap->AddVertex(vertex); // Add the vertex to the map
    }

    return true;
}

// read linedef data from the WAD file and store it in the map
bool WADLoader::ReadMapLinedef(Map *pMap)
{
    int iMapIndex = FindMapIndex(pMap); // find map index in directory list

    // check if map index is valid
    if (iMapIndex == -1)
    {
        return false;
    }

    // move to the linedef lump in the WAD directory
    iMapIndex += EMAPLUMPSINDEX::eLINEDEFS;

    // verify the lump name matches
    if (strcmp(m_WADDirectories[iMapIndex].LumpName, "LINEDEFS") != 0)
    {
        return false;
    }

    // calculate the number of linedefs by dividing the lump size by the size of a single linedef structure
    int iLinedefSizeInBytes = sizeof(Linedef);
    int iLinedefCount = m_WADDirectories[iMapIndex].LumpSize / iLinedefSizeInBytes;

    // temporary linedef object to hold data while reading
    Linedef linedef;
    for (int i = 0; i < iLinedefCount; ++i)
    {
        m_Reader.ReadLinedefData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iLinedefSizeInBytes, linedef); // read linedef data from WAD file into the temporary linedef object
        pMap->AddLinedef(linedef); // add the linedef to the map
    }

    return true;
}

// read thing data from the WAD file and store it in the map
bool WADLoader::ReadMapThings(Map *pMap)
{
    int iMapIndex = FindMapIndex(pMap); // find map index in directory list

    // check if map index is valid
    if (iMapIndex == -1)
    {
        return false;
    }

    // move to the thing lump in the WAD directory
    iMapIndex += EMAPLUMPSINDEX::eTHINGS;

    // verify the lump name matches
    if (strcmp(m_WADDirectories[iMapIndex].LumpName, "THINGS") != 0)
    {
        return false;
    }

    // calculate the number of things by dividing the lump size by the size of a single thing structure
    int iThingsSizeInBytes = sizeof(Thing);
    int iThingsCount = m_WADDirectories[iMapIndex].LumpSize / iThingsSizeInBytes;

    // temporary thing object to hold data while reading
    Thing thing;
    for (int i = 0; i < iThingsCount; ++i)
    {
        m_Reader.ReadThingData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iThingsSizeInBytes, thing); // read thing data from WAD file into the temporary thing object
        pMap->AddThing(thing); // add the thing to the map
    }

    return true;
}

// read BSP node data from the WAD file and stores it in the map
bool WADLoader::ReadMapNodes(Map *pMap)
{
    int iMapIndex = FindMapIndex(pMap); // find map index in directory list

    // check if map index is valid
    if (iMapIndex == -1)
    {
        return false;
    }

    // move to the nodes lump in the WAD directory
    iMapIndex += EMAPLUMPSINDEX::eNODES;

    // verify the lump name matches
    if (strcmp(m_WADDirectories[iMapIndex].LumpName, "NODES") != 0)
    {
        return false;
    }

    // calculate the number of nodes by dividing the lump size by the size of a single node structure
    int iNodesSizeInBytes = sizeof(Node);
    int iNodesCount = m_WADDirectories[iMapIndex].LumpSize / iNodesSizeInBytes;

    // temporary node object to hold data while reading
    Node node;
    for (int i = 0; i < iNodesCount; ++i)
    {
        m_Reader.ReadNodesData(m_WADData, m_WADDirectories[iMapIndex].LumpOffset + i * iNodesSizeInBytes, node); // read node data from WAD file into the temporary node object
        pMap->AddNode(node); // add the node to the map
    }

    return true;
}