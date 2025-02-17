#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Map.h"
#include "Player.h"
#include "WADLoader.h"

class DoomEngine
{
    public: 
        DoomEngine(SDL_Renderer *pRenderer);
        virtual ~DoomEngine();

        virtual void Render(); // draw something to show on screen
        virtual void KeyPressed(SDL_Event &event); // which keys are pressed
        virtual void KeyReleased(SDL_Event &event); // which keys are released
        virtual void Quit(); // close and shutdown the game
        virtual void Update();

        virtual bool IsOver(); // did the game end
        virtual bool Init(); // initialize game object

        virtual int GetRenderWidth();
        virtual int GetRenderHeight();
        virtual int GetTimePerFrame();

        virtual std::string GetName();
        virtual std::string GetWADFileName();

    protected:
        int m_iRenderWidth;
        int m_iRenderHeight;

        bool m_bIsOver;

        SDL_Renderer *m_pRenderer;
        WADLoader m_WADLoader; // game engine will own the loader
        Map *m_pMap; // game engine will own the map
        Player *m_pPlayer;
};