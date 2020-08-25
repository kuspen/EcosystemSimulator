#include "CGreedySearchRoutine.h"
#include "Algorithms.h"

#include "DebugUtil.h"

CGreedySearchRoutine::CGreedySearchRoutine(CMap* map) : CRoutine(map) {}

CGreedySearchRoutine::~CGreedySearchRoutine() {}

void CGreedySearchRoutine::move(CCharacter *character) {
	nextCoordinate(character);
}

void CGreedySearchRoutine::exec(CCharacter *character) {
	execTarget(character);
}

//void CGreedySearchRoutine::setTargetTypes(std::vector<ECharacterTypes> target_types){
//	m_targetTypes = target_types;
//}
//
//std::vector<ECharacterTypes> CGreedySearchRoutine::getTargetTypes() {
//	return m_targetTypes;
//}

void CGreedySearchRoutine::nextCoordinate(CCharacter *character) {

	// ˆê’è‚ÌHPˆÈã‚Å‚ ‚ê‚Î‚»‚Ìê‚Å‘Ò‹@
	if (character->isStay()) return;

	std::vector<ECharacterTypes> targets = character->getTargets();

	int size = m_map->getXSize() * m_map->getYSize();
	int* result = new int[size];
	for (int i = 0; i < size; i++) {
		result[i] = -1;
	}

	DWORD time = GetTickCount64();
	char c_time[128];
	sprintf_s(c_time, "%s_%d.txt", __func__, time);
	//DebugOpenFile(std::string(c_time));

	int target_x, target_y;
	breadthFirstSearch(m_map, character, targets, result, &target_x, &target_y);

	//for (int y = 0; y < m_map->getYSize(); y++) {
	//	for (int x = 0; x < m_map->getXSize(); x++) {
	//		DebugDumpFile("%03d ", result[x + m_map->getXSize() * y]);
	//	}
	//	DebugDumpFile("\n");
	//}

	if (target_x != -1 && target_y != -1) {
		getShortestStep(m_map, result, target_x, target_y, &m_next_x, &m_next_y);
//		DebugPrint("next_x=%d next_y=%d\n", m_next_x, m_next_y);
	}

	//DebugCloseFile();

	delete[] result;
}

void CGreedySearchRoutine::execTarget(CCharacter *character) {

	// ˆê’è‚ÌHPˆÈã‚Å‚ ‚ê‚Î‚»‚Ìê‚Å‘Ò‹@
	if (character->isStay()) return;
	
	std::vector<ECharacterTypes> targets = character->getTargets();

	ECharacterTypes *map = m_map->getMaps();
	int x_size = m_map->getXSize();
	int y_size = m_map->getYSize();

	int x = character->getX();
	int y = character->getY();

	for (auto itr = targets.begin(); itr != targets.end(); itr++) {

		int target_x = -1;
		int target_y = -1;

		// —×‚Étarget‚ª‘¶Ý‚·‚é‚©Šm”F
		if (x - 1 >= 0 && map[(x - 1) + x_size * y] == (*itr)) {
			target_x = x - 1;
			target_y = y;
		}
		else if (x + 1 < x_size && map[(x + 1) + x_size * y] == (*itr)) {
			target_x = x + 1;
			target_y = y;
		}
		else if (y - 1 >= 0 && map[x + x_size * (y - 1)] == (*itr)) {
			target_x = x;
			target_y = y - 1;
		}
		else if (y + 1 < y_size && map[x + x_size * (y + 1)] == (*itr)) {
			target_x = x;
			target_y = y + 1;
		}
		
		if(target_x != -1 && target_y != -1) {
			// íœÏ‚ÝCharacters‚É“o˜^‚³‚ê‚Ä‚¢‚È‚¢ê‡
			std::set<CCharacter*> willRemovedCharacters =  m_map->getWillRemovedCharacters();
			CCharacter* target = m_map->getCharacter(target_x, target_y);
			if (willRemovedCharacters.find(target) == willRemovedCharacters.end()) {
				m_map->setWillRemovedCharacter(target_x, target_y);
				character->recover();
				break;
			}
		}
	}

}
