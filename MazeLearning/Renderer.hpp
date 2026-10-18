#pragma

#include <SFML/Graphics.hpp>
#include "Grid.hpp"

class Renderer
{
private:
	float cellSize;

public:
	Renderer(float cellSize);

	void drawGrid(sf::RenderWindow& window, const Grid& grid);
};