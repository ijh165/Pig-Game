//  Created by Ivan Jonathan Hoo
//  Copyright (c) 2015 Ivan Jonathan Hoo. All rights reserved.

#include "gameofpig.h"
#include "ui_gameofpig.h"
#include <QDebug>
#include <QLCDNumber>

GameOfPig::GameOfPig(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameOfPig)
{
    ui->setupUi(this);
    init();
}

GameOfPig::~GameOfPig()
{
    delete ui;
}

//asks user confirmation when closing application
void GameOfPig::closeEvent(QCloseEvent *event)
{
    //pause computer playing
    if(computerIsPlaying)
        computerTimer->stop();

    //asks user confirmation
    event->ignore();
    if(QMessageBox::Yes == QMessageBox::question(this, "Closing Application?", "Are you sure you want to exit?", QMessageBox::Yes|QMessageBox::No))
        event->accept(); //close application
    else if(computerIsPlaying)
        computerTimer->start(); //continue computer playing
}

/* =====================================================================
 *                            HELPER FUNCTIONS
 * =====================================================================*/

//function to initialize appearance and setup timer
void GameOfPig::init()
{
    //setup computerTimer
    computerTimer = new QTimer(this);
    connect(computerTimer, SIGNAL(timeout()), this, SLOT(computerPlaying()));
    //initialize appearance
    this->setWindowTitle("Game Of Pig");
    displayPage(MAIN_MENU_PAGE_INDEX);

}

/* display log message on the UI
 *
 * TEXT_COLOR can be:
 *    RED_TEXT
 *    BLUE_TEXT
 */
void GameOfPig::printLogMessage(int TEXT_COLOR, QString text)
{
    switch(TEXT_COLOR)
    {
    case RED_TEXT:
        ui->LogMessage->setText("<font size=6 color=red>" + text + "</font>");
        break;
    case BLUE_TEXT:
        ui->LogMessage->setText("<font size=6 color=blue>" + text + "</font>");
        break;
    default:
        break;
    }
}

/* Clear the text on log message */
void GameOfPig::clearLogMessage()
{
    ui->LogMessage->setText("");
}

/* Function to display a specified page:
 *
 * PARAMS:
 *    Index - page to displayed
 */
void GameOfPig::displayPage(Page_Index index)
{
    qDebug() << "page index " << index;

    //go to desired page
    ui->stackedWidget->setCurrentIndex(index);

    //edit appearance and set computerIsPlaying bool to false
    switch(index)
    {
    case MAIN_MENU_PAGE_INDEX:
        //set computerIsPlaying bool to false
        computerIsPlaying = false;
        //edit page title and top buttons
        ui->PageTitle->setText("<font size=16 color=grey><b>MAIN MENU</b></font>");
        ui->TopMainMenuBt->setVisible(false);
        ui->TopQuitBt->setVisible(false);
        clearLogMessage();
        break;
    case ONE_PLAYER_PAGE_INDEX:
        //set computerIsPlaying bool to false
        computerIsPlaying = false;
        //edit page title and top buttons
        ui->PageTitle->setText("<font size=16 color=grey><b>ONE PLAYER MODE</b></font>");
        ui->TopMainMenuBt->setVisible(true);
        ui->TopQuitBt->setVisible(true);
        //edit versus label
        ui->OnePlayerVersusLabel->setText("<font size=12 color=red><b>VS</b></font>");
        //edit human labels
        ui->HumanPlayerLabel->setText("<font size=12 color=red><b>HUMAN</b></font>");
        ui->HumanRollingLabel->setText("<font size=12 color=grey><b>Rolling</b></font>");
        ui->HumanTurnTotalLabel->setText("<font size=12 color=grey><b>Turn Total</b></font>");
        ui->HumanTotalScoreLabel->setText("<font size=12 color=grey><b>Total Score</b></font>");
        //edit computer labels
        ui->ComputerPlayerLabel->setText("<font size=12 color=red><b>COMPUTER</b></font>");
        ui->ComputerRollingLabel->setText("<font size=12 color=grey><b>Rolling</b></font>");
        ui->ComputerTurnTotalLabel->setText("<font size=12 color=grey><b>Turn Total</b></font>");
        ui->ComputerTotalScoreLabel->setText("<font size=12 color=grey><b>Total Score</b></font>");
        //edit human LCD appearance
        ui->HumanRollingLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->HumanTurnTotalLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->HumanTotalScoreLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->HumanRollingLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->HumanTurnTotalLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->HumanTotalScoreLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        //edit computer LCD appearance
        ui->ComputerRollingLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->ComputerTurnTotalLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->ComputerTotalScoreLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->ComputerRollingLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->ComputerTurnTotalLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->ComputerTotalScoreLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        break;
    case TWO_PLAYER_PAGE_INDEX:
        //set computerIsPlaying bool to false
        computerIsPlaying = false;
        //edit page title and top buttons
        ui->PageTitle->setText("<font size=16 color=grey><b>TWO PLAYER MODE</b></font>");
        ui->TopMainMenuBt->setVisible(true);
        ui->TopQuitBt->setVisible(true);
        //edit P1 labels
        ui->Player1Label->setText("<font size=12 color=red><b>PLAYER 1</b></font>");
        ui->Player1RollingLabel->setText("<font size=12 color=grey><b>Rolling</b></font>");
        ui->Player1TurnTotalLabel->setText("<font size=12 color=grey><b>Turn Total</b></font>");
        ui->Player1TotalScoreLabel->setText("<font size=12 color=grey><b>Total Score</b></font>");
        //edit P2 labels
        ui->Player2Label->setText("<font size=12 color=red><b>PLAYER 2</b></font>");
        ui->Player2RollingLabel->setText("<font size=12 color=grey><b>Rolling</b></font>");
        ui->Player2TurnTotalLabel->setText("<font size=12 color=grey><b>Turn Total</b></font>");
        ui->Player2TotalScoreLabel->setText("<font size=12 color=grey><b>Total Score</b></font>");
        //edit P1 LCD appearance
        ui->Player1RollingLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->Player1TurnTotalLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->Player1TotalScoreLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->Player1RollingLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->Player1TurnTotalLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->Player1TotalScoreLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        //edit P2 LCD appearance
        ui->Player2RollingLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->Player2TurnTotalLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->Player2TotalScoreLCD->setSegmentStyle(QLCDNumber::Flat);
        ui->Player2RollingLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->Player2TurnTotalLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        ui->Player2TotalScoreLCD->setStyleSheet("QLCDNumber{ color: rgb(255,0,0); background-color: rgb(0,0,0); }");
        break;
    }
}

