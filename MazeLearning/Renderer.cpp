#include "Renderer.hpp"

Renderer::Renderer(float cellSize)
	: cellSize(cellSize)
{
}

void Renderer::drawGrid(sf::RenderWindow& window, const Grid& grid)
{
	for (int y = 0; y < grid.getHeight(); y++)
	{
		for (int x = 0; x < grid.getWidth(); x++)
		{
			sf::RectangleShape cell;

			cell.setSize({ cellSize, cellSize });

			cell.setPosition({
				x * cellSize,
				y * cellSize
				});

			if (grid.getCell(x, y) == CellType::Wall)
			{
				cell.setFillColor(sf::Color::Black);
			}
			else
			{
				cell.setFillColor(sf::Color::White);
			}	
			window.draw(cell);
		}
	}
}