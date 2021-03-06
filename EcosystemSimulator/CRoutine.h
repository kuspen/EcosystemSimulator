#pragma once
#include "CMap.h"
#include "CCharacter.h"

class CMap;
class CCharacter;

class CRoutine {

protected:

	CMap* m_map;
	
	int m_next_x;
	int m_next_y;


public:
	CRoutine(CMap* map);
	virtual ~CRoutine();

	void setNextX(int x);
	void setNextY(int y);
	int getNextX();
	int getNextY();

	virtual void move(CCharacter *character) = 0;
	virtual void exec(CCharacter *character) = 0;

};
