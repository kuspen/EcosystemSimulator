#pragma once
#include "CCharacter.h"
#include <vector>
#include <set>

class CCharacter;
enum class ECharacterTypes;

class CMap {

private:
	int m_x_size;
	int m_y_size;

	// Mapì‡ÇÃCharacterîzóÒ
	std::vector<CCharacter*> m_characters;
	std::set<CCharacter*> m_willRemovedCharacters;

	// MapÇÃç¿ïWñàÇÃCharacterà íu
	ECharacterTypes *m_maps;

public:
	CMap(int x_size, int y_size);
	~CMap();

	void setCharacter(CCharacter* character);
	void setWillRemovedCharacter(int x, int y);

	int getXSize();
	int getYSize();
	ECharacterTypes* getMaps();
	CCharacter* getCharacter(int x, int y);
	std::vector<CCharacter*> getCharacters();
	std::set<CCharacter*> getWillRemovedCharacters();

	void updateMaps();

	void move_characters();
	void exec_characters();
	void update_characters();
};