//disable and enable buttons depending on whose turn (1-player mode)
void GameOfPig::onePlayerTextButtonCtrl()
{
    qDebug() << "numOfTurns" << gameLogic.getNumOfTurns();

    if(gameLogic.getWhoseTurn()==PLAYER_ONE_TURN)
    {
        //set labels
        ui->OnePlayerWhoseTurnLabel->setText("<font size=13 color=red><b>Human's Turn</b></font>");
        ui->ComputerThinkingLabel->setText("<font size=6 color=blue>Computer is waiting...</font>");
        //human buttons
        ui->HumanRollBt->setEnabled(true);
        ui->HumanHoldBt->setEnabled(true);
        //computer stops playing...
        computerTimer->stop();
        computerTimerInt = 0;
        computerIsPlaying = false;

    }
    if(gameLogic.getWhoseTurn()==PLAYER_TWO_TURN)
    {
        //set labels
        ui->OnePlayerWhoseTurnLabel->setText("<font size=13 color=red><b>Computer's Turn</b></font>");
        ui->ComputerThinkingLabel->setText("<font size=7 color=red>Computer is thinking...</font>");
        //human buttons
        ui->HumanRollBt->setEnabled(false);
        ui->HumanHoldBt->setEnabled(false);
        //computer plays...
        computerIsPlaying = true;
        computerTimer->start();
    }
}

//initialize LCD numbers (1-player mode)
void GameOfPig::onePlayerInitNumbers()
{
    //human LCD numbers
    ui->HumanRollingLCD->display(0);
    ui->HumanTurnTotalLCD->display(0);
    ui->HumanTotalScoreLCD->display(0);
    //computer LCD numbers
    ui->ComputerRollingLCD->display(0);
    ui->ComputerTurnTotalLCD->display(0);
    ui->ComputerTotalScoreLCD->display(0);
}

