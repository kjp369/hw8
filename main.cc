/********************
	Kaylee Poole
	4/10/17
	Plays a game of checkers
*********************/

#include"game.h"
#include"space.h"
#include"checkers.h"
#include<iostream>
using namespace std;
using namespace main_savitch_14;

int main()
{
	Checkers x;
	Checkers::who winner;
	cout<<"To Play:Enter a string containing the location of the piece you wish to move and the location of the space you want to move to. If a jump is possible, that move will be made instead. \n";
	winner=x.play();
	if(winner==Checkers::HUMAN)
	{
		cout<<"You Win!\n";
	}
	else if(winner==Checkers::COMPUTER)
	{
		cout<<"Computer Wins!\n";
	}
	else
	{
		cout<<"Draw!\n";
	}
	return 0;
}
