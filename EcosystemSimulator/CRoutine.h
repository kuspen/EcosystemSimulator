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

	int getNextX();
	int getNextY();

	virtual void run(CCharacter *character) = 0;

};
