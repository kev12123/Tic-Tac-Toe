//
//  Game.cpp
//  es
//
//  Created by Kevin Giraldo on 5/29/15.
//  Copyright (c) 2015 Kevin Giraldo. All rights reserved.
//

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void Game::ChooseMode()
{
    cout << "1: To play with person\n"
    << "2: To play with computer\n"
    << "Please choose a mode to play: ";
    cin >> Mode;
    
    if (Mode==2)
    {
        cout << "\n1: normal\n"
        << "2: advanced\n"
        << "Select a level of the computer: ";
        
        cin >> level;
    }
    
    if (Mode!=1 && Mode!=2)
    {
        cout << "Invalid input! Try again" <<"\n\n";
        ChooseMode();
    }
}


void Game::display()
{
    cout << endl;
    
    if (Mode==1)
        cout << "Player 1 = X    Player 2 = O" << "\n\n" ;
    
    else if (Mode==2)
    {
        if (ChooseWhoBeX==1)
            cout << "Player = X    Computer = O" << "\n\n" ;
        
        else if (ChooseWhoBeX==2)
            cout << "Computer = X    Player = O" << "\n\n";
    }
    
    cout << "     |     |     " << endl;
    cout << "  " << square[0] << "  |  " << square[1] << "  |  " << square[2] << endl;
    
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    
    cout << "  " << square[3] << "  |  " << square[4] << "  |  " << square[5] << endl;
    
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    
    cout << "  " << square[6] << "  |  " << square[7] << "  |  " << square[8] << endl;
    
    cout << "     |     |     " << "\n" << endl;
}


void Game::WhoGoFirst()
{
    if (Mode==1) turn = 1;
    
    else if (Mode==2)                               //play with computer
    {
        cout << "\n1: You go first as player X\n"
        << "2: Computer go first as player X\n"
        << "Please make you choice: ";
        cin >> ChooseWhoBeX;
        
        while (ChooseWhoBeX!=1 && ChooseWhoBeX!=2)
        {
            cout << "Invalid input! Try again" <<"\n\n";
            WhoGoFirst();
        }
        turn = 1;
    }
    
    else WhoGoFirst();                         //If any input number is invalid, ask user to input again.
}


void Game::switch_turn()
{
    turn++;
}


char Game::GetTurn()
{
    if (turn%2==1) return X;
    else return O;
}


int Game::getMove()
{
    mark = GetTurn();
    
    if (Mode==1)       //Play with another people
    {
        if (mark==X)
        {
            cout<<"Player 1, enter your position for X: ";
            cin >> input;
            cout << endl;
            return input;
        }
        
        else if(mark==O)
        {
            cout<<"Player 2, enter your position for O: ";
            cin>>input;
            cout<<endl;
            return input;
        }
    }
    
    if (Mode==2)  //play with computer
    {
        if (ChooseWhoBeX==1)       //you go first as X
        {
            if (mark==X)
            {
                cout << "It's your turn. Enter your position for X: ";
                cin >> input;
                cout << endl;
                return input;
            }
            else if (mark==O)
            {
                cout << "It's the computer's turn. She is making her move...\n" <<endl;
                input =getMoveByAI();
                return input;
            }
        }
        
        if (ChooseWhoBeX==2)      //the computer go first as X
        {
            if (mark==X)
            {
                cout << "It's the computer's turn. She is making her move...";
                input =getMoveByAI();
                cout << endl;
                return input;
            }
            else if (mark==O)
            {
                cout << "It's your turn. Enter your position for O: ";
                cin >> input;
                cout << endl;
                return input;
            }
        }
    }
    
    return 0;

}


void Game::go(int input)
{
    if (isFree(input))
        square[input-1] = mark;
    else
    {
        cout<<"Invalid move! Try again!\n"<<endl;
        turn--;
        cin.ignore();
    }
}



bool Game::checkwin()
{
    if (   (square[0] == square[1] && square[1] == square[2])
        || (square[0] == square[3] && square[3] == square[6])
        || (square[0] == square[4] && square[4] == square[8])
        
        || (square[1] == square[4] && square[4] == square[7])
        
        || (square[2] == square[5] && square[5] == square[8])
        || (square[2] == square[4] && square[4] == square[6])
        
        || (square[3] == square[4] && square[4] == square[5])
        
        || (square[6] == square[7] && square[7] == square[8])
        )
        return true;
    
    else return false;
}


bool Game::isFull()
{
    for (int i=1;i<=9;i++)
    {
        if (isFree(i))  return false;  // When a location is still empty, return false
    }
    if (checkwin())  return false;   //When the board is full but somebody win in the last step,
    //it also return false for outputting the result
    else return true;
}


int Game::getMoveByAI()
{
    switch(level)
    {
        case 1:
            do
            {
                srand ((int)time(NULL));
                m= rand()%9+1 ; // random move
            }
            while ( !isFree(m) );
            break;
            
        case 2:
            switch (step)
        {
            case 1:
                if (ChooseWhoBeX==1)
                {
                    if (isFree(5))
                    {
                        m=5;
                        step++;
                        break;
                    }
                }
                else if (ChooseWhoBeX==2)
                {
                    m=EmptyCorner();
                    step++;
                    break;
                }
                
            case 2:
            case 3:
            case 4:
            case 5:
                if (possWin()!=-1)
                {
                    m = possWin();
                }
                else m=make2inRow();
                step++;
                break;
        }
    }
    return m;
}

