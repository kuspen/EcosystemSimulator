#include "CCharacter.h"

CCharacter::CCharacter(int x, int y, ECharacterTypes type):m_x(x), m_y(y), m_type(type) {}

CCharacter::~CCharacter() {}

void CCharacter::setX(int x) {
	m_x = x;
}

void CCharacter::setY(int y) {
	m_y = y;
}

void CCharacter::setType(ECharacterTypes type) {
	m_type = type;
}

void CCharacter::setRoutine(CRoutine *routine) {
	m_routine = routine;
}

void CCharacter::setTargets(std::vector<ECharacterTypes> targets) {
	m_targets = targets;
}

int CCharacter::getX() {
	return m_x;
}

int CCharacter::getY() {
	return m_y;
}

ECharacterTypes CCharacter::getType() {
	return m_type;
}

std::vector<ECharacterTypes> CCharacter::getTargets() {
	return m_targets;
}

void CCharacter::move() {

	if (m_routine != nullptr) {
		m_routine->run(this);

		m_x = m_routine->getNextX();
		m_y = m_routine->getNextY();
	}

}

