/*
Implements the Player class functions defined in Player.h. 
It initializes the player with an ID, allows updating the position and angle, and provides methods to retrieve these values.
*/

#include "Player.h"

// constructor that initializes player with a unique ID
Player::Player(int iID) : m_iPlayerID(iID)
{
}

// destructor for the player class
Player::~Player()
{
}

// return the player ID
int Player::GetID()
{
    return m_iPlayerID;
}

// return the player X position
int Player::GetXPosition()
{
    return m_XPosition;
}

// return the player Y position
int Player::GetYPosition()
{
    return m_YPosition;
}

// return the player facing direction
int Player::GetAngle()
{
    return m_Angle;
}

// set player X position
void Player::SetXPosition(int XPosition)
{
    m_XPosition = XPosition;
}

// set player Y position
void Player::SetYPosition(int YPosition)
{
    m_YPosition = YPosition;
}

// set player facing direction
void Player::SetAngle(int Angle)
{
    m_Angle = Angle;
}