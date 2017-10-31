/********************
	Kaylee Poole
	4/10/17
	Implementation of checkers.h
*********************/
#include"checkers.h"
#include"space.h"
#include"game.h"
#include"colors.h"
#include<iostream>
#include<string>
#include<cctype>
#include<queue>
using namespace std;
using namespace main_savitch_14;

Checkers::Checkers():game()
{
	restart();
}
void Checkers::restart()
{
	
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(((i%2)==0&&(j%2)==0)||((i%2==1)&&(j%2)==1))
			{
				board[i][j].set_nonplayable();
			}
		}
	}
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(((i%2)==1&&(j%2)==0)||((i%2)==0&&(j%2)==1))
			{
				board[i][j].set_red();
			}
		}
	}
	for(int i=7; i>4; i--)
	{
		for(int j=0; j<8; j++)
		{
			if(((i%2)==1&&(j%2)==0)||((i%2)==0&&(j%2)==1))
			{
				board[i][j].set_blue();
			}
		}
	}
	
	game::restart();
}
void Checkers::display_status()const
{
	for(char c='A'; c<='H'; c++)
	{
		cout<<BOLD<<"    "<<c<<"  "<<RESET;
	}
	cout<<endl;
	for(int i=0, k=1; i<8 && k<=8; i++, k++)
	{
		cout<<" ";
		for(int j=0; j<8; j++)
		{
			if((k%2==0 && j%2==0) || (k%2==1 && j%2==1))
			{
				cout<<B_WHITE<<"       "<<RESET;
			}
			else
			{
				cout<<B_CYAN<<"       "<<RESET;
			}
		}
		cout<<"\n"<<BOLD<<k<<RESET;

		for(int j=0; j<8; j++)
		{
			
			if(board[i][j].is_empty())
			{
				if(board[i][j].is_playable())
				{
					cout<<B_WHITE<<"       "<<RESET; 
				}
				else
				{
					cout<<B_CYAN<<"       "<<RESET;
				}			
			}
			else 
			{
				if(board[i][j].is_red())
				{
					cout<<B_WHITE<<RED<<"   "<<board[i][j].get_piece()<<"   "<<RESET;		
				}
				else if(board[i][j].is_blue())
				{
					cout<<B_WHITE<<BLUE<<"   "<<board[i][j].get_piece()<<"   "<<RESET;
				}
			}
		}
		cout<<endl;
		cout<<" ";
		for(int j=0; j<8; j++)
		{
			if((k%2==0 && j%2==0) || (k%2==1 && j%2==1))
			{
				cout<<B_WHITE<<"       "<<RESET;
			}
			else
			{
				cout<<B_CYAN<<"       "<<RESET;
			}
		}
		cout<<endl;
	}
	if(next_mover()==HUMAN)
	{
		display_message("Example input: A6B5\n");
	}
	else
	{
		display_message("Computer's Turn, Please Wait\n");
	}

}
bool Checkers::is_legal(const string& move)const
{
	int col, row, n_col, n_row, junk;	
	bool junk2=false;
	col=int(tolower(move[0])-'a');
	row=int(move[1]-'1');
	n_col=int(tolower(move[2])-'a');
	n_row=int(move[3]-'1');

	if(board[row][col].is_playable() && board[n_row][n_col].is_playable())
	{
		if(board[n_row][n_col].is_empty())
		{
			if(next_mover()==HUMAN && board[row][col].is_blue())
			{
				if(is_jump_possible(row, col, n_row, n_col, junk, junk2))
				{
					return true;
				}
				else if(board[row][col].is_bking())
				{
					return (((row==n_row+1 || row==n_row-1) && (col==n_col+1 || col==n_col-1) && inbounds(n_row, n_col)) || is_jump_possible(row, col, n_row, n_col, junk, junk2)); 
				}
				else
				{
					return row==n_row+1 && (col==n_col+1 || col==n_col-1) && inbounds(n_row, n_col); 
				}
			}
			else if(next_mover()==COMPUTER && board[row][col].is_red())
			{
				if(is_jump_possible(row, col, n_row, n_col, junk, junk2))
				{
					return true;
				}
				else if(board[row][col].is_rking())
				{
					return (((row==n_row+1 || row==n_row-1)&& (col==n_col+1 || col==n_col-1) && inbounds(n_row, n_col)) || is_jump_possible(row, col, n_row, n_col, junk, junk2)); 
				}
				else
				{
					return row==n_row-1 && (col==n_col+1 || col==n_col-1) && inbounds(n_row, n_col); 
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}	
}

void Checkers::make_move(const string& move)
{
	int col, row, n_col, n_row, f_col, f_row, jump_counter; //initial-next-final
	string move2;
	bool moved=false;
	bool stop=false;
	f_col=f_row=9;
	jump_counter=0;

	if(!is_jump_possible(row, col, f_row, f_col, jump_counter, moved))
	{
		col=int(tolower(move[0])-'a');
		row=int(move[1]-'1');
		f_col=int(tolower(move[2])-'a');
		f_row=int(move[3]-'1');
		
		if(board[row][col].is_blue())
		{
			if(f_row==0 || board[row][col].is_bking())
			{
				board[f_row][f_col].make_bking();
			}
			else
			{
				board[f_row][f_col].set_blue();
			}	
		}
		else
		{
			if(f_row==7|| board[row][col].is_rking())
			{
				board[f_row][f_col].make_rking();
			}
			else
			{
				board[f_row][f_col].set_red();
			}
		}

		board[row][col].make_empty();
	}
	else
	{
		while(is_jump_possible(row, col, f_row, f_col, jump_counter, moved))
		{
			if(move[4]!='#')
			{
				display_message("Jump Possible-Forcing Jump\n");
				if(jump_counter>1)
				{
					display_message("Multiple Jumps Possible-Enter the location of the piece you want to move: \n");
					getline(cin, move2);
					if(!check_piece(move2))
					{
						display_message("Illegal piece-Please enter a piece that can jump: ");
						getline(cin, move2);
					}
					col=int(tolower(move2[0])-'a');
					row=int(move2[1]-'1'); 
				}
				if(check_multi_jumps(row, col))
				{	
					display_message("2 Possible Jump Directions-Enter the location of the space you want to jump to (For jump chains, enter the first space in the sequence): \n");
					getline(cin, move2);
					if(!check_space(move2))
					{
						display_message("Illegal space-Please enter a space that can be jumped to: ");
						getline(cin, move2);
					}
					n_col=int(tolower(move2[0])-'a');
					n_row=int(move2[1]-'1'); 
				}
			}
		

			force_jump(row, col, n_row, n_col);
			board[(row+n_row)/2][(col+n_col)/2].make_empty();
			f_row=n_row;
			f_col=n_col;
		
			if(board[row][col].is_blue())
			{
				if(f_row==0 || board[row][col].is_bking())
				{
					board[f_row][f_col].make_bking();
					stop=true;
				}
				else
				{
					board[f_row][f_col].set_blue();
				}	
			}
			else
			{
				if(f_row==7 || board[row][col].is_rking())
				{
					board[f_row][f_col].make_rking();
				}
				else
				{
					board[f_row][f_col].set_red();
				}
			}
			board[row][col].make_empty();
			row=n_row;
			col=n_col;
			moved=true;
			if(stop)
			{
				break;
			}
		}
	}
	game::make_move(move);
}

bool Checkers::is_game_over( )const
{
	bool c_no_moves=false;
	bool h_no_moves=false;
	int h_piece, c_piece; 
	queue<string> moves;
	h_piece=c_piece=0;

	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			if(board[i][j].is_red())
			{
				++ c_piece;
			}
			else if(board[i][j].is_blue())
			{
				++ h_piece;
			}
		}
	}
	if(c_piece==0)
	{
		return true;
	}
	else if(h_piece==0)
	{
		return true;
	}
	
	if(next_mover()==HUMAN)
	{
		compute_moves(moves);
		if(moves.empty())
		{
			h_no_moves=true;
		}
	}
	else
	{
		compute_moves(moves);
		if(moves.empty())
		{
			c_no_moves=true;
		}
	}

	if(h_no_moves && c_no_moves)
	{
		return true;
	}
	else if(h_no_moves)
	{
		return true;
	}
	else if(c_no_moves)
	{
		return true;
	}
	
	return false;
	
}

bool Checkers::is_jump_possible(int& row2, int& col2, int f_row, int f_col, int& jump_counter, bool moved)const
{
	jump_counter=0;
	if(moved==false)
	{
		for(int row=0; row<8; row++)
		{
			for(int col=0; col<8; col++)
			{
				if(next_mover()==HUMAN && board[row][col].is_blue())
				{
					if (board[row][col].is_bking() && 
					  ((board[row-1][col+1].is_red() && board[row-2][col+2].is_empty() && inbounds(row-2, col+2)) ||
					   (board[row-1][col-1].is_red() && board[row-2][col-2].is_empty() && inbounds(row-2, col-2)) ||
					   (board[row+1][col+1].is_red() && board[row+2][col+2].is_empty() && inbounds(row+2, col+2)) ||
					   (board[row+1][col-1].is_red() && board[row+2][col-2].is_empty() && inbounds(row+2, col-2))))
					{
						++jump_counter;
						row2=row;
						col2=col;
					}
					else if((board[row-1][col+1].is_red() && board[row-2][col+2].is_empty() && inbounds(row-2, col+2)) || 
						   (board[row-1][col-1].is_red() && board[row-2][col-2].is_empty() && inbounds(row-2, col-2)))
					{
						++jump_counter;
						row2=row;
						col2=col;
					}
				}
				else if(next_mover()==COMPUTER && board[row][col].is_red())
				{
					if (board[row][col].is_rking() &&
					  ((board[row+1][col+1].is_blue() && board[row+2][col+2].is_empty() && inbounds(row+2, col+2)) || 
					   (board[row+1][col-1].is_blue() && board[row+2][col-2].is_empty() && inbounds(row+2, col-1)) ||
					   (board[row-1][col+1].is_blue() && board[row-2][col+2].is_empty() && inbounds(row-2, col+2)) ||
					   (board[row-1][col-1].is_blue() && board[row-2][col-2].is_empty() && inbounds(row-2, col-2))))
					{
						++jump_counter;
						row2=row;
						col2=col;
					}
					else if((board[row+1][col+1].is_blue() && board[row+2][col+2].is_empty() && inbounds(row+2, col+2)) || 
					  	   (board[row+1][col-1].is_blue() && board[row+2][col-2].is_empty() && inbounds(row+2, col-2)))
					{
						++jump_counter;
						row2=row;
						col2=col;
					}
				}
			}
		}
	}
	else
	{
		if(next_mover()==HUMAN && board[row2][col2].is_blue())
		{
			if ((board[row2][col2].is_bking() && 
			  ((board[row2-1][col2+1].is_red() && board[row2-2][col2+2].is_empty() && inbounds(row2-2, col2+2)) ||
			   (board[row2-1][col2-1].is_red() && board[row2-2][col2-2].is_empty() && inbounds(row2-2, col2-2)) ||
			   (board[row2+1][col2+1].is_red() && board[row2+2][col2+2].is_empty() && inbounds(row2+2, col2+2)) ||
			   (board[row2+1][col2-1].is_red() && board[row2+2][col2-2].is_empty() && inbounds(row2+2, col2-2))))||
			  ((board[row2-1][col2+1].is_red() && board[row2-2][col2+2].is_empty() && inbounds(row2-2, col2+2)) || 
			   (board[row2-1][col2-1].is_red() && board[row2-2][col2-2].is_empty() && inbounds(row2-2, col2-2))))
			{
				jump_counter=1;					
			}
		}
		else if(next_mover()==COMPUTER && board[row2][col2].is_red())
		{
			if ((board[row2][col2].is_rking() &&
			  ((board[row2+1][col2+1].is_blue() && board[row2+2][col2+2].is_empty() && inbounds(row2+2, col2+2)) || 
			   (board[row2+1][col2-1].is_blue() && board[row2+2][col2-2].is_empty() && inbounds(row2+2, col2-1)) ||
			   (board[row2-1][col2+1].is_blue() && board[row2-2][col2+2].is_empty() && inbounds(row2-2, col2+2)) ||
			   (board[row2-1][col2-1].is_blue() && board[row2-2][col2-2].is_empty() && inbounds(row2-2, col2-2))))||
			  ((board[row2+1][col2+1].is_blue() && board[row2+2][col2+2].is_empty() && inbounds(row2+2, col2+2)) || 
			   (board[row2+1][col2-1].is_blue() && board[row2+2][col2-2].is_empty() && inbounds(row2+2, col2-2))))
			{
				jump_counter=1;
			}
		}
	}
	return jump_counter>0;
	
}


bool Checkers::inbounds(int row, int col)const
{
	return row>=0 && row<=7 && col>=0 && col<=7;
}

bool Checkers::check_multi_jumps(int row, int col)const
{
	if(next_mover()==HUMAN)
	{
		return board[row-1][col+1].is_red() && board[row-1][col-1].is_red() && board[row-2][col+2].is_empty() && board[row-2][col-2].is_empty() && inbounds(row-2, col+2) && inbounds(row-2, col-2);
	}
	else
	{
		return board[row+1][col+1].is_blue() && board[row+1][col-1].is_blue() && board[row+2][col+2].is_empty() && board[row+2][col-2].is_empty() && inbounds(row+2, col+2) && inbounds(row+2, col-2);
	} 
}

void Checkers::force_jump(int row, int col, int& n_row, int& n_col)
{
	if(next_mover()==HUMAN)
	{
		if(board[row-1][col+1].is_red() && board[row-2][col+2].is_empty() && inbounds(row-2, col+2)) 
		{
			n_row=row-2;
			n_col=col+2;
			return;
		}
		else if(board[row-1][col-1].is_red() && board[row-2][col-2].is_empty() && inbounds(row-2, col-2))
		{
			n_row=row-2;
			n_col=col-2;
			return;
		}
		else if(board[row][col].is_bking() && board[row+1][col+1].is_red() && board[row+2][col+2].is_empty() && inbounds(row+2, col+2))
		{
			n_row=row+2;
			n_col=col+2;
			return;
		}
		else if(board[row][col].is_bking() && board[row+1][col-1].is_red() && board[row+2][col-2].is_empty() && inbounds(row+2, col-2))
		{
			n_row=row+2;
			n_col=col-2;
			return;
		}
	}
	else if (next_mover()==COMPUTER)
	{
		if(board[row+1][col+1].is_blue() && board[row+2][col+2].is_empty() && inbounds(row+2, col+2))   
		{
			n_row=row+2;
			n_col=col+2;
			return;
		}
		else if(board[row+1][col-1].is_blue() && board[row+2][col-2].is_empty() && inbounds(row+2, col-2))
		{
			n_row=row+2;
			n_col=col-2;
			return;
		}	
		else if(board[row][col].is_rking() && board[row-1][col+1].is_blue() && board[row-2][col+2].is_empty() && inbounds(row-2, col+2))
		{
			n_row=row-2;
			n_col=col+2;
			return;
		}	
		else if(board[row][col].is_rking() && board[row-1][col-1].is_blue() && board[row+2][col-2].is_empty() && inbounds(row+2, col-2))
		{
			n_row=row+2;
			n_col=col-2;
			return;
		}
	}
}

bool Checkers::check_piece(const string& move2)const
{
	int col, row;
	col=int(tolower(move2[0])-'a');
	row=int(move2[1]-'1');

	if(next_mover()==HUMAN && board[row][col].is_blue())
	{
		return (board[row-1][col+1].is_red() && board[row-2][col+2].is_empty() && inbounds(row-2, col+2)) || 
			  (board[row-1][col-1].is_red() && board[row-2][col-2].is_empty() && inbounds(row-2, col-2));
	}
	else if(next_mover()==COMPUTER && board[row][col].is_red())
	{
		return (board[row+1][col+1].is_blue() && board[row+2][col+2].is_empty() && inbounds(row+2, col+2)) || 
			  (board[row+1][col-1].is_blue() && board[row+2][col-2].is_empty() && inbounds(row+2, col-2));
	}
	else
	{
		return false;
	}
}

bool Checkers::check_space(const string& move2)const
{
	int col, row;
	col=int(tolower(move2[0])-'a');
	row=int(move2[1]-'1');

	if(next_mover()==HUMAN)
	{
		return board[row][col].is_empty() && (board[row+2][col-2].is_blue() ||
 			  board[row+2][col+2].is_blue()) && inbounds(row, col);
	}
	else
	{
		return board[row][col].is_empty() && (board[row-2][col-2].is_red() ||
			  board[row-2][col+2].is_red()) && inbounds(row, col);
	} 
}

game* Checkers::clone( )const
{
	return new Checkers(*this);
}

void Checkers::compute_moves(queue<string>& moves)const
{
	string move="     ";
	queue<string> tmp;
	char row, col, n_row, n_col;
	int i, j, i2, j2;
	int junk;
	bool junk2=false;
	for(row='1', i=0; row<='8' && i<8; row++, i++)
	{
		for(col='A', j=0; col<='H' && j<8; col++, j++)
		{
			for(n_row='1', i2=0; n_row<='8' && i2<8; n_row++, i2++)
			{
				for( n_col='A',  j2=0; n_col<='H' && j2<8; n_col++, j2++)
				{
					move[0]=col;
					move[1]=row;
					move[2]=n_col;
					move[3]=n_row;
					move[4]='#';
					if(is_legal(move))
					{
						if(is_jump_possible(i, j, i2, j2, junk, junk2))
						{
							tmp.push(move);
						}
						else
						{
							moves.push(move);
						}					
					}
				}
			}
		}
	}
	if(!tmp.empty())
	{
		moves=tmp;
	}
}


int Checkers::evaluate( )const
{
	//kings are worth 5 points-normal pieces are worth 1 point
	int h_total, c_total;
	queue<string> moves;
	h_total=c_total=0;
	for(int row=0; row<8; row++)
	{
		for(int col=0; col<8; col++)
		{
			if(board[row][col].is_red())
			{
				if(board[row][col].is_rking())
				{
					c_total+=5; 
				}
				else
				{
					++c_total;
				}
			}
			else if(board[row][col].is_blue())
			{
				if(board[row][col].is_bking())
				{
					h_total+=5;
				}
				else
				{
					++h_total;
				}
			}
		}
	}

	return c_total-h_total;
}

game::who Checkers::winning( )const
{
	queue<string> moves;
	int h_piece, c_piece; 
	bool c_no_moves=false;
	bool h_no_moves=false;
	h_piece=c_piece=0;
	for(int i=0; i<=7; i++)
	{
		for(int j=0; j<=7; j++)
		{
			if(board[i][j].is_red())
			{
				++ c_piece;
			}
			else if(board[i][j].is_blue())
			{
				++ h_piece;
			}
		}
	}

	if(next_mover()==HUMAN)
	{
		compute_moves(moves);
		if(moves.empty())
		{
			h_no_moves=true;
		}
	}
	else
	{
		compute_moves(moves);
		if(moves.empty())
		{
			c_no_moves=true;
		}
	}

	if(c_piece>h_piece || h_no_moves)
	{
		return COMPUTER;
	}
	else if(c_piece<h_piece || c_no_moves)
	{
		return HUMAN;
	}
	else if(c_piece==h_piece || (h_no_moves && c_no_moves))
	{
		return NEUTRAL;
	}
}
