/*
Defines the Map class, which represents a game level. 
It stores and manages map elements like vertices, linedefs, things (enemies, objects), and BSP nodes. 
It also provides functions for rendering the automap and transforming map coordinates to screen coordinates.
*/

#pragma once // ensure the file is included only once during compilation

#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "DataTypes.h"
#include "Player.h"

class Map
{
    public:
        // constructor that initializes the map with a renderer, name, and player reference
        Map(SDL_Renderer *pRenderer, std::string sName, Player *pPlayer);
        ~Map(); // destructor that cleans up any allocated resources

        std::string GetName();                  // return the name of the map
        void AddVertex(Vertex &v);              // add a new vertex to the map's vertex list
        void AddLinedef(Linedef &l);            // add a new linedef to the map
        void AddThing(Thing &thing);            // add a new thing to the map
        void AddNode(Node &node);               // add a new BSP tree node to the map
        void AddSubsector(Subsector &subsector);
        void AddSeg(Seg &seg);
        void RenderAutoMap();                   // render the entire automap
        void SetLumpIndex(int iIndex);          // set the lump index for the map data

        int GetLumpIndex();                     // retrieves the lump index for the map data

    protected:
        void RenderAutoMapPlayer();             // render the player on the automap
        void RenderAutoMapWalls();              // render the walls on the automap
        void RenderBSPNodes();
        void RenderAutoMapNode(int iNodeID);    // render the BSP three nodes on the automap
        void RenderBSPNodes(int iNodeID);
        void RenderSubsector(int iSubsectorID);

        int RemapXToScreen(int XMapPosition);   // convert the map's X coordinate to screen space
        int RemapYToScreen(int YMapPosition);   // convert the map's X coordinate to screen space

        bool IsPointOnLeftSide(int XPosition, int YPosition, int iNodeID);
        
        std::string m_sName;                    // name of the map
        std::vector<Vertex> m_Vertexes;         // collection of map vertices
        std::vector<Linedef> m_Linedefs;        // collection of map walls
        std::vector<Thing> m_Things;            // collection of map things
        std::vector<Node> m_Nodes;              // BSP tree nodes for rendering
        std::vector<Subsector> m_Subsector;
        std::vector<Seg> m_Segs;

        int m_XMin;                             // minimum X coordinate of the map
        int m_XMax;                             // maximum X coordinate of the map
        int m_YMin;                             // minimum Y coordinate of the map
        int m_YMax;                             // maximum Y coordinate of the map
        int m_iRenderXSize;                     // render width for the automap
        int m_iRenderYSize;                     // render height for the automap
        int m_iAutoMapScaleFactor;              // scaling factor for the automap
        int m_iLumpIndex;                       // index in the WAD file for map data

        SDL_Renderer *m_pRenderer;              // SDL renderer for drawing the automap

        Player *m_pPlayer;                      // reference to the player in the map
};