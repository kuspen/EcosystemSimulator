#include "CRoutine.h"

CRoutine::CRoutine(CMap* map) : m_map(map) {}

CRoutine::~CRoutine() {};

int CRoutine::getNextX() {
	return m_next_x;
}

int CRoutine::getNextY() {
	return m_next_y;
}
