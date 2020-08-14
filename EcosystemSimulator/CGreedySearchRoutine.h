#pragma once
#include "CRoutine.h"

#include <vector>

class CGreedySearchRoutine : public CRoutine {

private:

	std::vector<ECharacterTypes> m_targetTypes;

public:

	CGreedySearchRoutine(CMap* map);
	~CGreedySearchRoutine();

//	void setTargetTypes(std::vector<ECharacterTypes> target_types);

	void move(CCharacter *character);
	void exec(CCharacter *character);

//	std::vector<ECharacterTypes> getTargetTypes();

private:
	
	void nextCoordinate(CCharacter *character);
	void execTarget(CCharacter* character);
};
