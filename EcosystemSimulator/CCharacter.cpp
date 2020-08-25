#include "CCharacter.h"
#include "Algorithms.h"

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

void CCharacter::setHp(int hp) {
	if (hp > 255) hp = 255;
	m_hp = hp;
}

void CCharacter::setRecoveredHp(int recorverd_hp) {
	m_recovered_hp = recorverd_hp;
}

void CCharacter::setBornedHp(int bornedHp) {
	m_borned_hp = bornedHp;
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

int CCharacter::getHp() {
	return m_hp;
}

void CCharacter::recover() {
	setHp(getHp() + m_recovered_hp);
}

bool CCharacter::isBorn() {
	if (m_hp >= m_borned_hp) {
		if (getRandomValue() % 3 == 0) {
			return true;
		}
	}
	return false;
}


void CCharacter::move() {

	if (m_routine != nullptr) {
		m_routine->move(this);

		m_x = m_routine->getNextX();
		m_y = m_routine->getNextY();
	}

}

void CCharacter::exec() {

	if (m_routine != nullptr) {
		m_routine->exec(this);
	}

}

