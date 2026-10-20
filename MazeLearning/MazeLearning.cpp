#include "Grid.hpp"
#include "Renderer.hpp"
#include "MazeGenerator.hpp"
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Maze Learning");

	Grid grid(30, 30);
	MazeGenerator generator;
	generator.generateDFS(grid);

	Renderer renderer(28.0f);

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
					generator.generateDFS(grid);
				else if (key->code == sf::Keyboard::Key::P)
					generator.generatePrim(grid);
			}
		}
		window.clear(sf::Color::White);
		renderer.drawGrid(window, grid);
		window.display();
	}
	return 0;
}