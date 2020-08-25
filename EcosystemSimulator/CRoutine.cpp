#include "CRoutine.h"

CRoutine::CRoutine(CMap* map) : m_map(map) {}

CRoutine::~CRoutine() {};

void CRoutine::setNextX(int x) {
	m_next_x = x;
}
void CRoutine::setNextY(int y) {
	m_next_y = y;
}

int CRoutine::getNextX() {
	return m_next_x;
}

int CRoutine::getNextY() {
	return m_next_y;
}
