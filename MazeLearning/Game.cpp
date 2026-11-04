#include "Game.hpp"

game::game()
	: window(sf::VideoMode({ 1100, 800 }), "Maze_Game"),
	grid(29, 29),
	renderer(27.0f),
	playerX(1),
	playerY(1),
	goalX(grid.getWidth() - 2),
	goalY(grid.getHeight() - 2),
	won(false),
	showHint(false),
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
	updateHint();
	window.setTitle("Maze Learning");
}

void game::resetSearch()
{
	result = PathResult{};
	shown = 0;
	algoName = "";
}

void game::updateHint()
{
	hint.clear();

	if (!showHint || won)
		return;

	PathResult r = pathfinder.astar(grid, Pos{ playerX, playerY }, Pos{ goalX, goalY });

	for (int i = 1; i < (int)r.path.size() && i <= hintStep; i++)
		hint.push_back(r.path[i]);
}

void game::runCompare()
{
	Pos start{ playerX, playerY };
	Pos goal{ goalX, goalY };

	compare.clear();

	auto add = [&](const std::string& name, const PathResult& r)
		{
			compare.push_back(SearchStats{
				name,
				(int)r.visited.size(),
				(int)r.path.size(),
				r.cost

				});
		};
	add("BFS", pathfinder.bfs(grid, start, goal));
	add("Dijkstra", pathfinder.dijkstra(grid, start, goal));
	add("A*", pathfinder.astar(grid, start, goal));
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
		algoName = "BFS";
	}
	else if (code == sf::Keyboard::Key::J)
	{
		result = pathfinder.dijkstra(grid, start, goal);
		shown = 0;
		algoName = "Dijkstra";
	}
	else if (code == sf::Keyboard::Key::A)
	{
		result = pathfinder.astar(grid, start, goal);
		shown = 0;
		algoName = "A*";
	}
	else if (code == sf::Keyboard::Key::H)
	{
		showHint = !showHint;
		updateHint();
	}
	else if (code == sf::Keyboard::Key::C)
	{
		runCompare();
	}
	else if (code == sf::Keyboard::Key::Equal || code == sf::Keyboard::Key::Add)
	{
		stepTime /= 1.5f;
		if (stepTime < 0.002f)
			stepTime = 0.002f;
	}
	else if (code == sf::Keyboard::Key::Hyphen || code == sf::Keyboard::Key::Subtract)
	{
		stepTime *= 1.5f;
		if (stepTime < 0.3f)
			stepTime = 0.3f;
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
		updateHint();
	}

	//-kiểm tra thắng'
	if (playerX == goalX && playerY == goalY)
	{
		won = true;
		updateHint();
		window.setTitle("Ban da thang! Bam D hoac P de choi lai");
	}
}

void game::update()
{
	timer += clock.restart().asSeconds();

	int total = (int)result.visited.size();

	while (timer >= stepTime && shown < total)
	{
		timer -= stepTime;
		shown++;
	}

	if (shown >= total)
	{
		timer = 0.0f;
	}
}

void game::render()
{
	window.clear(sf::Color::White);
	renderer.drawGrid(window, grid);
	renderer.drawVisited(window, result.visited, shown);

	if (shown >= (int)result.visited.size())
		renderer.drawPath(window, result.path);

	renderer.drawHint(window, hint);
	renderer.drawGoal(window, goalX, goalY);
	renderer.drawPlayer(window, playerX, playerY);

	drawPanel();
	window.display();
}

void game::drawPanel()
{
	const float x = 810.0f;
	sf::Color ink = sf::Color::Black;
	sf::Color gray(110, 110, 110);

	renderer.drawText(window, "Maze learning", x, 15.0f, 24, ink);

	std::vector<std::string> info;
	
	if (algoName.empty())
	{
		info.push_back("Thuat toan: (chua chay)");
	}
	else
	{
		info.push_back("Thuat toan: " + algoName);
		info.push_back("O da duyet: " + std::to_string(result.visited.size()));
		info.push_back("Duong di: " + std::to_string(result.path.size()) + " o");
		info.push_back("Chi phi: " + std::to_string(result.cost));
	}

	info.push_back("");
	info.push_back(std::string("Goi y: ") + (showHint ? "Bat" : "Tat"));
	info.push_back(won ? "Thang!" : "Dang choi");

	float y = 70.0f;
	for (const std::string& line : info)
	{
		renderer.drawText(window, line, x, y, 18, ink);
		y += 26.0f;
	}

	if (!compare.empty())
	{
		float cy = 300.0f;

		renderer.drawText(window, "So sanh 3 thuat toan", x, cy, 16, ink);
		cy += 22.0f;

		renderer.drawText(window, "Ten", x, cy, 14, gray);
		renderer.drawText(window, "Duyet", x + 100.0f, cy, 14, gray);
		renderer.drawText(window, "Dai", x + 170.0f, cy, 14, gray);
		renderer.drawText(window, "Phi", x + 225.0f, cy, 14, gray);
		cy += 22.0f;

		for (const SearchStats& s : compare)
		{
			renderer.drawText(window, s.name, x, cy, 16, ink);
			renderer.drawText(window, std::to_string(s.visited), x + 100.0f, cy, 16, ink);
			renderer.drawText(window, std::to_string(s.pathLength), x + 170.0f, cy, 16, ink);
			renderer.drawText(window, std::to_string(s.cost), x + 225.0f, cy, 16, ink);
			cy += 24.0f;
		}
	}

	std::vector<std::string> guide = {
		"PHIM:",
		"Mui ten: di chuyen",
		"D / P: tao me cung",
		"B: BFS",
		"J: Dijkstra",
		"A: A*",
		"H: bat/tat goi y"
	};

	y = 400.0f;
	for (const std::string& line : guide)
	{
		renderer.drawText(window, line, x, y, 16, gray);
		y += 24.0f;
	}
}