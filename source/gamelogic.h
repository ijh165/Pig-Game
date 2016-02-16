#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QtGlobal>

//define rolling bools
#define PLAYER_ROLL_ONE false
#define PLAYER_NOT_ROLL_ONE true
//define turn bools
#define PLAYER_ONE_TURN false
#define PLAYER_TWO_TURN true

class GameLogic
{
public:
    //constructor
    GameLogic();
    //getters
    bool getWhoseTurn();
    int getRolling();
    int getTurnTotal();
    int getP1totalScore();
    int getP2totalScore();
    int getNumOfTurns();
    //initializer
    void init();
    //game logistic functions
    int roll();
    void P1hold();
    void P2hold();
    bool P1roll();
    bool P2roll();

private:
    //private variables
    bool whoseTurn;
    int rolling;
    int turnTotal;
    int P1totalScore;
    int P2totalScore;
    int numOfTurns;
};

#endif // GAMELOGIC_H
