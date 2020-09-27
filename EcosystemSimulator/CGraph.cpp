#include "CGraph.h"
#include "DxLib.h"
#include "DebugUtil.h"

CGraph::CGraph(int size_x, int size_y) {

	m_size_x = size_x - 80;
	m_size_y = size_y - 60;

	m_origin_x = 40;
	m_origin_y = 720 + 360 - 40;

	m_scale = 1;
	m_x_show_start_index = 0;
}

CGraph::~CGraph() {}


void CGraph::set_character(std::string character_name, int color) {

	graph_info info;
	std::vector<int> num_character;

	info.character_name = character_name;
	info.color = color;
	info.num_character = num_character;

	m_graph_infos.push_back(info);

}

void CGraph::set_character_number(std::string character_name, int number) {

	for (auto&& info : m_graph_infos) {
		if (character_name == info.character_name) {

			// サイズ以上の場合、データを詰めなおし
			if (info.num_character.size() >= m_size_x) {
				std::vector<int> temp_info;
				for (int i = 1; i < m_size_x; i++) {
					temp_info.push_back(info.num_character[i]);
				}
				info.num_character.clear();
				info.num_character = temp_info;
			}
			info.num_character.push_back(number);
		}
	}
	
}

void CGraph::update_graph() {

	// X/Y軸の大きさを確定
	m_scale = 1;
	int graph_x_size = m_size_x;
	for (auto&& info : m_graph_infos) {
		for (auto&& elem : info.num_character) {
			
			int temp_scale = 1;
			temp_scale = elem;
			if (temp_scale > m_scale) m_scale = temp_scale;
			//for (int i = 0; i < (int)std::to_string(elem).length(); i++) {
			//	temp_scale *= 10;
			//}
			//if (temp_scale > m_scale) m_scale = temp_scale;

			if (graph_x_size > info.num_character.size()) {
				graph_x_size = (int)info.num_character.size();
			}
		}
	}

	// X/Y軸表示
	DrawLine(m_origin_x, m_origin_y, m_origin_x + m_size_x, m_origin_y, GetColor(255, 255, 255));
	DrawLine(m_origin_x, m_origin_y, m_origin_x, m_origin_y - m_size_y, GetColor(255, 255, 255));

	DrawString(0, m_origin_y, "0", GetColor(255, 255, 255));
	DrawString(0, m_origin_y - (m_size_y / 2), std::to_string(m_scale/2).c_str(), GetColor(255, 255, 255));
	DrawString(0, m_origin_y - m_size_y, std::to_string(m_scale).c_str(), GetColor(255, 255, 255));

	double y_resolution = (double) m_size_y / m_scale;
	for (auto&& info : m_graph_infos) {
		int last_y;
		for (int x = 0; x < graph_x_size; x++) {
			int y = m_origin_y - (int)(y_resolution * info.num_character[x]);
			DrawPixel(x + m_origin_x, y, info.color);

			if (x != 0) {
				DrawLine(x - 1 + m_origin_x, last_y, x + m_origin_x, y, info.color);
			}
			last_y = y;
		}
	}

}

