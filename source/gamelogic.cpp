#include "gamelogic.h"

/* =====================================================================
 *                              CONSTRUCTOR
 * =====================================================================*/

GameLogic::GameLogic()
{
    init();
}

/* =====================================================================
 *                                GETTERS
 * =====================================================================*/

bool GameLogic::getWhoseTurn()
{
    return whoseTurn;
}

int GameLogic::getRolling()
{
    return rolling;
}

int GameLogic::getTurnTotal()
{
    return turnTotal;
}

int GameLogic::getP1totalScore()
{
    return P1totalScore;
}

int GameLogic::getP2totalScore()
{
    return P2totalScore;
}

int GameLogic::getNumOfTurns()
{
    return numOfTurns;
}

/* =====================================================================
 *                              INITIALIZER
 * =====================================================================*/

void GameLogic::init() //to be used by constructor and also in when new game starts
{
    whoseTurn = PLAYER_ONE_TURN;
    rolling = 0;
    turnTotal = 0;
    P1totalScore = 0;
    P2totalScore = 0;
    numOfTurns = 0;
}

/* =====================================================================
 *                         GAME LOGISTIC FUNCTIONS
 * =====================================================================*/

int GameLogic::roll()
{
    return (rand()%6 + 1);
}

void GameLogic::P1hold()
{
    P1totalScore += turnTotal;
    rolling = 0;
    turnTotal = 0;
    numOfTurns++;
    whoseTurn = PLAYER_TWO_TURN;
}

void GameLogic::P2hold()
{
    P2totalScore += turnTotal;
    rolling = 0;
    turnTotal = 0;
    numOfTurns++;
    whoseTurn = PLAYER_ONE_TURN;
}

bool GameLogic::P1roll()
{
    rolling = roll();
    if(rolling == 1)
    {
        rolling = 0;
        turnTotal = 0;
        numOfTurns++;
        whoseTurn = PLAYER_TWO_TURN;
        return PLAYER_ROLL_ONE;
    }
    turnTotal += rolling;
    return PLAYER_NOT_ROLL_ONE;
}

bool GameLogic::P2roll()
{
    rolling = roll();
    if(rolling == 1)
    {
        rolling = 0;
        turnTotal = 0;
        numOfTurns++;
        whoseTurn = PLAYER_ONE_TURN;
        return PLAYER_ROLL_ONE;
    }
    turnTotal += rolling;
    return PLAYER_NOT_ROLL_ONE;
}
