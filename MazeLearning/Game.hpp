#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Grid.hpp"
#include "Renderer.hpp"
#include "MazeGenerator.hpp"
#include "Pathfinder.hpp"

struct SearchStats
{
	std::string name;
	int visited;
	int pathLength;
	int cost;
};

class game
{
private:
	//-các thành phần chính
	sf::RenderWindow window;
	Grid grid;
	MazeGenerator generator;
	Renderer renderer;
	Pathfinder pathfinder;

	//-trạng thái trò chơi
	int playerX;
	int playerY;
	int goalX;
	int goalY;
	bool won;

	//-gợi ý đường đi
	bool showHint;
	std::vector<Pos> hint;
	const int hintStep = 10;

	//-kết quả tìm đường và phát lại
	PathResult result;
	int shown;
	std::string algoName;

	std::vector<SearchStats> compare;
	
	sf::Clock clock;
	float timer;
	float stepTime = 0.03f;

	//-các hàm nội bộ
	void newMaze(bool usePrim);
	void resetSearch();
	void updateHint();
	void runCompare();

	void handleEvents();
	void handleKey(sf::Keyboard::Key code);
	void update();
	void render();
	void drawPanel();

public:
	game();
	void run();
};