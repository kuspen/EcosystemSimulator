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

	int m_hp;
	const int m_max_hp = 255;

	int m_recovered_hp;
	int m_borned_hp;
	int m_stayed_hp;

public:
	CCharacter(int x, int y, ECharacterTypes type);
	virtual ~CCharacter();


	void setX(int x);
	void setY(int y);
	void setType(ECharacterTypes type);
	void setRoutine(CRoutine* routine);
	void setTargets(std::vector<ECharacterTypes> targets);
	void setHp(int hp);
	void setRecoveredHp(int hp);
	void setBornedHp(int hp);
	void setStayedHp(int hp);

	int getX();
	int getY();
	int getHp();

	ECharacterTypes getType();
	std::vector<ECharacterTypes> getTargets();

	void move();
	void exec();

	void recover();
	bool isBorn();
	bool isStay();

};
