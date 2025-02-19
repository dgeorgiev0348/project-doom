#pragma once

#include <cstdint>

#include "DataTypes.h"

class WADReader
{
public:
    WADReader();    // default constructor
    ~WADReader();   // destructor

    void ReadHeaderData(const uint8_t *pWADData, int offset, Header &header);           // read header data from the WAD file
    void ReadDirectoryData(const uint8_t *pWADData, int offset, Directory &directory);  // read directory data from the WAD file
    void ReadVertexData(const uint8_t *pWADData, int offset, Vertex &vertex);           // read vertex data from the WAD file
    void ReadLinedefData(const uint8_t *pWADData, int offset, Linedef &linedef);        // read linedef data from the WAD file
    void ReadThingData(const uint8_t *pWADData, int offset, Thing &thing);              // read things data from the WAD file
    void ReadNodesData(const uint8_t *pWADData, int offset, Node &node);                // read nodes data from the WAD file

protected:
    uint16_t Read2Bytes(const uint8_t *pWADData, int offset);                           // helper method to read 2 bytes from the WAD file starting at the given offset.
    uint32_t Read4Bytes(const uint8_t *pWADData, int offset);                           // helper method to read 4 bytes from the WAD file starting at the given offset.
};