/*
This file defines the structures and enumerations used for parsing and handling Doom's WAD files, including map data, entities, and BSP nodes.
*/

#pragma once // ensures the file is included only once in a single compilation

#include <cstdint> // include for fixed-width integer types

// enum representing different lump indices in a WAD file
enum EMAPLUMPSINDEX
{
    eName,      // name of the map
    eTHINGS,    // list of entities (enemies, items, player stats, etc.)
    eLINEDEFS,  // line definitions (walls and interactive elements)
    eSIDEDDEFS, // side definitions (textures and properties for walls)
    eVERTEXES,  // vertices (points in the map geometry)
    eSEAGS,     // segments (used in rendering and collisions)
    eSSECTORS,  // sub-sectors (used in redering and partitioning the map)
    eNODES,     // BSP tree nodes (used for rendering and visibility checks)
    eSECTORS,   // sectors (areas of the maps with properties like height, lighting, etc.)
    eREJECT,    // reject table (used for optimizing AI pathfinding)
    eBLOCKMAP,  // blockmap (used for collision detection and patial parititioning)
    eCOUNT      // total count of lump indices
};

// enum defining different line (wall) flags used in maps
enum ELINEDEFFLAGS
{
    eBLOCKING       = 0,    // blocks everything
    eBLOCKMONSTERS  = 1,    // blocks only monsters
    eTWOSIDED       = 2,    // can be seen from both sides
    eDONTPEGTOP     = 4,    // texture alignment flag (prevents movement when ceiling height changes)
    eDONTPEGBOTTOM  = 8,    // texture alignment flag (prevents movement when floor heigth changes)
    eSECRET         = 16,   // line is visible on the map
    eSOUNDBLOCK     = 32,   // blocks sound propagation
    eDONTDRAW       = 64,   // prevents the line from being drawn
    eDRAW           = 128   // forces the line to be drawn
};

// strucure defining the header of a WAD file
struct Header
{
    char WADType[5];            // type of WAD file ("IWAD" for game data, "PWAD" for patches/mods)
    uint32_t DirectoryCount;    // number of directory entries (lumps)
    uint32_t DirectoryOffset;   // offset to the lump directory
};

// structure defining a directory entry for lumps (data blocks) in a WAD file
struct Directory
{
    uint32_t LumpOffset;    // offset to the lump data in the files
    uint32_t LumpSize;      // size of the lump data in bytes
    char LumpName[9];       // name of the lump (8 characters + null terminator)
};

// structure representing a vertex (point in 2D space) in a map
struct Vertex
{
    int16_t XPosition;  // X coordinate
    int16_t YPosition;  // Y coordinate
};

// structure representing a linedef (wall) in a map
struct Linedef
{
    uint16_t StartVertex;   // index of starting vertex
    uint16_t EndVertex;     // index of ending vertex
    uint16_t Flags;         // linedef flags (ELINEDEFFLAGS)
    uint16_t LineType;      // special type of line (doors, switches, teleporters, etc.)
    uint16_t SectorTag;     // identifier for sector-based triggers (linked doors and switches)
    uint16_t RightSidedef;  // lindex of right-sidedef (0xFFFF if none)
    uint16_t LeftSidedef;   // lindex of left-sidedef (0xFFFF if none)
};

// structure representing an entity (thing) in a map
struct Thing
{
    int16_t XPosition;  // X coordinate
    int16_t YPosition;  // Y coordinate
    uint16_t Angle;     // facing angle
    uint16_t Type;      // type (player, enemy, item, etc.)
    uint16_t Flags;     // flags for entity behavior (difficulty-specific spawn settings)
};

// structure representing a node in the BSP tree for rendering and collision detection
struct Node
{
    int16_t XPartition;         // X coordinate of partition line
    int16_t YPartition;         // Y coordinate of partition line
    int16_t ChangeXPartition;   // delta X for partition slope
    int16_t ChangeYPartition;   // delta Y for partition slope

    int16_t RightBoxTop;        // top boundary of the right child bounding box
    int16_t RightBoxBottom;     // bottom boundary of the right child bounding box
    int16_t RightBoxLeft;       // left boundary of the right child bounding box
    int16_t RightBoxRight;      // right boundary of the right child bounding box

    int16_t LeftBoxTop;         // top boundary of the left child bounding box
    int16_t LeftBoxBottom;      // bottom boundary of the left child bounding box
    int16_t LeftBoxLeft;        // left boundary of the left child bounding box
    int16_t LeftBoxRight;       // right boundary of the left child bounding box

    uint16_t RightChildID;      // index of the right child node or subsector (if MSB is set, it's a leaf)
    uint16_t LeftChildID;       // index of the left child node or subsector (if MSB is set, it's a leaf)
};