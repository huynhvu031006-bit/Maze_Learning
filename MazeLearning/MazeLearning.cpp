#include "Grid.hpp"
#include "Renderer.hpp"
#include "MazeGenerator.hpp"
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Maze Learning");

	Grid grid(21, 21);
	MazeGenerator generator;
	generator.generateDFS(grid);

	Renderer renderer(28.0f);

	int playerX = 1;
	int playerY = 1;

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
				}
				else if (key->code == sf::Keyboard::Key::P)
				{
					generator.generatePrim(grid);
					playerX = 1;
					playerY = 1;
				}

				int newX = playerX;
				int newY = playerY;

				if (key->code == sf::Keyboard::Key::Up)  newY--;
				else if (key->code == sf::Keyboard::Key::Down) newY++;
				else if (key->code == sf::Keyboard::Key::Left) newX--;
				else if (key->code == sf::Keyboard::Key::Right) newX++;

				if (grid.isWalkable(newX, newY))
				{
					playerX = newX;
					playerY = newY;
				}
			}
		}
		window.clear(sf::Color::White);
		renderer.drawGrid(window, grid);
		renderer.drawPlayer(window, playerX, playerY);
		window.display();
	}
	return 0;
}