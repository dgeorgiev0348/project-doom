#include "WADReader.h" // include header file

#include <cstring>

WADReader::WADReader() // default constructor
{
}

WADReader::~WADReader() // destructor
{
}

uint16_t WADReader::Read2Bytes(const uint8_t *pWADData, int offset)
{
    uint16_t ReadValue; // variable to store the read value
    std::memcpy(&ReadValue, pWADData + offset, sizeof(uint16_t)); // copy 2 bytes from data
    return ReadValue; // return value
}

uint32_t WADReader::Read4Bytes(const uint8_t *pWADData, int offset)
{
    uint32_t ReadValue; // variable to store the read value
    std::memcpy(&ReadValue, pWADData + offset, sizeof(uint32_t)); // copy 4 bytes from data
    return ReadValue; // return value
}

void WADReader::ReadHeaderData(const uint8_t *pWADData, int offset, Header &header)
{
    //0x00 to 0x03
    header.WADType[0] = pWADData[offset];       // read WAD type character 0
    header.WADType[1] = pWADData[offset + 1];   // read WAD type character 1
    header.WADType[2] = pWADData[offset + 2];   // read WAD type character 2
    header.WADType[3] = pWADData[offset + 3];   // read WAD type character 3
    header.WADType[4] = '\0';                   // null terminate the WAD type string

    //0x04 to 0x07
    header.DirectoryCount = Read4Bytes(pWADData, offset + 4);   // read directory count 

    //0x08 to 0x0b
    header.DirectoryOffset = Read4Bytes(pWADData, offset + 8);  // read directory offset
}

void WADReader::ReadDirectoryData(const uint8_t *pWADData, int offset, Directory &directory)
{
    //0x00 to 0x03
    directory.LumpOffset = Read4Bytes(pWADData, offset);    // read lump offset

    //0x04 to 0x07
    directory.LumpSize = Read4Bytes(pWADData, offset + 4);  // read lump size

    //0x08 to 0x0F
    directory.LumpName[0] = pWADData[offset + 8];   // read lump name character 0
    directory.LumpName[1] = pWADData[offset + 9];   // read lump name character 1
    directory.LumpName[2] = pWADData[offset + 10];  // read lump name character 2
    directory.LumpName[3] = pWADData[offset + 11];  // read lump name character 3
    directory.LumpName[4] = pWADData[offset + 12];  // read lump name character 4
    directory.LumpName[5] = pWADData[offset + 13];  // read lump name character 5
    directory.LumpName[6] = pWADData[offset + 14];  // read lump name character 6
    directory.LumpName[7] = pWADData[offset + 15];  // read lump name character 7
    directory.LumpName[8] = '\0';                   // null terminate the lumo name string
}

void WADReader::ReadVertexData(const uint8_t *pWADData, int offset, Vertex &vertex)
{
    //0x00 to 0x01
    vertex.XPosition = Read2Bytes(pWADData, offset);        // read X position

    //0x02 to 0x03
    vertex.YPosition = Read2Bytes(pWADData, offset + 2);    // read Y position
}

void WADReader::ReadLinedefData(const uint8_t *pWADData, int offset, Linedef &linedef)
{
    linedef.StartVertex = Read2Bytes(pWADData, offset);         // read start vertex index
    linedef.EndVertex = Read2Bytes(pWADData, offset + 2);       // read end vertex index
    linedef.Flags = Read2Bytes(pWADData, offset + 4);           // read flags 
    linedef.LineType = Read2Bytes(pWADData, offset + 6);        // read line type
    linedef.SectorTag = Read2Bytes(pWADData, offset + 8);       // read sector tag
    linedef.RightSidedef = Read2Bytes(pWADData, offset + 10);   // read right sidedef index
    linedef.LeftSidedef = Read2Bytes(pWADData, offset + 12);    // read left sidedef index
}

void WADReader::ReadThingData(const uint8_t *pWADData, int offset, Thing &thing)
{
    thing.XPosition = Read2Bytes(pWADData, offset);     // read X position
    thing.YPosition = Read2Bytes(pWADData, offset + 2); // read Y position
    thing.Angle = Read2Bytes(pWADData, offset + 4);     // read angle
    thing.Type = Read2Bytes(pWADData, offset + 6);      // read type
    thing.Flags = Read2Bytes(pWADData, offset + 8);     // reaf flags
}

void WADReader::ReadNodesData(const uint8_t *pWADData, int offset, Node &node)
{
    node.XPartition = Read2Bytes(pWADData, offset);             // read X partition
    node.YPartition = Read2Bytes(pWADData, offset + 2);         // read Y partition
    node.ChangeXPartition = Read2Bytes(pWADData, offset + 4);   // read change X partition
    node.ChangeYPartition = Read2Bytes(pWADData, offset + 6);   // read change Y partition

    node.RightBoxTop = Read2Bytes(pWADData, offset + 8);        // read rigth box top
    node.RightBoxBottom = Read2Bytes(pWADData, offset + 10);    // read right box bottom
    node.RightBoxLeft = Read2Bytes(pWADData, offset + 12);      // read right box left
    node.RightBoxRight = Read2Bytes(pWADData, offset + 14);     // read right box right

    node.LeftBoxTop = Read2Bytes(pWADData, offset + 16);        // read left box top
    node.LeftBoxBottom = Read2Bytes(pWADData, offset + 18);     // read left box bottom
    node.LeftBoxLeft = Read2Bytes(pWADData, offset + 20);       // read left box left
    node.LeftBoxRight = Read2Bytes(pWADData, offset + 22);      // read left box right

    node.RightChildID = Read2Bytes(pWADData, offset + 24);      // read right child ID
    node.LeftChildID = Read2Bytes(pWADData, offset + 26);       // read left child ID
}

void WADReader::ReadSubsectorData(const uint8_t *pWADData, int offset, Subsector &subsector)
{
    subsector.SegCount = Read2Bytes(pWADData, offset);
    subsector.FirstSegID = Read2Bytes(pWADData, offset + 2);
}

void WADReader::ReadSegData(const uint8_t *pWADData, int offset, Seg &seg)
{
    seg.StartVertexID = Read2Bytes(pWADData, offset);
    seg.EndVertexID = Read2Bytes(pWADData, offset + 2);
    seg.Angle = Read2Bytes(pWADData, offset + 4);
    seg.LinedefID = Read2Bytes(pWADData, offset + 6);
    seg.Direction = Read2Bytes(pWADData, offset + 8);
    seg.Offset = Read2Bytes(pWADData, offset + 10);
}