int Game::EmptyCorner()
{
    if (isFree(1)) return 1;
    if (isFree(3)) return 3;
    if (isFree(7)) return 7;
    if (isFree(9)) return 9;
    else return -1;
}

int Game::make2inRow()
{
    if (square[0]==mark && isFree(2) && isFree(3))  return 3;
    if (square[0]==mark && isFree(4) && isFree(7))  return 7;
    if (square[0]==mark && isFree(5) && isFree(9))  return 9;
    
    if (square[1]==mark && isFree(5) && isFree(8))  return 5;
    
    if (square[2]==mark && isFree(6) && isFree(8))  return 8;
    if (square[2]==mark && isFree(5) && isFree(7))  return 7;
    
    if (square[3]==mark && isFree(5) && isFree(6))  return 5;
    
    if (square[6]==mark && isFree(8) && isFree(9))  return 9;
    
    else return getAnyFreeSpace();  //if there is no more move can make 2 in a row
}

bool Game::isFree(int input)
{
    if (square[input-1] == (char)(input+48))    //Compare the value of input with the corresponding element in the array
        return true;                    //by converting the input from the int type to the char type.
    //48 is the number of '0' in the ASCII.
    else return false;
}


int Game::getAnyFreeSpace()
{    for (int i=1;i<=9;i++)
    {
        if (isFree(i)) return i;
    }
    
    return 0;
}


int Game::possWin()
{
    
    ///////////////////////////////////////////////////////////////////////////////////////
    //////////////////check the situation of the computer itself first/////////////////////
    
    if (square[0] == square[1] && square[1]==mark && isFree(3)) return 3;
    if (square[0] == square[2] && square[2]==mark && isFree(2)) return 2;
    if (square[1] == square[2] && square[2]==mark && isFree(1)) return 1;
    
    
    if (square[0] == square[3] && square[3]==mark && isFree(7)) return 7;
    if (square[0] == square[6] && square[6]==mark && isFree(4)) return 4;
    if (square[3] == square[6] && square[6]==mark && isFree(1)) return 1;
    
    if (square[0] == square[4] && square[4]==mark && isFree(9)) return 9;
    if (square[0] == square[8] && square[8]==mark && isFree(5)) return 5;
    if (square[4] == square[8] && square[8]==mark && isFree(1)) return 1;
    
    if (square[1] == square[4] && square[4]==mark && isFree(8)) return 8;
    if (square[1] == square[7] && square[7]==mark && isFree(5)) return 5;
    if (square[4] == square[7] && square[7]==mark && isFree(2)) return 2;
    
    if (square[2] == square[5] && square[5]==mark && isFree(9)) return 9;
    if (square[2] == square[8] && square[8]==mark && isFree(6)) return 6;
    if (square[5] == square[8] && square[8]==mark && isFree(3)) return 3;
    
    if (square[2] == square[4] && square[4]==mark && isFree(7)) return 7;
    if (square[2] == square[6] && square[6]==mark && isFree(5)) return 5;
    if (square[4] == square[6] && square[6]==mark && isFree(3)) return 3;
    
    if (square[3] == square[4] && square[4]==mark && isFree(6)) return 6;
    if (square[3] == square[5] && square[5]==mark && isFree(5)) return 5;
    if (square[4] == square[5] && square[5]==mark && isFree(4)) return 4;
    
    if (square[6] == square[7] && square[7]==mark && isFree(9)) return 9;
    if (square[6] == square[8] && square[8]==mark && isFree(8)) return 8;
    if (square[7] == square[8] && square[8]==mark && isFree(7)) return 7;
    
    /////////////////////////////////////////////////////////////////////////////
    //////////////////then check the situation of the player/////////////////////
    
    if (square[0] == square[1] && isFree(3)) return 3;
    if (square[0] == square[2] && isFree(2)) return 2;
    if (square[1] == square[2] && isFree(1)) return 1;
    
    
    if (square[0] == square[3] && isFree(7)) return 7;
    if (square[0] == square[6] && isFree(4)) return 4;
    if (square[3] == square[6] && isFree(1)) return 1;
    
    if (square[0] == square[4] && isFree(9)) return 9;
    if (square[0] == square[8] && isFree(5)) return 5;
    if (square[4] == square[8] && isFree(1)) return 1;
    
    if (square[1] == square[4] && isFree(8)) return 8;
    if (square[1] == square[7] && isFree(5)) return 5;
    if (square[4] == square[7] && isFree(2)) return 2;
    
    if (square[2] == square[5] && isFree(9)) return 9;
    if (square[2] == square[8] && isFree(6)) return 6;
    if (square[5] == square[8] && isFree(3)) return 3;
    
    if (square[2] == square[4] && isFree(7)) return 7;
    if (square[2] == square[6] && isFree(5)) return 5;
    if (square[4] == square[6] && isFree(3)) return 3;
    
    if (square[3] == square[4] && isFree(6)) return 6;
    if (square[3] == square[5] && isFree(5)) return 5;
    if (square[4] == square[5] && isFree(4)) return 4;
    
    if (square[6] == square[7] && isFree(9)) return 9;
    if (square[6] == square[8] && isFree(8)) return 8;
    if (square[7] == square[8] && isFree(7)) return 7;
    
    else return -1;
}
