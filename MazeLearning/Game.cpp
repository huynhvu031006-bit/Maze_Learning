#include "Game.hpp"

game::game()
	: window(sf::VideoMode({ 1000, 800 }), "Maze_Game"),
	grid(29, 29),
	renderer(27.0f),
	playerX(1),
	playerY(1),
	goalX(grid.getWidth() - 2),
	goalY(grid.getHeight() - 2),
	won(false),
	shown(0),
	timer(0.0f)
{
	newMaze(false);
}

void game::run()
{
	while (window.isOpen())
	{
		handleEvents();
		update();
		render();
	}
}

void game::newMaze(bool usePrim)
{
	if (usePrim)
		generator.generatePrim(grid);
	else
		generator.generateDFS(grid);

	generator.addLoops(grid, 30);
	generator.addMud(grid, 0);

	playerX = 1;
	playerY = 1;
	won = false;
	resetSearch();
	window.setTitle("Maze Learning");
}

void game::resetSearch()
{
	result = PathResult{};
	shown = 0;
}

void game::showStarts(const std::string& name)
{
	window.setTitle(name + ": duyet " + std::to_string(result.visited.size())
	+ " o, duong di " + std::to_string(result.path.size())
	+ " o, chi phi " + std::to_string(result.cost));
}

void game::handleEvents()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed > ())
		{
			window.close();
		}
		else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
		{
			handleKey(key->code);
		}
	}
}

void game::handleKey(sf::Keyboard::Key code)
{
	Pos start{ playerX, playerY };
	Pos goal{ goalX, goalY };

	//-tạo mê cung mới
	if (code == sf::Keyboard::Key::D)
	{
		newMaze(false);
	}
	else if (code == sf::Keyboard::Key::P)
	{
		newMaze(true);
	}
	//-tìm đường
	else if (code == sf::Keyboard::Key::B)
	{
		result = pathfinder.bfs(grid, start, goal);
		shown = 0;
		showStarts("BFS");
	}
	else if (code == sf::Keyboard::Key::J)
	{
		result = pathfinder.dijkstra(grid, start, goal);
		shown = 0;
		showStarts("Dijkstra");
	}
	else if (code == sf::Keyboard::Key::A)
	{
		result = pathfinder.astar(grid, start, goal);
		shown = 0;
		showStarts("A*");
	}

	//-di chuyển nhân vật
	int newX = playerX;
	int newY = playerY;

	if (code == sf::Keyboard::Key::Up)              newY--;
	else if (code == sf::Keyboard::Key::Down)       newY++;
	else if (code == sf::Keyboard::Key::Left)       newX--;
	else if (code == sf::Keyboard::Key::Right)      newX++;

	bool daDiChuyen = (newX != playerX || newY != playerY);

	if (!won && daDiChuyen && grid.isWalkable(newX, newY))
	{
		playerX = newX;
		playerY = newY;
		resetSearch();
	}

	//-kiểm tra thắng'
	if (playerX == goalX && playerY == goalY)
	{
		won = true;
		window.setTitle("Ban da thang! Bam D hoac P de choi lai");
	}
}

void game::update()
{
	timer += clock.restart().asSeconds();
	if (timer >= stepTime)
	{
		timer = 0.0f;
		if (shown < (int)result.visited.size())
			shown++;
	}
}

void game::render()
{
	window.clear(sf::Color::White);
	renderer.drawGrid(window, grid);
	renderer.drawVisited(window, result.visited, shown);

	if (shown >= (int)result.visited.size())
		renderer.drawPath(window, result.path);

	renderer.drawGoal(window, goalX, goalY);
	renderer.drawPlayer(window, playerX, playerY);
	window.display();
}