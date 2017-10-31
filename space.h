/********************
	Kaylee Poole
	4/10/17
	Header file for Space class which defines all possible spaces on a checkers board.
*********************/
#ifndef SPACE_H
#define SPACE_H

namespace main_savitch_14{
class Space{
	public:
		Space(); //default constructor
		bool is_empty()const; //checks to see if space is empty
		bool is_playable()const; //checks to see if space is playable/non-playable
		bool is_blue()const; //checks to see if piece is a blue piece
		bool is_red()const; //checks to see if piece is a red piece
		bool is_bking()const; //checks to see if piece is a blue king
		bool is_rking()const; //checks to see if piece is a red king
		void make_bking(); //makes a normal piece into a blue king
		void make_rking(); //makes a normal piece into a red king
		char get_piece()const; //returns piece
		void set_nonplayable(); //sets the space to playable
		void set_red(); //sets piece to red
		void set_blue(); //sets piece to blue
		void make_empty(); //makes the space empty

	private:
		char piece;
		bool playable;
		
};
}

#endif 

