//
//  Game.h
//  es
//
//  Created by Kevin Giraldo on 5/29/15.
//  Copyright (c) 2015 Kevin Giraldo. All rights reserved.
//

#ifndef __es__Game__
#define __es__Game__

#include <stdio.h>

class Game
{
private:
    const char X = 'X';
    const char O = 'O';
    
    
public:
    char square[9] = {'1','2','3','4','5','6','7','8','9'};
    int Mode;
    int ChooseWhoBeX;
    int turn;
    int input;
    char mark;
    void reset();
    void display();
    void WhoGoFirst();
    int getMove();
    bool checkwin();
    bool isFull();
    void switch_turn();
    void go(int);
    char GetTurn();
    bool isFree(int);
    void ChooseMode();
    
    /////////////////////////////////////////////////
    ////////////Computer AI//////////////////////////
    /////////////////////////////////////////////////
    int m;
    int step = 1;
    int level;
    int getMoveByAI();
    int EmptyCorner();
    int make2inRow();
    int possWin();
    int getAnyFreeSpace();
};


#endif /* defined(__es__Game__) */
