#include <iostream>
#include <vector>

#include "DxLib.h"

#include "CCarnivore.h"
#include "CHerbivore.h"
#include "CGrass.h"
#include "CGraph.h"

#include "CGreedySearchRoutine.h"
#include "DebugUtil.h"


const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

const int FIELD_WIDTH = 1280;
const int FIELD_HEIGHT = 720;

const int GRAPH_WIDTH = 1280;
const int GRAPH_HEIGHT = 360;

const int CHARACTER_SIZE = 10;

CMap g_map(FIELD_WIDTH/CHARACTER_SIZE, FIELD_HEIGHT/CHARACTER_SIZE);
CGraph g_graph(GRAPH_WIDTH, GRAPH_HEIGHT);

FILE* g_result_file_fp = nullptr;

void dumpResultFile(std::string file_name) {

	if (g_result_file_fp == nullptr) {
		fopen_s(&g_result_file_fp, file_name.c_str(), "w");
	}
	else {
		// 現在数表示
		int num_grass = 0;
		int num_herbivore = 0;
		int num_carnivore = 0;

		std::vector<CCharacter*> characters = g_map.getCharacters();
		for (auto&& character : characters) {
			CGrass* grass = dynamic_cast<CGrass*>(character);
			CHerbivore* herbivore = dynamic_cast<CHerbivore*>(character);
			CCarnivore* carnivore = dynamic_cast<CCarnivore*>(character);
			if (grass) {
				num_grass++;
			}
			else if (herbivore) {
				num_herbivore++;
			}
			else if (carnivore) {
				num_carnivore++;
			}
		}
		fprintf(g_result_file_fp, "%d,%d,%d\n", num_grass, num_herbivore, num_carnivore);

	}


}

CHerbivore* makeHerbivore(int x, int y) {

	CHerbivore* herbivore = new CHerbivore(x, y);

	std::vector<ECharacterTypes> greedySearchTarget;
	greedySearchTarget.push_back(ECharacterTypes::CTYPE_GRASS);

	CGreedySearchRoutine* greedySearchRoutine = new CGreedySearchRoutine(&g_map);
	greedySearchRoutine->setNextX(x);
	greedySearchRoutine->setNextY(y);
	herbivore->setRoutine(greedySearchRoutine);

	herbivore->setHp(100);
	herbivore->setTargets(greedySearchTarget);
	herbivore->setBornedHp(150);
	herbivore->setRecoveredHp(50);
	herbivore->setStayedHp(200);


	return herbivore;
}

CCarnivore* makeCarnivore(int x, int y) {

	CCarnivore* carnivore = new CCarnivore(x, y);

	std::vector<ECharacterTypes> greedySearchTarget;
	greedySearchTarget.push_back(ECharacterTypes::CTYPE_HERBIVORE);

	CGreedySearchRoutine* greedySearchRoutine = new CGreedySearchRoutine(&g_map);
	greedySearchRoutine->setNextX(x);
	greedySearchRoutine->setNextY(y);
	carnivore->setRoutine(greedySearchRoutine);

	carnivore->setHp(140);
	carnivore->setTargets(greedySearchTarget);
	carnivore->setBornedHp(150);
	carnivore->setRecoveredHp(100);
	carnivore->setStayedHp(200);

	return carnivore;
}

int init() {
	
	std::vector<ECharacterTypes> greedySearchTarget;
	greedySearchTarget.push_back(ECharacterTypes::CTYPE_GRASS);

	CGrass* grass1 = new CGrass(32, 22);
	CGrass* grass2 = new CGrass(43, 42);
	CGrass* grass3 = new CGrass(14, 28);


	grass1->setHp(100);
	grass2->setHp(100);
	grass3->setHp(100);

	g_map.setCharacter(grass1);
	g_map.setCharacter(grass2);
	g_map.setCharacter(grass3);

	g_map.setCharacter(makeHerbivore(10, 10));
	g_map.setCharacter(makeHerbivore(20, 10));
	g_map.setCharacter(makeHerbivore(30, 10));
	g_map.setCharacter(makeHerbivore(40, 10));
	g_map.setCharacter(makeHerbivore(50, 10));
	g_map.setCharacter(makeCarnivore(60, 10));

	g_graph.set_character("Grass", GetColor(0, 255, 0));
	g_graph.set_character("Herbivore", GetColor(0, 0, 255));
	g_graph.set_character("Carnivore", GetColor(255, 0, 0));

	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 16);

	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	return 0;
}

void finalize() {
	if (g_result_file_fp != nullptr) {
		fclose(g_result_file_fp);
		g_result_file_fp = nullptr;
	}
}

