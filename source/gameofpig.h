#ifndef GAMEOFPIG_H
#define GAMEOFPIG_H

#include <QMainWindow>
#include <QtWidgets>
#include <QStack>
#include <QQueue>
#include <QString>
#include <QTimer>
#include "gamelogic.h"

/*Log message color*/
#define RED_TEXT  0
#define BLUE_TEXT 1

/*Current mode*/
#define ONE_PLAYER_MODE 0
#define TWO_PLAYER_MODE 1

/* Page_Index: the index in this list should match with the UI stacked widget */
enum Page_Index {
    MAIN_MENU_PAGE_INDEX = 0,
    ONE_PLAYER_PAGE_INDEX = 1,
    TWO_PLAYER_PAGE_INDEX = 2,
};

namespace Ui {
class GameOfPig;
}

class GameOfPig : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameOfPig(QWidget *parent = 0);
    ~GameOfPig();

    //asks user confirmation when closing application
    void closeEvent(QCloseEvent* event);

    //helper functions
    void init();
    void printLogMessage(int, QString);
    void clearLogMessage();
    void displayPage(Page_Index);
    void onePlayerTextButtonCtrl();
    void onePlayerInitNumbers();
    void twoPlayerTextButtonCtrl();
    void twoPlayerInitNumbers();
    void gameOver(int, QString);
    void rollAnimation();

private slots:

    //main menu button controls
    void on_OnePlayerModeBt_clicked();
    void on_TopMainMenuBt_clicked();

    //1-player mode button controls
    void on_HumanRollBt_clicked();
    void on_HumanHoldBt_clicked();

    //2-player mode button controls
    void on_TwoPlayerModeBt_clicked();
    void on_Player1RollBt_clicked();
    void on_Player1HoldBt_clicked();
    void on_Player2RollBt_clicked();
    void on_Player2HoldBt_clicked();

    //custom slot
    void computerPlaying();

private:
    Ui::GameOfPig *ui;
    GameLogic gameLogic; //gameLogic object
    QStack<Page_Index> pageStack; //stack to keep track of page history (not used in this program because not required)
    QTimer* computerTimer; //for computer playing demonstration
    int computerTimerInt; //computer timer value
    bool computerIsPlaying; //boolean whether computer is currently playing or not
};

#endif // GAMEOFPIG_H
