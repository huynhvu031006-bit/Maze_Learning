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

			CellType type = grid.getCell(x, y);

			if (type == CellType::Wall)
			{
				cell.setFillColor(sf::Color::Black);
			}
			else if (type == CellType::Mud)
				cell.setFillColor(sf::Color(139, 90, 43));
			else
					cell.setFillColor(sf::Color::White);
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

void Renderer::drawPath(sf::RenderWindow& window, const std::vector<Pos>& path)
{
	for (const Pos& p : path)
	{
		sf::RectangleShape dot;
		dot.setSize({ cellSize * 0.3f, cellSize * 0.3f });

		dot.setPosition({
			p.x * cellSize + cellSize * 0.35f,
			p.y * cellSize + cellSize * 0.35f
			});
		dot.setFillColor(sf::Color(255, 160, 0));
		window.draw(dot);
	}
}

void Renderer::drawVisited(sf::RenderWindow& window, const std::vector<Pos>& visited, int count)
{
	for (int i = 0; i < count && i < (int)visited.size(); i++)
	{
		sf::RectangleShape cell;
		cell.setSize({ cellSize, cellSize });

		cell.setPosition({
			visited[i].x * cellSize,
			visited[i].y * cellSize
			});
		cell.setFillColor(sf::Color(80, 140, 255, 110));
		window.draw(cell);
	}
}