//disable and enable buttons depending on whose turn (2-player mode)
void GameOfPig::twoPlayerTextButtonCtrl()
{
    qDebug()<<"numOfTurns"<<gameLogic.getNumOfTurns();

    if(gameLogic.getWhoseTurn()==PLAYER_ONE_TURN)
    {
        //set WhoseTurnLabel
        ui->TwoPlayerWhoseTurnLabel->setText("<font size=13 color=red><b>P1 Turn</b></font>");
        //P1 buttons
        ui->Player1RollBt->setEnabled(true);
        ui->Player1HoldBt->setEnabled(true);
        //P2 buttons
        ui->Player2RollBt->setEnabled(false);
        ui->Player2HoldBt->setEnabled(false);
    }
    if(gameLogic.getWhoseTurn()==PLAYER_TWO_TURN)
    {
        //set WhoseTurnLabel
        ui->TwoPlayerWhoseTurnLabel->setText("<font size=13 color=red><b>P2 Turn</b></font>");
        //P1 buttons
        ui->Player1RollBt->setEnabled(false);
        ui->Player1HoldBt->setEnabled(false);
        //P2 buttons
        ui->Player2RollBt->setEnabled(true);
        ui->Player2HoldBt->setEnabled(true);
    }
}

//initialize LCD numbers (2-player mode)
void GameOfPig::twoPlayerInitNumbers()
{
    //P1 LCD numbers
    ui->Player1RollingLCD->display(0);
    ui->Player1TurnTotalLCD->display(0);
    ui->Player1TotalScoreLCD->display(0);
    //P2 LCD numbers
    ui->Player2RollingLCD->display(0);
    ui->Player2TurnTotalLCD->display(0);
    ui->Player2TotalScoreLCD->display(0);
}

//display game over message box
void GameOfPig::gameOver(int currentMode, QString winner)
{
    QMessageBox msgBox(QMessageBox::Question,
                       QString(winner + " wins!"),
                       QString(winner + " reaches 100 or more points after " + QString::number(gameLogic.getNumOfTurns()) + " turns!"),
                       QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, "Restart Game");
    msgBox.setButtonText(QMessageBox::No, "Return to Main Menu");

    if (msgBox.exec() == QMessageBox::Yes)
    {
        gameLogic.init();
        if(currentMode == ONE_PLAYER_MODE)
        {
            onePlayerTextButtonCtrl();
            onePlayerInitNumbers();
        }
        else if(currentMode == TWO_PLAYER_MODE)
        {
            twoPlayerTextButtonCtrl();
            twoPlayerInitNumbers();
        }

    }
    else
        displayPage(MAIN_MENU_PAGE_INDEX);
}

void GameOfPig::rollAnimation()
{
//    if(currentMode == TWO_PLAYER_MODE &&
//       currentTurn == PLAYER_ONE_TURN)
//    {
        for(int i=0; i<10000; i++)
            for(int j=1; j<=6; j++)
            {
                ui->Player1RollingLCD->display(j);
                QThread::msleep(300);
            }
//    }
}

/* =====================================================================
 *                          TOP BUTTONS CONTROLS
 * =====================================================================*/

void GameOfPig::on_TopMainMenuBt_clicked()
{
    //pause computer playing
    if(computerIsPlaying)
        computerTimer->stop();

    //asks user confirmation
    if(QMessageBox::Yes == QMessageBox::question(this, "Exiting Current Game", "Are you sure you want to return to the main menu?", QMessageBox::Yes|QMessageBox::No))
        displayPage(MAIN_MENU_PAGE_INDEX);
    else if(computerIsPlaying)
        computerTimer->start(); //continue computer playing
}

/* =====================================================================
 *                       MAIN MENU BUTTON CONTROLS
 * =====================================================================*/

void GameOfPig::on_OnePlayerModeBt_clicked()
{
    //go to one player page
    displayPage(ONE_PLAYER_PAGE_INDEX);

    //initialize gameLogic object and appearance
    gameLogic.init();
    onePlayerTextButtonCtrl();
    onePlayerInitNumbers();
}

void GameOfPig::on_TwoPlayerModeBt_clicked()
{
    //go to two player page
    displayPage(TWO_PLAYER_PAGE_INDEX);

    //initialize gameLogic object and appearance
    gameLogic.init();
    twoPlayerTextButtonCtrl();
    twoPlayerInitNumbers();
}

/* =====================================================================
 *                      1-PLAYER MODE BUTTON CONTROLS
 * =====================================================================*/

/*****************************Human Controls*****************************/

