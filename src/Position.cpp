//@Pinton Mattia

//############### INCLUDES ###############
#include "Position.h"
#include "Board.h"
#include <string.h>

std::ostream& operator<<(std::ostream& os,const Position& pos)
{
	const int line_size = (Board::BOARD_SIZE / 4)+1; // 8
	const int column_size = (Board::BOARD_SIZE / 4)-1; // 6
	std::string outp = "";
	if (pos.get_valore() < line_size) { // 0 - 7
		outp += "H";
		outp += static_cast<char>('0'+(8 - pos.get_valore()));
	}
	else if (pos.get_valore() < line_size + column_size) { // 8 - 13
		int temp_val = pos.get_valore() - line_size; // 0 - 7
		outp += static_cast<char>('G' - temp_val);
		outp += "1";
	}
	else if (pos.get_valore() < line_size*2 + column_size) {  //16 - 21
		int temp_val = pos.get_valore() - (line_size + column_size); // 0 - 7
		outp += "A";
		outp += static_cast<char>('0' + temp_val + 1);
	}
	else // 21 - 28
	{
		int temp_val = pos.get_valore() - (2*line_size + column_size);; // 0 - 7
		outp += static_cast<char>('B' + temp_val);
		outp += "8";
	}
	return os << outp;
}