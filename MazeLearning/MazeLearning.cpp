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
	
	PathResult result;
	int shown = 0;

	sf::Clock clock;
	float timer = 0.0f;
	const float stepTime = 0.03f;

	auto reserSearch = [&]()
		{
			result = PathResult{};
			shown = 0;
		};

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
					reserSearch();
					window.setTitle("Maze learning");
				}
				else if (key->code == sf::Keyboard::Key::P)
				{
					generator.generatePrim(grid);
					playerX = 1;
					playerY = 1;
					won = false;
					reserSearch();
					window.setTitle("Maze Learning");
				}
				else if (key->code == sf::Keyboard::Key::B)
				{
					result = pathfinder.bfs(grid, Pos{ playerX, playerY }, Pos{ goalX, goalY });
					shown = 0;

					window.setTitle("BFS: duyet " + std::to_string(result.visited.size())
						+ " o, duong di dai " + std::to_string(result.path.size()) + " o");
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
					reserSearch();
				}

				if (playerX == goalX && playerY == goalY)
				{
					won = true;
					window.setTitle("ban da thang! bam d hoac p de choi lai");
				}
			}
		}

		timer += clock.restart().asSeconds();
		if (timer >= stepTime)
		{
			timer = 0.0f;
			if (shown < (int)result.visited.size())
				shown++;
		}

		window.clear(sf::Color::White);
		renderer.drawGrid(window, grid);
		renderer.drawVisited(window, result.visited, shown);

		if (shown >= (int)result.visited.size())
			renderer.drawPath(window, result.path);

		renderer.drawGoal(window, goalX, goalY);
		renderer.drawPlayer(window, playerX, playerY);
		window.display();
	}
	return 0;
}