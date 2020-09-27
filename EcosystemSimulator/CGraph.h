#pragma once
#include <vector>
#include <string>
class CGraph {

private:

	int m_size_x;
	int m_size_y;

	int m_origin_x;
	int m_origin_y;

	int m_scale;

	int m_x_show_start_index;

	typedef struct {
		std::string character_name;
		unsigned int color;
		std::vector<int> num_character;
	} graph_info;

	std::vector<graph_info> m_graph_infos;

public:
	CGraph(int size_x, int size_y);
	~CGraph();

	void set_character(std::string character_name, int color);
	void set_character_number(std::string character_name, int number);
	void update_graph();

};

