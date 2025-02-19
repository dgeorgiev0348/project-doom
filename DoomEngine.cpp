/*
This file implements the DoomEngine class, handling game initialization, rendering, input processing, and updating the game state.
*/

#include "DoomEngine.h"

using namespace std;

// constructor initializing the DoomEngine with a renderer and default values
DoomEngine::DoomEngine(SDL_Renderer *pRenderer) : m_iRenderWidth(320), m_iRenderHeight(200), m_bIsOver(false), m_pRenderer(pRenderer)
{
}

// destructor that cleans up dynamically allocated resources
DoomEngine::~DoomEngine()
{
    delete m_pMap;      // free memory allocated for the map
    delete m_pPlayer;   // free memory allocated for the player
}

// initialize the game engine, load WAD file and set up the map and player
bool DoomEngine::Init()
{
    // Create Player and Map objects after renderer is set up
    m_pPlayer = new Player(1);                          // create a new player object
    m_pMap = new Map(m_pRenderer, "E1M1", m_pPlayer);   // load the E1M1 map with the player

    m_WADLoader.SetWADFilePath(GetWADFileName());       // set the path to the WAD file
    m_WADLoader.LoadWAD();                              // load the WAD file into memory

    m_WADLoader.LoadMapData(m_pMap);                    // load the map data from the WAD into the game
    return true;
}

// return the path to the WAD file
std::string DoomEngine::GetWADFileName()
{
    return "/home/gushtera/Documents/project-doom-build/WAD/DOOM.WAD";
}

// render the game screen
void DoomEngine::Render()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0x00, 0x00, 0x00, 0x00);    // set background color to black
    SDL_RenderClear(m_pRenderer);                                   // clear the screen 
    m_pMap->RenderAutoMap();                                        // render the automap
}

// handle key press events
void DoomEngine::KeyPressed(SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:       // handle up arrow key
        break;  

    case SDLK_DOWN:     // handle down arrow key
        break;

    case SDLK_LEFT:     // handle left arrow key
        break;

    case SDLK_RIGHT:    // handle right arrow key
        break;

    case SDLK_ESCAPE:   // if Escape key is pressed, quit the game
        Quit();
        break;

    default:
        break;
    }
}

// handle key release events
void DoomEngine::KeyReleased(SDL_Event &event)
{
}

// quit the game (set the game-over flag to true)
void  DoomEngine::Quit()
{
    m_bIsOver = true;
}

// update the game logic
void DoomEngine::Update()
{

}

// check if game is over
bool DoomEngine::IsOver()
{
    return m_bIsOver;
}

// return the screen width for rendering
int DoomEngine::GetRenderWidth()
{
    return m_iRenderWidth;
}

// return the screen height for rendering
int DoomEngine::GetRenderHeight()
{
    return m_iRenderHeight;
}

// return the name of the game
string DoomEngine::GetName()
{
    return "Project-DOOM";
}

// return the time per frame in milliseconds
int DoomEngine::GetTimePerFrame()
{
    return 1000 / 60;
}