void GameOfPig::on_HumanRollBt_clicked()
{
    //roll dice and check if its one
    if(gameLogic.P1roll() == PLAYER_ROLL_ONE)
    {
        //temporarily set rolling LCD number
        ui->HumanRollingLCD->display(1);

        //create message box
        QMessageBox::critical(this, "Oops!", QString("Human rolled a 1! No score for this turn!"));

        //set LCD numbers
        ui->HumanRollingLCD->display(gameLogic.getRolling());
        ui->HumanTurnTotalLCD->display(0);
        ui->HumanTotalScoreLCD->display(gameLogic.getP1totalScore());

        //buttons and texts controls and print log message
        onePlayerTextButtonCtrl();
        printLogMessage(RED_TEXT, QString("Human rolled a 1! No score for this turn!"));

        return;
    }

    //set LCD numbers
    ui->HumanRollingLCD->display(gameLogic.getRolling());
    ui->HumanTurnTotalLCD->display(gameLogic.getTurnTotal());
    ui->HumanTotalScoreLCD->display(gameLogic.getP1totalScore());

    //print log message
    printLogMessage(BLUE_TEXT, QString("Human rolled a " + QString::number(gameLogic.getRolling()) + "!"));
}

void GameOfPig::on_HumanHoldBt_clicked()
{
    //in case user press hold accidentally
    if(gameLogic.getTurnTotal() == 0)
    {
        if(QMessageBox::No == QMessageBox::question(this, "Holding without rolling", "Are you sure you want to hold without rolling?", QMessageBox::Yes|QMessageBox::No))
        {
            return;
        }
    }

    //hold
    gameLogic.P1hold();

    //set LCD numbers
    ui->HumanRollingLCD->display(gameLogic.getRolling());
    ui->HumanTurnTotalLCD->display(0);
    ui->HumanTotalScoreLCD->display(gameLogic.getP1totalScore());

    //buttons and texts controls and print log message
    onePlayerTextButtonCtrl();
    printLogMessage(BLUE_TEXT, QString("Human held!"));

    //check if Human win
    if(gameLogic.getP1totalScore() >= 100)
    {
        computerTimer->stop();
        gameOver(ONE_PLAYER_MODE,"Human");
    }
}

/*****************************Computer Controls*****************************/



/* =====================================================================
 *                      2-PLAYER MODE BUTTON CONTROLS
 * =====================================================================*/

/*****************************Player 1 Controls*****************************/

void GameOfPig::on_Player1RollBt_clicked()
{
    //roll dice and check if its one
    if(gameLogic.P1roll() == PLAYER_ROLL_ONE)
    {
        //temporarily set rolling LCD number
        ui->Player1RollingLCD->display(1);

        //create message box
        QMessageBox::critical(this, "Oops!", QString("P1 rolled a 1! No score for this turn!"));

        //set LCD numbers
        ui->Player1RollingLCD->display(gameLogic.getRolling());
        ui->Player1TurnTotalLCD->display(0);
        ui->Player1TotalScoreLCD->display(gameLogic.getP1totalScore());

        //buttons and texts controls and print log message
        twoPlayerTextButtonCtrl();
        printLogMessage(RED_TEXT, QString("P1 rolled a 1! No score for this turn!"));

        return;
    }

    //set LCD numbers
    ui->Player1RollingLCD->display(gameLogic.getRolling());
    ui->Player1TurnTotalLCD->display(gameLogic.getTurnTotal());
    ui->Player1TotalScoreLCD->display(gameLogic.getP1totalScore());

    //print log message
    printLogMessage(BLUE_TEXT, QString("P1 rolled a " + QString::number(gameLogic.getRolling()) + "!"));
}

void GameOfPig::on_Player1HoldBt_clicked()
{
    //in case user press hold accidentally
    if(gameLogic.getTurnTotal() == 0)
    {
        if(QMessageBox::No == QMessageBox::question(this, "Holding without rolling", "Are you sure you want to hold without rolling?", QMessageBox::Yes|QMessageBox::No))
        {
            return;
        }
    }

    //hold
    gameLogic.P1hold();

    //set LCD numbers
    ui->Player1RollingLCD->display(gameLogic.getRolling());
    ui->Player1TurnTotalLCD->display(0);
    ui->Player1TotalScoreLCD->display(gameLogic.getP1totalScore());

    //buttons and texts controls and print log message
    twoPlayerTextButtonCtrl();
    printLogMessage(BLUE_TEXT, QString("P1 held!"));

    //check if P1 win
    if(gameLogic.getP1totalScore() >= 100)
    {
        //QMessageBox::information(this, "P1 wins!", QString("P1 reaches 100 or more points after " + QString::number(gameLogic.getNumOfTurns()) + " turns!"));
        gameOver(TWO_PLAYER_MODE,"P1");
    }
}

/*****************************Player 2 Controls*****************************/

