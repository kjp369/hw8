/********************
	Kaylee Poole
	4/10/17
	Header file for checkers class that is derived from the game class 
*********************/

#ifndef CHECKERS_H
#define CHECKERS_H

#include"space.h"
#include"game.h"

namespace main_savitch_14{
class Checkers:public game{
	public:
		Checkers();
		void make_move(const std::string& move);
		void restart();
		void display_status()const;
		bool is_legal(const std::string& move)const;
		bool is_game_over( )const;
		game* clone( )const;
		void compute_moves(std::queue<std::string>& moves)const;
		int evaluate( )const;
		who winning( )const;
		bool is_jump_possible(int& row2, int& col2, int f_row, int f_col, int& jump_counter, bool moved)const; // checks to see if a jump is possible
		bool inbounds(int row, int col)const; //checks to see if row and col are within bounds
		bool check_multi_jumps(int row, int col)const; //checks to see of player has a choice between jumps
		void force_jump(int row, int col, int& n_row, int& n_col); //part of the jump process
		bool check_piece(const std::string& move2)const; // checks to see if it is legal to move a certain piece when jumping
		bool check_space(const std::string& move2)const; //checks to see if it is legal to move to a certain space when jumping

	private:
		Space board[8][8];
};
}

#endif
