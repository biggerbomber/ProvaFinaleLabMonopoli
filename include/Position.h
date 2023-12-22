#ifndef POSITION_H
#define POSITION_H
#include <iostream>
//@Pinton Mattia
class Position {
public:
	Position(int pos) : m_position{ pos }{};
	int get_value() { return m_position; };
private:
	int m_position{ 0 };
};

std::ostream& operator<<(std::ostream& os, Position pos);
#endif
