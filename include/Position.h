#ifndef POSITION_H
#define POSITION_H
#include <iostream>
//@Pinton Mattia
class Position {
public:
	Position(int pos) : m_position{ pos }{};
	int get_valore() const{ return m_position; };
	void set_valore(int n) {
		m_position = n;
	};
private:
	int m_position{ 0 };
};

std::ostream& operator<<(std::ostream& os,const Position& pos);
#endif
