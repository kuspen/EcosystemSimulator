#include "CMap.h"

CMap::CMap(int x_size, int y_size) : m_x_size(x_size), m_y_size(y_size) {
	int size = x_size * y_size;
	m_maps = new ECharacterTypes[size];
	
	for (int i = 0; i < size; i++) {
		m_maps[i] = ECharacterTypes::CTYPE_NONE;
	}
}

CMap::~CMap() {
	delete[] m_maps;
}

void CMap::setCharacter(CCharacter* character) {

	// ƒŠƒXƒg‚É“o˜^
	m_characters.push_back(character);

	// map‚É”½‰f
	int x = character->getX();
	int y = character->getY();
	ECharacterTypes type = character->getType();
	m_maps[x + m_x_size * y] = type;

}

int CMap::getXSize() {
	return m_x_size;
}

int CMap::getYSize() {
	return m_y_size;
}

ECharacterTypes* CMap::getMaps() {
	return m_maps;
}
void CMap::updateMaps() {
	for (auto itr = m_characters.begin(); itr != m_characters.end(); itr++) {
		int x = (*itr)->getX();
		int y = (*itr)->getY();
		ECharacterTypes type = (*itr)->getType();
		m_maps[x + m_x_size * y] = type;
	}
}

void CMap::move_characters() {
	for (auto itr = m_characters.begin(); itr != m_characters.end(); itr++) {
		(*itr)->move();
	}
}

void CMap::exec_characters() {

}

void CMap::update_characters() {

}
