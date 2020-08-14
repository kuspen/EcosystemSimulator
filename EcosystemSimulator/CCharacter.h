#pragma once
#include "CRoutine.h"
#include <vector>

class CRoutine;

enum class ECharacterTypes {
	CTYPE_NULL,		// mapíTçıóp
	CTYPE_NONE,
	CTYPE_GRASS,
	CTYPE_HERBIVORE,
	CTYPE_CARNIVORE
};

class CCharacter {

protected:
	int m_x;
	int m_y;

	ECharacterTypes m_type;
	CRoutine* m_routine;

	std::vector<ECharacterTypes> m_targets;

public:
	CCharacter(int x, int y, ECharacterTypes type);
	virtual ~CCharacter();


	void setX(int x);
	void setY(int y);
	void setType(ECharacterTypes type);
	void setRoutine(CRoutine* routine);
	void setTargets(std::vector<ECharacterTypes> targets);

	int getX();
	int getY();

	ECharacterTypes getType();
	std::vector<ECharacterTypes> getTargets();

	void move();
	void exec();

};