int draw() {
	
	std::vector<CCharacter*> characters = g_map.getCharacters();

	// Characterの位置を描写
	for (auto itr = characters.begin(); itr != characters.end(); itr++) {
		int x = (*itr)->getX() * CHARACTER_SIZE;
		int y = (*itr)->getY() * CHARACTER_SIZE;
		ECharacterTypes type = (*itr)->getType();

		unsigned int color = GetColor(0, 0, 0);
		if (type == ECharacterTypes::CTYPE_GRASS) {
			color = GetColor(0, 255, 0);
		}
		else if (type == ECharacterTypes::CTYPE_HERBIVORE) {
//			color = GetColor(0, 0, 255 - (*itr)->getHp());
			color = GetColor(0, 0, (*itr)->getHp());
		}
		else if (type == ECharacterTypes::CTYPE_CARNIVORE) {
//			color = GetColor(255, 0, 0);
			color = GetColor((*itr)->getHp(), 0, 0);
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

	// Grassをランダムに発生させる
	for (int x = 0; x < x_size; x++) {
		for (int y = 0; y < y_size; y++) {
			if (map[x + x_size * y] == ECharacterTypes::CTYPE_NONE) {
				int rand_max = 500;
				int rand = GetRand(rand_max);
				if (rand == 0) {
					CGrass* grass = new CGrass(x, y);
					g_map.setCharacter(grass);
				}
			}
		}
	}

	for (auto&& character : characters) {
		CHerbivore* herbivore = dynamic_cast<CHerbivore*>(character);
		CCarnivore* carnivore = dynamic_cast<CCarnivore*>(character);
		// herbivoreが繁殖する処理
		if (herbivore) {
			if (herbivore->isBorn()) {
				herbivore->setHp(herbivore->getHp() - 100);
				int x = herbivore->getX();
				int y = herbivore->getY();
				if (x - 1 >= 0 && map[(x - 1) + x_size * y] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeHerbivore(x-1, y));
				}
				else if (x + 1 < x_size && map[(x + 1) + x_size * y] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeHerbivore(x+1, y));
				}
				else if (y - 1 >= 0 && map[x + x_size * (y - 1)] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeHerbivore(x, y-1));
				}
				else if (y + 1 < y_size && map[x + x_size * (y + 1)] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeHerbivore(x, y+1));
				}
			}
		}
		// carnivoreが繁殖する処理
		else if (carnivore) {
			if (carnivore->isBorn()) {
				carnivore->setHp(carnivore->getHp() - 100);
				int x = carnivore->getX();
				int y = carnivore->getY();
				if (x - 1 >= 0 && map[(x - 1) + x_size * y] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeCarnivore(x-1, y));
				}
				else if (x + 1 < x_size && map[(x + 1) + x_size * y] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeCarnivore(x+1, y));
				}
				else if (y - 1 >= 0 && map[x + x_size * (y - 1)] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeCarnivore(x, y-1));
				}
				else if (y + 1 < y_size && map[x + x_size * (y + 1)] == ECharacterTypes::CTYPE_NONE) {
					g_map.setCharacter(makeCarnivore(x, y+1));
				}
			}

		}
	}

	// 現在数表示
	int num_grass = 0;
	int num_herbivore = 0;
	int num_carnivore = 0;

	for (auto&& character : characters) {
		CGrass* grass = dynamic_cast<CGrass*>(character);
		CHerbivore* herbivore = dynamic_cast<CHerbivore*>(character);
		CCarnivore* carnivore = dynamic_cast<CCarnivore*>(character);
		if (grass) {
			num_grass++;
		}
		else if (herbivore) {
			num_herbivore++;
		}
		else if (carnivore) {
			num_carnivore++;
		}
	}

	clsDx();
	printfDx("Grass = %d\n", num_grass);
	printfDx("Herbivore = %d\n", num_herbivore);
	printfDx("Carnivore = %d\n", num_carnivore);

	// グラフ表示
	g_graph.set_character_number("Grass", num_grass);
	g_graph.set_character_number("Herbivore", num_herbivore);
	g_graph.set_character_number("Carnivore", num_carnivore);
	g_graph.update_graph();

	dumpResultFile(std::string("result.txt"));

	return 0;
}

int move() {

	std::vector<CCharacter*> characters = g_map.getCharacters();

	for (auto itr = characters.begin(); itr != characters.end(); itr++) {
		(*itr)->move();
	}
	g_map.updateMaps();

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

	for (auto&& character : g_map.getCharacters()) {
		CHerbivore* herbivore = dynamic_cast<CHerbivore*>(character);
		CCarnivore* carnivore = dynamic_cast<CCarnivore*>(character);
		// herbivoreのhp減少
		if (herbivore) {
			int hp = herbivore->getHp() - 1;
			if (hp <= 0) {
				g_map.setWillRemovedCharacter(herbivore->getX(), herbivore->getY());
			}
			herbivore->setHp(hp);
		}
		// carnivoreのhp減少
		else if (carnivore) {
			int hp = carnivore->getHp() - 1;
			if (hp <= 0) {
				g_map.setWillRemovedCharacter(carnivore->getX(), carnivore->getY());
			}
			carnivore->setHp(hp);
		}
	}

	// map内のCharactersから削除予定のCharacterを削除
	g_map.update_characters();
	return 0;
}


int main(int argc, char* argv[]) {


//	setDebugMode(EDebugMode::DEBUG_MODE_DEBUG_FULL);


	init();
	Sleep(5000);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		ClearDrawScreen();

		setup();

		move();

		exec();

		status_update();

		draw();

		ScreenFlip();

		WaitTimer(1);

	}

	DxLib_End();

	finalize();

	return 0;
}

