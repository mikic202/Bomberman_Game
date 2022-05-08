#ifndef VersusModeBoard_H
#define VersusModeBoard_H
#include "GameBoard.h"

class VersusModeBoard : GameBoard
{
private:
	int size_;
public:
	VersusModeBoard(int size);
	int size();
};


#endif // !VersusModeBoard_H

