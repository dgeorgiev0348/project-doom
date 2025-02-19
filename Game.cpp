/*
Implements the Game class, handling SDL initialization, input processing, rendering, updating, and cleanup. 
It ensures the game runs smoothly by managing the main loop, delegating logic to DoomEngine, and handling SDL-related tasks like window creation and rendering.
*/

#include "Game.h"

#include <iostream>
#include <string>

// constructor that initializes the game window size
Game::Game() : m_iWindowWidth(1280), m_iWindowHeight(800)
{
}

// dsctructor that cleans up resources and shuts down SDL
Game::~Game()
{
    delete m_pDoomEngine;               // free memory allocated for DoomEngine
    SDL_DestroyWindow(m_pWindow);       // destroy the SDL window
    SDL_DestroyRenderer(m_pRenderer);   // destroy the SDL renderer
    SDL_Quit();                         // quit SDL
}

// initialize SDL, create a window, set up renderer and initialize the DoomEngine
bool Game::Init()
{
    //Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // create SDL window
    m_pWindow = SDL_CreateWindow(NULL, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iWindowWidth, m_iWindowHeight, SDL_WINDOW_SHOWN);
    if (m_pWindow == nullptr)
    {
        std::cout << "SDL failed to create window! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // create SDL renderer
    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
    if (m_pRenderer == nullptr)
    {
        std::cout << "SDL failed to create renderer! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // initialize DoomEngine with the renderer
    m_pDoomEngine = new DoomEngine(m_pRenderer);

    // Set correct Logical size before initializing the engine
    if (SDL_RenderSetLogicalSize(m_pRenderer, m_pDoomEngine->GetRenderWidth(), m_pDoomEngine->GetRenderHeight()) != 0)
    {
        std::cout << "SDL failed to set logical size! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // check if DoomEngine initialized correctly
    if (!m_pDoomEngine->Init())
    {
        std::cout << m_pDoomEngine->GetName() << " failed to initialize!" << std::endl;
        return false;
    }

    // set window title to the game's name
    SDL_SetWindowTitle(m_pWindow, m_pDoomEngine->GetName().c_str());

    return true;
}

// process user input events and send them to DoomEngine
void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            m_pDoomEngine->KeyPressed(event);
            break;

        case SDL_KEYUP:
            m_pDoomEngine->KeyReleased(event);
            break;

        case SDL_QUIT:
            m_pDoomEngine->Quit();
            break;
        }
    }
}

// call necessary rendering functions to draw the game frame
void Game::Render()
{
    RenderClear();              // clear the screen
    m_pDoomEngine->Render();    // render game objects
    RenderPresent();            // present the rendered frame
    SDL_RenderPresent(m_pRenderer);
}

// present the rendered frame to the screen
void Game::RenderPresent()
{
    SDL_RenderPresent(m_pRenderer);
}

// clear the screen before rendering new frame
void Game::RenderClear()
{
    SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0xff); // set clear color to black
    SDL_RenderClear(m_pRenderer);
}

// update game logic
void Game::Update()
{
    m_pDoomEngine->Update();
}

// check if game is over
bool Game::IsOver()
{
    return m_pDoomEngine->IsOver();
}

// delay execution to maintain a steady frame rate
void Game::Delay()
{
    SDL_Delay(m_pDoomEngine->GetTimePerFrame());
}