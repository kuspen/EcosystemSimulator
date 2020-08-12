#include "CGreedySearchRoutine.h"
#include "Algorithms.h"

#include "DebugUtil.h"

CGreedySearchRoutine::CGreedySearchRoutine(CMap* map) : CRoutine(map) {}

CGreedySearchRoutine::~CGreedySearchRoutine() {}

void CGreedySearchRoutine::run(CCharacter *character) {
	nextCoordinate(character);
}

//void CGreedySearchRoutine::setTargetTypes(std::vector<ECharacterTypes> target_types){
//	m_targetTypes = target_types;
//}
//
//std::vector<ECharacterTypes> CGreedySearchRoutine::getTargetTypes() {
//	return m_targetTypes;
//}

void CGreedySearchRoutine::nextCoordinate(CCharacter *character) {

	std::vector<ECharacterTypes> targets = character->getTargets();

	int size = m_map->getXSize() * m_map->getYSize();
	int* result = new int[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}

	int target_x, target_y;
	breadthFirstSearch(m_map, character, targets, result, &target_x, &target_y);
	if (target_x != -1 && target_y != -1) {
		getShortestStep(m_map, result, target_x, target_y, &m_next_x, &m_next_y);
	}

	delete[] result;
}

