/********************
	Kaylee Poole
	4/10/17
	Implementation of space.h
*********************/

#include"space.h"
using namespace std;
using namespace main_savitch_14;

Space::Space() //default constructor
{
	piece=' ';
	playable=true;
}
bool Space::is_empty()const //checks to see if space is empty
{
	return piece==' ';
}

bool Space::is_playable()const //checks to see if space is playable/non-playable
{
	return playable==true;
}

bool Space::is_blue()const //checks to see if its a blue piece
{
	return piece=='b' || piece=='B';
}

bool Space::is_red()const //checks to see if is its a red piece
{
	return piece=='r' || piece=='R';
}
bool Space::is_bking()const //checks to see if piece is a blue king
{
	return piece=='B';
}

bool Space::is_rking()const //checks to see if piece is a red king
{
	return piece=='R';
}
void Space::make_rking() //makes a normal piece into a red king
{
	piece='R';
}

void Space::make_bking() //makes a normal piece into a blue king
{
	piece='B';
}

char Space::get_piece()const //returns piece
{
	return piece; 
}

void Space::set_nonplayable() //sets the space to nonplayable
{
	playable=false;
}

void Space::set_red() //sets piece to red
{
	piece='r';
}

void Space::set_blue() //sets piece to black
{
	piece='b';
}

void Space::make_empty() //makes the space empty
{
	piece=' ';
}
