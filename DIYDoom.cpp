/*
This is the main entry point for the Doom remake, initializing the game and running the main loop, 
which processes input, updates game logic, renders frames, and manages timing.
*/

#include <iostream> // standard input/output stream library 

#include "Game.h"   // include the game class definition

// entry point for the game
int main(int argc, char* argv[])
{
    Game game;      // create an instance of the game class
    game.Init();    // initialize the game

    // main game loop: runs until the game is over
    while (!game.IsOver())
    {
        game.ProcessInput();    // handle user input
        game.Update();          // update game logic
        game.Render();          // render the game frame to screen
        game.Delay();           // apply a delay to control frame rate
    }
    
    return 0; // exit the program successfully
}