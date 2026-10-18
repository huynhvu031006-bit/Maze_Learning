#include "Grid.hpp"
#include "Renderer.hpp"
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Maze Learning");

	Grid grid(10, 10);

	grid.setCell(1, 1, CellType::Path);
	grid.setCell(2, 1, CellType::Path);
	grid.setCell(3, 1, CellType::Path);

	grid.setCell(3, 2, CellType::Path);
	grid.setCell(3, 3, CellType::Path);

	Renderer renderer(40.0f);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is < sf::Event::Closed>())
			{
				window.close();
			}
		}
		window.clear(sf::Color::White);
		renderer.drawGrid(window, grid);
		window.display();
	}
	return 0;
}