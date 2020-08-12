#include "Algorithms.h"
#include "DebugUtil.h"

#include <queue>



void breadthFirstSearch(CMap* map, CCharacter *character, std::vector<ECharacterTypes> targets, int* result, int *x, int *y) {

	*x = -1;
	*y = -1;

	int temp_x = character->getX();
	int temp_y = character->getY();

	int graph_x_size = map->getXSize();
	int graph_y_size = map->getYSize();
	int graph_size = graph_x_size * graph_y_size;
	ECharacterTypes *graph = new ECharacterTypes[graph_size];
	ECharacterTypes* org_graph = map->getMaps();

	for (int i = 0; i < graph_size; i++) {
		graph[i] = org_graph[i];
	}
	
	Coordinate current = {temp_x, temp_y};

	std::queue<Coordinate> q;
	q.push(current);
	graph[current.x + graph_x_size * current.y] = ECharacterTypes::CTYPE_NULL;
	result[current.x + graph_x_size * current.y] = 0;

	while (!q.empty()) {
		current = q.front();
		q.pop();
		
		// up
		if (current.y - 1 >= 0) {
	
			for (auto itr = targets.begin(); itr != targets.end(); itr++) {
				ECharacterTypes target = *itr;
				if (graph[current.x + graph_x_size * (current.y - 1)] == target) {
					*x = current.x;
					*y = current.y + 1;
					delete[] graph;
					return;
				}
				else if (graph[current.x + graph_x_size * (current.y - 1)] == ECharacterTypes::CTYPE_NONE) {
					Coordinate temp = {current.x, current.y + 1};
					graph[temp.x + graph_x_size * temp.y] = ECharacterTypes::CTYPE_NULL;
					result[current.x + graph_x_size * (current.y - 1)] = result[current.x + graph_x_size * current.y] + 1;
					q.push(temp);
				}
			}

		}
		// down
		if (current.y + 1 < graph_y_size) {

			for (auto itr = targets.begin(); itr != targets.end(); itr++) {
				ECharacterTypes target = *itr;
				if (graph[current.x + graph_x_size * (current.y + 1)] == target) {
					*x = current.x;
					*y = current.y + 1;
					delete[] graph;
					return;
				}
				else if (graph[current.x + graph_x_size * (current.y + 1)] == ECharacterTypes::CTYPE_NONE) {
					Coordinate temp = { current.x, current.y + 1 };
					graph[temp.x + graph_x_size * temp.y] = ECharacterTypes::CTYPE_NULL;
					result[current.x + graph_x_size * (current.y + 1)] = result[current.x + graph_x_size * current.y] + 1;
					q.push(temp);
				}
			}

		}
		// left
		if (current.x - 1 >= 0) {

			for (auto itr = targets.begin(); itr != targets.end(); itr++) {
				ECharacterTypes target = *itr;
				if (graph[(current.x - 1) + graph_x_size * current.y] == target) {
					*x = current.x - 1;
					*y = current.y;
					delete[] graph;
					return;
				}
				else if (graph[(current.x - 1) + graph_x_size * current.y] == ECharacterTypes::CTYPE_NONE) {
					Coordinate temp = { current.x - 1, current.y };
					graph[temp.x + graph_x_size * temp.y] = ECharacterTypes::CTYPE_NULL;
					result[(current.x - 1) + graph_x_size * current.y] = result[current.x + graph_x_size * current.y] + 1;
					q.push(temp);
				}
			}

		}
		// right
		if (current.x + 1 < graph_x_size) {

			for (auto itr = targets.begin(); itr != targets.end(); itr++) {
				ECharacterTypes target = *itr;
				if (graph[(current.x + 1) + graph_x_size * current.y] == target) {
					*x = current.x + 1;
					*y = current.y;
					delete[] graph;
					return;
				}
				else if (graph[(current.x + 1) + graph_x_size * current.y] == ECharacterTypes::CTYPE_NONE) {
					Coordinate temp = { current.x + 1, current.y };
					graph[temp.x + graph_x_size * temp.y] = ECharacterTypes::CTYPE_NULL;
					result[(current.x + 1) + graph_x_size * current.y] = result[current.x + graph_x_size * current.y] + 1;
					q.push(temp);
				}
			}

		}
	}

	delete[] graph;
	
}

void getShortestStep(CMap* map, int* result, int target_x, int target_y, int *next_x, int *next_y) {

	int graph_x_size = map->getXSize();
	int graph_y_size = map->getYSize();


	Coordinate current = {target_x, target_y};

	enum class EDirect {
		UP, DOWN, LEFT, RIGHT
	};

	while (1) {

		int min = graph_x_size * graph_y_size * graph_x_size;
		bool isFind = false;

		EDirect direct;
			
		// up
		if (current.y - 1 >= 0 && result[current.x + graph_x_size * (current.y-1)] != -1) {
			if (min > result[current.x + graph_x_size * (current.y - 1)]) {
				min = result[current.x + graph_x_size * (current.y - 1)];

				if (min == 0) {
					*next_x = current.x;
					*next_y = current.y;
					return;
				}

				direct = EDirect::UP;
				isFind = true;
			}
		}
		// down
		if (current.y + 1 < graph_y_size && result[current.x + graph_x_size * (current.y+1)] != -1) {
			if (min > result[current.x + graph_x_size * (current.y + 1)]) {
				min = result[current.x + graph_x_size * (current.y + 1)];

				if (min == 0) {
					*next_x = current.x;
					*next_y = current.y;
					return;
				}
				direct = EDirect::DOWN;
				isFind = true;
			}
		}
		// left
		if (current.x - 1 >= 0 && result[(current.x-1) + graph_x_size * current.y] != -1) {
			if (min > result[(current.x - 1) + graph_x_size * current.y]) {
				min = result[(current.x - 1) + graph_x_size * current.y];

				if (min == 0) {
					*next_x = current.x;
					*next_y = current.y;
					return;
				}
				direct = EDirect::LEFT;
				isFind = true;
			}
		}
		// right
		if (current.x + 1 < graph_x_size && result[(current.x+1) + graph_x_size * current.y] != -1) {
			if (min > result[(current.x + 1) + graph_x_size * current.y]) {
				min = result[(current.x + 1) + graph_x_size * current.y];

				if (min == 0) {
					*next_x = current.x;
					*next_y = current.y;
					return;
				}
				direct = EDirect::RIGHT;
				isFind = true;
			}
		}

		if (isFind) {
			if (direct == EDirect::UP) {
				current.y = current.y - 1;
			}
			else if (direct == EDirect::DOWN) {
				current.y = current.y + 1;
			}
			else if (direct == EDirect::LEFT) {
				current.x = current.x - 1;
			}
			else if (direct == EDirect::RIGHT) {
				current.x = current.x + 1;
			}
		}
		else {
			break;
		}
	}

}
