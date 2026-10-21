#include "MazeGenerator.hpp"
#include <stack>
#include <vector>

MazeGenerator::MazeGenerator()
	: rng(std::random_device{}())
{
}

void MazeGenerator::generateDFS(Grid& grid)
{
	int w = grid.getWidth();
	int h = grid.getHeight();

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			grid.setCell(x, y, CellType::Wall);

	int dx[4] = { 0, 0, -2, 2 };
	int dy[4] = { -2, 2, 0, 0 };

	std::stack<Pos> stack;
	grid.setCell(1, 1, CellType::Path);
	stack.push({ 1, 1 });

	while (!stack.empty())
	{
		Pos cur = stack.top();
		
		std::vector<int> dirs;
		for (int i = 0; i < 4; i++)
		{
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];

			bool trongLuoi = (nx >= 1 && nx < w - 1 && ny >= 1 && ny < h - 1);
			if (trongLuoi && grid.getCell(nx, ny) == CellType::Wall)
				dirs.push_back(i);
		}
		if (dirs.empty())
		{
			stack.pop();
		}
		else
		{
			std::uniform_int_distribution<int> dist(0, (int)dirs.size() - 1);
			int d = dirs[dist(rng)];

			grid.setCell(cur.x + dx[d] / 2, cur.y + dy[d] / 2, CellType::Path);
			grid.setCell(cur.x + dx[d], cur.y + dy[d], CellType::Path);

			stack.push({ cur.x + dx[d], cur.y + dy[d] });
		}
	}
}

void MazeGenerator::generatePrim(Grid& grid)
{
	int w = grid.getWidth();
	int h = grid.getHeight();

	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++)
			grid.setCell(x, y, CellType::Wall);

	int dx[4] = { 0, 0, -2, 2 };
	int dy[4] = { -2, 2, 0, 0 };

	std::vector<Pos> frontier;
	std::vector<bool> inFrontier(w * h, false);

	auto addFrontier = [&](int cx, int cy)
		{
			for (int i = 0; i < 4; i++)
			{
				int nx = cx + dx[i];
				int ny = cy + dy[i];

				bool trongLuoi = (nx >= 1 && nx < w - 1 && ny >= 1 && ny < h - 1);
				if (trongLuoi
					&& grid.getCell(nx, ny) == CellType::Wall
					&& !inFrontier[ny * w + nx])
				{
					frontier.push_back({ nx, ny });
					inFrontier[ny * w + nx] = true;
				}
			}
		};
	grid.setCell(1, 1, CellType::Path);
	addFrontier(1, 1);

	while (!frontier.empty())
	{
		std::uniform_int_distribution<int> distF(0, (int)frontier.size() - 1);
		int idx = distF(rng);
		Pos cur = frontier[idx];

		frontier[idx] = frontier.back();
		frontier.pop_back();

		std::vector<int> dirs;
		for (int i = 0; i < 4; i++)
		{
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];

			bool trongLuoi = (nx >= 1 && nx < w - 1 && ny >= 1 && ny < h - 1);
			if (trongLuoi && grid.getCell(nx, ny) == CellType::Path)
				dirs.push_back(i);
		}

		std::uniform_int_distribution<int> distD(0, (int)dirs.size() - 1);
		int d = dirs[distD(rng)];

		grid.setCell(cur.x + dx[d] / 2, cur.y + dy[d] / 2, CellType::Path);
		grid.setCell(cur.x, cur.y, CellType::Path);

		addFrontier(cur.x, cur.y);
	}
}