#include "Pathfinder.hpp"
#include <queue>
#include <algorithm>

std::vector<Pos> Pathfinder::bfs(const Grid& grid, Pos start, Pos goal)
{
	int w = grid.getWidth();
	int h = grid.getHeight();

	std::vector<bool> visited(w * h, false);
	std::vector<Pos> parent(w * h, Pos{ -1, -1 });

	int dx[4] = { 0, 0, -1, 1 };
	int dy[4] = { -1, 1, 0, 0 };

	std::queue<Pos> q;
	q.push(start);
	visited[start.y * w + start.x] = true;

	bool found = false;

	while (!q.empty())
	{
		Pos cur = q.front();
		q.pop();

		if (cur.x == goal.x && cur.y == goal.y)
		{
			found = true;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int nx = cur.x + dx[i];
			int ny = cur.y + dy[i];

			if (grid.isWalkable(nx, ny) && !visited[ny * w + nx])
			{
				visited[ny * w + nx] = true;
				parent[ny * w + nx] = cur;
				q.push({ nx, ny });
			}
		}
	}

	std::vector<Pos> path;
	if (!found)
		return path;
	Pos p = goal;
	while (!(p.x == start.x && p.y == start.y))
	{
		path.push_back(p);
		p = parent[p.y * w + p.x];
	}
	path.push_back(start);

	std::reverse(path.begin(), path.end());
	return path;
}