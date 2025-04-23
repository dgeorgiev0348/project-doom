/*
This file implements the Map class, which holds the geometric and entity data
for a single Doom map (level), loaded from a WAD file. It also provides
functionality to render an overhead automap view using SDL.
*/

#include "Map.h"      // definition of the Map class and associated data types
#include <climits>    // constants like INT_MAX, INT_MIN for boundary initialization

using namespace std; // Using the standard namespace for convenience (std::string, std::vector, std::pair, etc.)

// constructor: initializes map properties, boundaries, and stores renderer/player pointers
Map::Map(SDL_Renderer *pRenderer, std::string sName, Player *pPlayer) :
    m_sName(sName),                 // Initialize map name.
    m_XMin(INT_MAX),                // Initialize minimum X coordinate to the largest possible integer value.
    m_XMax(INT_MIN),                // Initialize maximum X coordinate to the smallest possible integer value.
    m_YMin(INT_MAX),                // Initialize minimum Y coordinate to the largest possible integer value.
    m_YMax(INT_MIN),                // Initialize maximum Y coordinate to the smallest possible integer value.
    m_iAutoMapScaleFactor(15),      // Set the default scale factor for the automap (larger value = more zoomed out).
    m_iLumpIndex(-1),               // Initialize WAD lump index to -1 (indicating not set).
    m_pRenderer(pRenderer),         // Store the pointer to the SDL renderer.
    m_pPlayer(pPlayer)              // Store the pointer to the Player object.
{
    // Get the logical dimensions of the rendering target.
    SDL_RenderGetLogicalSize(m_pRenderer, &m_iRenderXSize, &m_iRenderYSize);
    // Decrement sizes because rendering coordinates are often 0-based (0 to width-1, 0 to height-1).
    --m_iRenderXSize;
    --m_iRenderYSize;
}

// destructor
Map::~Map()
{
}

// adds a vertex and updates the map's bounding box (XMin, XMax, YMin, YMax)
void Map::AddVertex(Vertex &v)
{
    // Add the vertex to the vector of vertices.
    m_Vertexes.push_back(v);

    // Update the minimum and maximum X coordinates found so far.
    if (m_XMin > v.XPosition)
    {
        m_XMin = v.XPosition;
    }
    // Use 'else if' for slight optimization; a value can't be both smaller than min and larger than max.
    else if (m_XMax < v.XPosition)
    {
        m_XMax = v.XPosition;
    }

    // Update the minimum and maximum Y coordinates found so far.
    if (m_YMin > v.YPosition)
    {
        m_YMin = v.YPosition;
    }
    else if (m_YMax < v.YPosition)
    {
        m_YMax = v.YPosition;
    }
}

// adds a linedef (wall segment) to the map's list
void Map::AddLinedef(Linedef &l)
{
    // Add the linedef to the vector of linedefs.
    m_Linedefs.push_back(l);
}

// adds a thing (entity); updates player start position if it's the player thing
void Map::AddThing(Thing &thing)
{
    // Check if this thing's type corresponds to the player start identifier.
    if (thing.Type == m_pPlayer->GetID())
    {
        // If it's the player start, set the player's initial position and angle.
        m_pPlayer->SetXPosition(thing.XPosition);
        m_pPlayer->SetYPosition(thing.YPosition);
        m_pPlayer->SetAngle(thing.Angle);
    }

    // Add the thing to the vector of things, regardless of its type.
    m_Things.push_back(thing);
}

// adds a BSP node to the map's list
void Map::AddNode(Node &node)
{
    // Add the BSP node to the vector of nodes.
    m_Nodes.push_back(node);
}

// returns the name of the map
string Map::GetName()
{
    return m_sName;
}

// converts a map X-coordinate to an automap screen X-coordinate
int Map::RemapXToScreen(int XMapPosition)
{
    // Translate the map coordinate so m_XMin is at 0, then scale down.
    // Example: If m_XMin is -100, XMapPosition is 50, scale is 10.
    // (50 + (-(-100))) / 10 = (50 + 100) / 10 = 150 / 10 = 15.
    return (XMapPosition + (-m_XMin)) / m_iAutoMapScaleFactor;
}

// converts a map Y-coordinate to an automap screen Y-coordinate (handles Y-axis inversion)
int Map::RemapYToScreen(int YMapPosition)
{
    // Translate the map coordinate so m_YMin is at 0, scale down,
    // then subtract from the render height to flip the Y-axis.
    // Example: If m_YMin is -200, YMapPosition is 100, scale is 10, height is 200.
    // (100 + (-(-200))) / 10 = (100 + 200) / 10 = 300 / 10 = 30.
    // Screen Y = 200 - 30 = 170.
    return m_iRenderYSize - (YMapPosition + (-m_YMin)) / m_iAutoMapScaleFactor;
}

// orchestrates rendering the full automap view (walls, player, etc.)
void Map::RenderAutoMap()
{
    RenderAutoMapWalls();  // Draw the map geometry.
    RenderAutoMapPlayer(); // Draw the player's current position.
    RenderAutoMapNode();   // Draw diagnostic information for the last BSP node (for debugging).
}

