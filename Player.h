/*
Defines the Player class, which represents a player in the game. 
It stores the player's ID, position (X, Y), and angle (facing direction). 
*/

#pragma once // ensure the file is included only once during compilation

#include <SDL2/SDL.h>

class Player
{
    public:
        Player(int iID);                    // constructor that initializes the player with a unique ID
        ~Player();                          // destructor for the player class

        void SetXPosition(int XPosition);   // set the X position of the player
        void SetYPosition(int YPosition);   // set the Y position of the player
        void SetAngle(int Angle);           // set the facing direction of the player

        int GetID();                        // return the ID of the player
        int GetXPosition();                 // return the X position of the player
        int GetYPosition();                 // return the Y position of the player
        int GetAngle();                     // retutn the facing direction of the player

    protected:
        int m_iPlayerID;                    // unique player ID
        int m_XPosition;                    // player X coordinate
        int m_YPosition;                    // player Y coordinate
        int m_Angle;                        // player facing direction
};