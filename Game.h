/*
Defines the Game class, which manages the main game loop, input handling, rendering, and initialization. 
It provides the core functionality to run and control the game, using SDL for rendering and a DoomEngine instance for game logic.
*/

#pragma once // ensure the file is included only once during compilation

#include <SDL2/SDL.h> // SDL2 library for rendering and handling graphics

#include "DoomEngine.h" // include DoomEngine class definition

// game class that manages the overall game loop, window and rendering
class Game
{
    public:
        Game();                     // constructor that initializes the Game object
        virtual ~Game();            // destructor that cleans up resources

        void ProcessInput();        // handle user input
        void Render();              // render game elements on screen
        void Update();              // update game logic and state
        void Delay();               // delay execution to control the game's framerate
        void RenderPresent();       // presents the render frame to the screen
        void RenderClear();         // clear the screen before rendering new screen

        bool IsOver();              // check if game has ended
        bool Init();                // initialize the game

    protected:
        int m_iWindowWidth;         // width of the game window
        int m_iWindowHeight;        // height of the game window

        SDL_Window *m_pWindow;      // pointer to the SDL window
        SDL_Renderer *m_pRenderer;  // pointer to the SDL renderer
        DoomEngine *m_pDoomEngine;  // pointer to the DoomEngine instance
};