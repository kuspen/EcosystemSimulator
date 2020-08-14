#include <iostream>
#include <vector>

#include "DxLib.h"

#include "CHerbivore.h"
#include "CGrass.h"

#include "CGreedySearchRoutine.h"
#include "DebugUtil.h"


const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

const int CHARACTER_SIZE = 10;

CMap g_map(WINDOW_WIDTH/CHARACTER_SIZE, WINDOW_HEIGHT/CHARACTER_SIZE);
std::vector<CCharacter*> g_characters;



int init() {
	
	std::vector<ECharacterTypes> greedySearchTarget;
	greedySearchTarget.push_back(ECharacterTypes::CTYPE_GRASS);

	CHerbivore* herbivore = new CHerbivore(1, 1);
	CGrass* grass1 = new CGrass(32, 22);
	CGrass* grass2 = new CGrass(43, 42);
	CGrass* grass3 = new CGrass(14, 28);

	herbivore->setTargets(greedySearchTarget);

	CGreedySearchRoutine* greedySearchRoutine = new CGreedySearchRoutine(&g_map);
	herbivore->setRoutine(greedySearchRoutine);

	g_characters.push_back(herbivore);
	g_characters.push_back(grass1);
	g_characters.push_back(grass2);
	g_characters.push_back(grass3);

	for (auto itr = g_characters.begin(); itr != g_characters.end(); itr++) {
		g_map.setCharacter(*itr);
	}

	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);

	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	return 0;
}

int draw() {
	
	std::vector<CCharacter*> characters = g_map.getCharacters();

	// CharacterÇÃà íuÇï`é 
	for (auto itr = characters.begin(); itr != characters.end(); itr++) {
		int x = (*itr)->getX() * CHARACTER_SIZE;
		int y = (*itr)->getY() * CHARACTER_SIZE;
		ECharacterTypes type = (*itr)->getType();

		unsigned int color = GetColor(0, 0, 0);
		if (type == ECharacterTypes::CTYPE_GRASS) {
			color = GetColor(0, 255, 0);
		}
		else if (type == ECharacterTypes::CTYPE_HERBIVORE) {
			color = GetColor(0, 0, 255);
		}
		else if (type == ECharacterTypes::CTYPE_CARNIVORE) {
			color = GetColor(255, 0, 0);
		}

		DrawBox(x, y, x + CHARACTER_SIZE, y + CHARACTER_SIZE, color, TRUE);

	}

	return 0;

}

int setup() {
	
	ECharacterTypes *map = g_map.getMaps();
	std::vector<CCharacter*> characters = g_map.getCharacters();
	int x_size = g_map.getXSize();
	int y_size = g_map.getYSize();

	// GrassÇÉâÉìÉ_ÉÄÇ…î≠ê∂Ç≥ÇπÇÈ
	for (int x = 0; x < x_size; x++) {
		for (int y = 0; y < y_size; y++) {
			if (map[x + x_size * y] == ECharacterTypes::CTYPE_NONE) {
				int rand = GetRand(20000);
				if (rand == 0) {
					CGrass* grass = new CGrass(x, y);
					g_map.setCharacter(grass);
				}
			}
		}
	}

	return 0;
}

int move() {

	std::vector<CCharacter*> characters = g_map.getCharacters();

	for (auto itr = characters.begin(); itr != characters.end(); itr++) {
		(*itr)->move();
	}

	return 0;
}

int exec() {

	std::vector<CCharacter*> characters = g_map.getCharacters();

	for (auto itr = characters.begin(); itr != characters.end(); itr++) {
		(*itr)->exec();
	}

	return 0;
}

int status_update() {

	// g_charactersÇ∆g_mapì‡ÇÃCharactersÇìØä˙
	std::set<CCharacter*> willRemovedCharacters = g_map.getWillRemovedCharacters();
	for (auto s_itr = willRemovedCharacters.begin(); s_itr != willRemovedCharacters.end(); s_itr++) {
		auto itr = std::find(g_characters.begin(), g_characters.end(),(*s_itr));
		if (itr != g_characters.end()) {
			g_characters.erase(itr);
		}
	}

	// mapì‡ÇÃCharactersÇ©ÇÁçÌèúó\íËÇÃCharacterÇçÌèú
	g_map.update_characters();
	return 0;
}


int main(int argc, char* argv[]) {

	setDebugMode(EDebugMode::DEBUG_MODE_DEBUG_FULL);


	init();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();

		setup();

		move();

		exec();

		status_update();

		draw();

		ScreenFlip();

		WaitTimer(100);

	}

	DxLib_End();

	return 0;
}

