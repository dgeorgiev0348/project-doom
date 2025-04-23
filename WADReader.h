/*
Defines the WADReader class, responsible for reading and interpreting data
structures directly from the raw byte data of a WAD file.
It handles parsing specific data types like Header, Directory entries,
Vertices, Linedefs, Things, and Nodes from a memory buffer.
*/

#pragma once // ensure the file is included only once during compilation

#include <cstdint>      // standard integer types like uint8_t, uint16_t, uint32_t
#include "DataTypes.h"  // WAD data structure definitions (Header, Directory, Vertex, Linedef, Thing, Node)

class WADReader
{
public:
    WADReader();    // default constructor
    ~WADReader();   // destructor

    void ReadHeaderData(const uint8_t *pWADData, int offset, Header &header);           // read the main WAD header data from the provided buffer and offset
    void ReadDirectoryData(const uint8_t *pWADData, int offset, Directory &directory);  // read a single directory entry from the buffer at the specified offset
    void ReadVertexData(const uint8_t *pWADData, int offset, Vertex &vertex);           // read data for a single vertex from the buffer at the specified offset
    void ReadLinedefData(const uint8_t *pWADData, int offset, Linedef &linedef);        // read data for a single linedef from the buffer at the specified offset
    void ReadThingData(const uint8_t *pWADData, int offset, Thing &thing);              // read data for a single thing (object/entity) from the buffer at the specified offset
    void ReadNodesData(const uint8_t *pWADData, int offset, Node &node);                // read data for a single BSP node from the buffer at the specified offset

protected:
    uint16_t Read2Bytes(const uint8_t *pWADData, int offset);   // reads a 2-byte unsigned integer (uint16_t) from the buffer at the specified offset
    uint32_t Read4Bytes(const uint8_t *pWADData, int offset);   // reads a 4-byte unsigned integer (uint32_t) from the buffer at the specified offset
};