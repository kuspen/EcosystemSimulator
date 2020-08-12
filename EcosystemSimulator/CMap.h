#pragma once
#include "CCharacter.h"
#include <vector>

class CCharacter;
enum class ECharacterTypes;

class CMap {

private:
	int m_x_size;
	int m_y_size;

	// Map����Character�z��
	std::vector<CCharacter*> m_characters;

	// Map�̍��W����Character�ʒu
	ECharacterTypes *m_maps;

public:
	CMap(int x_size, int y_size);
	~CMap();

	void setCharacter(CCharacter* character);

	int getXSize();
	int getYSize();
	ECharacterTypes* getMaps();

	void updateMaps();

	void move_characters();
	void exec_characters();
	void update_characters();
};
