//
//  main.cpp
//  es
//
//  Created by Kevin Giraldo on 5/29/15.
//  Copyright (c) 2015 Kevin Giraldo. All rights reserved.
//

#include <iostream>
#include "Game.h"

using namespace std;

int main()
{
    //creating an object a
    
    while (true)
    {
        Game a;
        a.ChooseMode();
        a.WhoGoFirst();
        a.display();       //display the board
        do
        {
            int move = a.getMove();      //ask for input
            a.go(move);                  //get the move on the board
            a.display();                 //display the result of the move
            if (a.checkwin()) break;     //if anybody win in this turn, game over
            a.switch_turn();
        }
        while( !a.isFull() );              //if the board is full, game ends.
        
        if ( a.isFull() )   cout << "Draw"<<endl;
        else cout << "Player " << a.GetTurn() <<" is winner\n"<<endl;
        
        do
        {
            char option;
            cout << "Play it again?(Y/N): ";
            cin >> option;
            if (option=='Y'||option=='y')
            {
                cout << endl;
                //
                break;   //jump out of this loop and come back to the outer loop
            }
            else if (option=='N'||option=='n') return 0;    //end up the whole program
            else cout << "Invalid input!\n" <<endl;
        }
        while(true);
    }
    return 0;
}