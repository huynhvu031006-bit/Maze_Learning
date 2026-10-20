#include "Grid.hpp"
#include "Renderer.hpp"
#include "MazeGenerator.hpp"
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Maze Learning");

	Grid grid(29, 29);
	MazeGenerator generator;
	generator.generateDFS(grid);

	Renderer renderer(28.0f);

	int playerX = 1;
	int playerY = 1;

	int goalX = grid.getWidth() - 2;
	int goalY = grid.getHeight() - 2;

	bool won = false;

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
					window.setTitle("Maze learning");
				}
				else if (key->code == sf::Keyboard::Key::P)
				{
					generator.generatePrim(grid);
					playerX = 1;
					playerY = 1;
					won = false;
					window.setTitle("Maze Learning");
				}

				int newX = playerX;
				int newY = playerY;

				if (key->code == sf::Keyboard::Key::Up)  newY--;
				else if (key->code == sf::Keyboard::Key::Down) newY++;
				else if (key->code == sf::Keyboard::Key::Left) newX--;
				else if (key->code == sf::Keyboard::Key::Right) newX++;

				if (!won && grid.isWalkable(newX, newY))
				{
					playerX = newX;
					playerY = newY;
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
		renderer.drawGoal(window, goalX, goalY);
		renderer.drawPlayer(window, playerX, playerY);
		window.display();
	}
	return 0;
}