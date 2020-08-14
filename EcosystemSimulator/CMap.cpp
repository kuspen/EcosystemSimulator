#include "CMap.h"
#include "DebugUtil.h"

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

void CMap::setWillRemovedCharacter(int x, int y) {
	for (auto itr = m_characters.begin(); itr != m_characters.end(); itr++) {
		if ((*itr)->getX() == x && (*itr)->getY() == y) {
			m_willRemovedCharacters.insert(*itr);
		}
	}
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

CCharacter* CMap::getCharacter(int x, int y) {
	for(int i=0; i<m_characters.size(); i++) {
		int c_x = m_characters[i]->getX();
		int c_y = m_characters[i]->getY();
		if (c_x == x && c_y == y) {
			return m_characters[i];
		}
	}
	return nullptr;
}

std::vector<CCharacter*> CMap::getCharacters() {
	return m_characters;
}

std::set<CCharacter*> CMap::getWillRemovedCharacters() {
	return m_willRemovedCharacters;
}

void CMap::updateMaps() {

	for (int x = 0; x < m_x_size; x++) {
		for (int y = 0; y < m_y_size; y++) {
			m_maps[x + m_x_size * y] = ECharacterTypes::CTYPE_NONE;
		}
	}

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
	for (auto itr = m_characters.begin(); itr != m_characters.end(); itr++) {
		(*itr)->exec();
	}
}

void CMap::update_characters() {

	for (auto s_itr = m_willRemovedCharacters.begin(); s_itr != m_willRemovedCharacters.end(); s_itr++) {
		auto result = std::find(m_characters.begin(), m_characters.end(), (*s_itr));
		DebugPrint("%s %d %d\n", __func__, (*result)->getX(), (*result)->getY());
		if (result != m_characters.end()) {
			DebugPrint("size before = %d\n", m_characters.size());
			m_characters.erase(result);
			DebugPrint("size after = %d\n", m_characters.size());
		}
	}
	m_willRemovedCharacters.clear();

	updateMaps();
}
