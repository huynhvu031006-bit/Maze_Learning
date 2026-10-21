#include "Grid.hpp"
#include "Renderer.hpp"
#include "MazeGenerator.hpp"
#include "Pathfinder.hpp"
#include <SFML/Graphics.hpp>
#include <vector>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Maze Learning");

	Grid grid(29, 29);
	MazeGenerator generator;
	generator.generateDFS(grid);

	Renderer renderer(28.0f);
	Pathfinder pathfinder;

	int playerX = 1;
	int playerY = 1;

	int goalX = grid.getWidth() - 2;
	int goalY = grid.getHeight() - 2;

	bool won = false;
	std::vector<Pos> path;

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is < sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
			{
				if (key->code == sf::Keyboard::Key::D)
				{
					generator.generateDFS(grid);
					playerX = 1;
					playerY = 1;
					won = false;
					path.clear();
					window.setTitle("Maze learning");
				}
				else if (key->code == sf::Keyboard::Key::P)
				{
					generator.generatePrim(grid);
					playerX = 1;
					playerY = 1;
					won = false;
					path.clear();
					window.setTitle("Maze Learning");
				}
				else if (key->code == sf::Keyboard::Key::B)
				{
					path = pathfinder.bfs(grid, Pos{ playerX, playerY }, Pos{ goalX, goalY });
				}

				int newX = playerX;
				int newY = playerY;

				if (key->code == sf::Keyboard::Key::Up)  newY--;
				else if (key->code == sf::Keyboard::Key::Down) newY++;
				else if (key->code == sf::Keyboard::Key::Left) newX--;
				else if (key->code == sf::Keyboard::Key::Right) newX++;

				bool daDiChuyen = (newX != playerX || newY != playerY);

				if (!won && daDiChuyen && grid.isWalkable(newX, newY))
				{
					playerX = newX;
					playerY = newY;
					path.clear();
				}

				if (playerX == goalX && playerY == goalY)
				{
					won = true;
					window.setTitle("ban da thang! bam d hoac p de choi lai");
				}
			}
		}
		window.clear(sf::Color::White);
		renderer.drawGrid(window, grid);
		renderer.drawPath(window, path);
		renderer.drawGoal(window, goalX, goalY);
		renderer.drawPlayer(window, playerX, playerY);
		window.display();
	}
	return 0;
}