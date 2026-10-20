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

void Renderer::drawPlayer(sf::RenderWindow& window, int x, int y)
{
	sf::RectangleShape player;
	player.setSize({ cellSize * 0.6f, cellSize * 0.6f });

	player.setPosition({
		x * cellSize + cellSize * 0.2f,
		y * cellSize + cellSize * 0.2f
		});

	player.setFillColor(sf::Color(0, 180, 0));
	window.draw(player);
}

void Renderer::drawGoal(sf::RenderWindow& window, int x, int y)
{
	sf::RectangleShape goal;
	goal.setSize({ cellSize * 0.8f, cellSize * 0.8f });

	goal.setPosition({
		x * cellSize + cellSize * 0.1f,
		y * cellSize + cellSize * 0.1f
		});
	goal.setFillColor(sf::Color::Red);
	window.draw(goal);
}