void GameOfPig::on_Player2RollBt_clicked()
{
    //roll dice and check if its one
    if(gameLogic.P2roll() == PLAYER_ROLL_ONE)
    {
        //temporarily set rolling LCD number
        ui->Player2RollingLCD->display(1);

        //create message box
        QMessageBox::critical(this, "Oops!", QString("P2 rolled a 1! No score for this turn!"));

        //set LCD numbers
        ui->Player2RollingLCD->display(gameLogic.getRolling());
        ui->Player2TurnTotalLCD->display(0);
        ui->Player2TotalScoreLCD->display(gameLogic.getP2totalScore());

        //buttons and texts controls and print log message
        twoPlayerTextButtonCtrl();
        printLogMessage(RED_TEXT, QString("P2 rolled a 1! No score for this turn!"));

        return;
    }

    //set LCD numbers
    ui->Player2RollingLCD->display(gameLogic.getRolling());
    ui->Player2TurnTotalLCD->display(gameLogic.getTurnTotal());
    ui->Player2TotalScoreLCD->display(gameLogic.getP2totalScore());

    //print log message
    printLogMessage(BLUE_TEXT, QString("P2 rolled a " + QString::number(gameLogic.getRolling()) + "!"));
}

void GameOfPig::on_Player2HoldBt_clicked()
{
    //in case user press hold accidentally
    if(gameLogic.getTurnTotal() == 0)
    {
        if(QMessageBox::No == QMessageBox::question(this, "Holding without rolling", "Are you sure you want to hold without rolling?", QMessageBox::Yes|QMessageBox::No))
        {
            return;
        }
    }

    //hold
    gameLogic.P2hold();

    //set LCD numbers
    ui->Player2RollingLCD->display(gameLogic.getRolling());
    ui->Player2TurnTotalLCD->display(0);
    ui->Player2TotalScoreLCD->display(gameLogic.getP2totalScore());

    //buttons and texts controls and print log message
    twoPlayerTextButtonCtrl();
    printLogMessage(BLUE_TEXT, QString("P2 held!"));

    //check if P2 win
    if(gameLogic.getP2totalScore() >= 100)
    {
        //QMessageBox::information(this, "P2 wins!", QString("P2 reaches 100 or more points after " + QString::number(gameLogic.getNumOfTurns()) + " turns!"));
        gameOver(TWO_PLAYER_MODE,"P2");
    }
}

/* =====================================================================
 *                              CUSTOM SLOTS
 * =====================================================================*/

void GameOfPig::computerPlaying()
{
    computerTimerInt++;
    computerTimerInt = computerTimerInt % 1000000000;

    if(computerTimerInt%100000 == 0)
    {
        qDebug()<<"computerTimerInt:"<<computerTimerInt;

        //computer playing logic
        if( ( (gameLogic.getTurnTotal() < 20) && (gameLogic.getP2totalScore()+gameLogic.getTurnTotal() < 100) ) ||
            ( (gameLogic.getP2totalScore()+gameLogic.getTurnTotal() < 100) && (100-gameLogic.getP1totalScore() <= 10) )
          )
        {
            //roll dice and check if its one
            if(gameLogic.P2roll() == PLAYER_ROLL_ONE)
            {
                //set LCD numbers
                ui->ComputerRollingLCD->display(gameLogic.getRolling());
                ui->ComputerTurnTotalLCD->display(0);
                ui->ComputerTotalScoreLCD->display(gameLogic.getP2totalScore());

                //buttons and texts controls and print log message
                onePlayerTextButtonCtrl();
                printLogMessage(RED_TEXT, QString("Computer rolled a 1! No score for this turn!"));

                return;
            }

            //set LCD numbers
            ui->ComputerRollingLCD->display(gameLogic.getRolling());
            ui->ComputerTurnTotalLCD->display(gameLogic.getTurnTotal());
            ui->ComputerTotalScoreLCD->display(gameLogic.getP2totalScore());

            //print log message
            printLogMessage(BLUE_TEXT, QString("Computer rolled a " + QString::number(gameLogic.getRolling()) + "!"));
        }
        else
        {
            //hold
            gameLogic.P2hold();

            //set LCD numbers
            ui->ComputerRollingLCD->display(gameLogic.getRolling());
            ui->ComputerTurnTotalLCD->display(0);
            ui->ComputerTotalScoreLCD->display(gameLogic.getP2totalScore());

            //buttons and texts controls and print log message
            onePlayerTextButtonCtrl();
            printLogMessage(BLUE_TEXT, QString("Computer held!"));

            //check if Computer win
            if(gameLogic.getP2totalScore() >= 100)
            {
                gameOver(ONE_PLAYER_MODE,"Computer");
            }
        }
    }
}
