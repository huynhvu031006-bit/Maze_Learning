#include "Pathfinder.hpp"
#include <queue>
#include <algorithm>

PathResult Pathfinder::bfs(const Grid& grid, Pos start, Pos goal)
{
	PathResult result;

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

		result.visited.push_back(cur);

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

	if (!found)
		return result;
	Pos p = goal;
	while (!(p.x == start.x && p.y == start.y))
	{
		result.path.push_back(p);
		p = parent[p.y * w + p.x];
	}
	result.path.push_back(start);

	std::reverse(result.path.begin(), result.path.end());
	return result;
}