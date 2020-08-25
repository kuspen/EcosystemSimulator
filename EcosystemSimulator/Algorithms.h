#pragma once
#include "CMap.h"
#include "CCharacter.h"
#include <vector>

struct Coordinate {
	int x;
	int y;
};

void breadthFirstSearch(CMap* map, CCharacter* character, std::vector<ECharacterTypes> target, int* result, int* x, int* y);
void getShortestStep(CMap* map, int* result, int target_x, int target_y, int *next_x, int *next_y);

unsigned int getRandomValue();
