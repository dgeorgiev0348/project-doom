/*
This file defines the DoomEngine class, which serves as the core game engine. 
It manages rendering, input handling, game updates, and WAD file loading.
*/

#pragma once // ensures this file is only included once during compilation

#include <SDL2/SDL.h>   // SDL2 library for rendering and event handling
#include <string>       // standard string library

#include "Map.h"        // include the Map class
#include "Player.h"     // include the Player class
#include "WADLoader.h"  // include the WADLoader class

// core game engine managing rendering, input and game state
class DoomEngine
{
    public: 
        DoomEngine(SDL_Renderer *pRenderer);        // constructor that takes and SDL_Renderer pointer for rendering graphics
        virtual ~DoomEngine();                      // destructor for cleaning up resources

        virtual void Render();                      // render the game screen
        virtual void KeyPressed(SDL_Event &event);  // handle key press events
        virtual void KeyReleased(SDL_Event &event); // handle key release events
        virtual void Quit();                        // shut down the game and clean up resources
        virtual void Update();                      // update the game state

        virtual bool IsOver();                      // check if the game is over
        virtual bool Init();                        // initialize the game

        virtual int GetRenderWidth();               // return the rendering width of the screen
        virtual int GetRenderHeight();              // return the rendering height of the screen
        virtual int GetTimePerFrame();              // return the time per frame

        virtual std::string GetName();              // return the name of the game
        virtual std::string GetWADFileName();       // return the name of the WAD file being used

    protected:
        int m_iRenderWidth;                         // screen width for rendering
        int m_iRenderHeight;                        // screen height for rendering

        bool m_bIsOver;                             // flag to indicate if the game has ended

        SDL_Renderer *m_pRenderer;                  // pointer to the SDL renderer for drawing graphics
        WADLoader m_WADLoader;                      // handle loading and parsing WAD files
        Map *m_pMap;                                // pointer to the current game map
        Player *m_pPlayer;                          // pointer to the player object
};