// renders the player's position marker on the automap
void Map::RenderAutoMapPlayer()
{
    // Set the drawing color to red for the player marker.
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red, fully opaque

    // Define offsets for a 3x3 pixel square centered on the player position.
    pair<int, int> Direction[] = {
        make_pair(-1, -1), make_pair(0, -1), make_pair(+1, -1), // Top row
        make_pair(-1, 0),  make_pair(0, 0),  make_pair(+1, 0),  // Middle row
        make_pair(-1, +1), make_pair(0, +1), make_pair(+1, +1)  // Bottom row
    };

    // Calculate the player's base screen coordinates.
    int screenX = RemapXToScreen(m_pPlayer->GetXPosition());
    int screenY = RemapYToScreen(m_pPlayer->GetYPosition());

    // Draw the 9 points forming the marker.
    for (int i = 0; i < 9; ++i)
    {
        SDL_RenderDrawPoint(m_pRenderer,
            screenX + Direction[i].first,  // Apply X offset
            screenY + Direction[i].second); // Apply Y offset
    }

    // Future enhancement: Could draw a line/arrow indicating player's angle.
}

// renders all the map walls (linedefs) on the automap
void Map::RenderAutoMapWalls()
{
    // Set the drawing color to white for walls.
    SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // White, fully opaque

    // Iterate through each linedef in the map data.
    for (Linedef &l : m_Linedefs)
    {
        // Get the start and end vertices using the indices stored in the linedef.
        Vertex vStart = m_Vertexes[l.StartVertex];
        Vertex vEnd = m_Vertexes[l.EndVertex];

        // Convert the map coordinates of the start and end vertices to screen coordinates.
        int startScreenX = RemapXToScreen(vStart.XPosition);
        int startScreenY = RemapYToScreen(vStart.YPosition);
        int endScreenX = RemapXToScreen(vEnd.XPosition);
        int endScreenY = RemapYToScreen(vEnd.YPosition);

        // Draw a line representing the wall segment on the screen.
        SDL_RenderDrawLine(m_pRenderer, startScreenX, startScreenY, endScreenX, endScreenY);
    }
}

// renders debug visualization for the last added BSP node (bounding boxes, partition line)
void Map::RenderAutoMapNode()
{
    // If there are no nodes, do nothing.
    if (m_Nodes.empty()) {
        return;
    }

    // Get the last node added to the list (often the root or a recently processed node in BSP building).
    Node node = m_Nodes.back(); // Use back() for potentially better efficiency than m_Nodes[m_Nodes.size()-1]

    // Calculate the screen coordinates for the Right Bounding Box.
    // Note: Need to handle width/height calculation carefully after remapping.
    // Adding +1 might be necessary if coordinates represent pixels and rect expects width/height.
    int rightBoxScreenX = RemapXToScreen(node.RightBoxLeft);
    int rightBoxScreenY = RemapYToScreen(node.RightBoxTop); // Top Y in map space becomes larger screen Y
    int rightBoxScreenW = RemapXToScreen(node.RightBoxRight) - rightBoxScreenX + 1;
    int rightBoxScreenH = RemapYToScreen(node.RightBoxBottom) - rightBoxScreenY + 1; // Height calculation needs care due to Y flipping

    SDL_Rect RightRect = {
        rightBoxScreenX,
        rightBoxScreenY, // This is the top-left corner in screen space
        rightBoxScreenW,
        rightBoxScreenH
    };

    // Calculate the screen coordinates for the Left Bounding Box.
    int leftBoxScreenX = RemapXToScreen(node.LeftBoxLeft);
    int leftBoxScreenY = RemapYToScreen(node.LeftBoxTop);
    int leftBoxScreenW = RemapXToScreen(node.LeftBoxRight) - leftBoxScreenX + 1;
    int leftBoxScreenH = RemapYToScreen(node.LeftBoxBottom) - leftBoxScreenY + 1;

    SDL_Rect LeftRect = {
        leftBoxScreenX,
        leftBoxScreenY, // Top-left corner in screen space
        leftBoxScreenW,
        leftBoxScreenH
    };

    // Draw the Right Bounding Box in Green.
    SDL_SetRenderDrawColor(m_pRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE); // Green
    SDL_RenderDrawRect(m_pRenderer, &RightRect);

    // Draw the Left Bounding Box in Red.
    SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Red
    SDL_RenderDrawRect(m_pRenderer, &LeftRect);

    // Draw the Partition Line in Blue.
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE); // Blue
    SDL_RenderDrawLine(m_pRenderer,
        RemapXToScreen(node.XPartition),                     // Start X of partition line
        RemapYToScreen(node.YPartition),                     // Start Y of partition line
        RemapXToScreen(node.XPartition + node.ChangeXPartition), // End X of partition line
        RemapYToScreen(node.YPartition + node.ChangeYPartition)); // End Y of partition line
}


// sets the WAD lump index associated with this map
void Map::SetLumpIndex(int iIndex)
{
    m_iLumpIndex = iIndex;
}

// retrieves the WAD lump index associated with this map
int Map::GetLumpIndex()
{
    return m_iLumpIndex;
}