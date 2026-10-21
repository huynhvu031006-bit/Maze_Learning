#pragma once

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Renderer
{
private:
	float cellSize;

public:
	Renderer(float cellSize);

	void drawGrid(sf::RenderWindow& window, const Grid& grid);

	void drawPlayer(sf::RenderWindow& window, int x, int y);

	void drawGoal(sf::RenderWindow& window, int x, int y);

	void drawPath(sf::RenderWindow& window, const std::vector<Pos>& path);
};