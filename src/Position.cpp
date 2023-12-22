//############### INCLUDES ###############
#include "../include/Position.h"
#include <string.h>
#include "../include/Board.h"
std::ostream& operator<<(std::ostream& os,const Position& pos)
{
	std::string outp;
	if (pos.get_valore() < ) {
		outp = "H" + (8 - pos.get_valore());
	}
	else if (pos.get_valore() < 16) {
		int temp_val = pos.get_valore() - 8; // 0 - 7
		outp = static_cast<char>('H' - temp_val)+ "" + (temp_val + 1);
	}
	else if (pos.get_valore() < 24) {
		int temp_val = pos.get_valore() - 16; // 0 - 7
	}
	else
	{
		int temp_val = pos.get_valore() - 32; // 0 - 7
	}
}