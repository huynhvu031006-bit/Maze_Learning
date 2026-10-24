#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Grid.hpp"
#include "Renderer.hpp"
#include "MazeGenerator.hpp"
#include "Pathfinder.hpp"

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

	//-kết quả tìm đường và phát lại
	PathResult result;
	int shown;
	
	sf::Clock clock;
	float timer;
	const float stepTime = 0.03f;

	//-các hàm nội bộ
	void newMaze(bool usePrim);
	void resetSearch();
	void showStarts(const std::string& name);
	void handleEvents();
	void handleKey(sf::Keyboard::Key code);
	void update();
	void render();

public:
	game();
	void run();
};