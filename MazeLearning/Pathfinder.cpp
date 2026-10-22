#include "Pathfinder.hpp"
#include <queue>
#include <functional>
#include <algorithm>

static std::vector<Pos> buildPath(const std::vector<Pos>& parent, int w, Pos start, Pos goal)
{
	std::vector<Pos> path;

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

static int calcCost(const Grid& grid, const std::vector<Pos> path)
{
	int total = 0;
	for (int i = 1; i < (int)path.size(); i++)
		total += grid.getCost(path[i].x, path[i].y);
	return total;
}

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
	
	result.path = buildPath(parent, w, start, goal);
	result.cost = calcCost(grid, result.path);
	return result;
}

struct Node
{
	int cost;
	Pos pos;

	bool operator>(const Node& other) const
	{
		return cost > other.cost;
	}
};

PathResult Pathfinder::dijkstra(const Grid& grid, Pos start, Pos goal)
{
	PathResult result;

	int w = grid.getWidth();
	int h = grid.getHeight();

	const int INF = 1000000000;
	std::vector<int> dist(w * h, INF);
	std::vector<bool> done(w * h, false);
	std::vector<Pos> parent(w * h, Pos{ -1, -1 });

	int dx[4] = { 0, 0, -1, 1 };
	int dy[4] = { -1, 1, 0, 0 };

	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

	dist[start.y * w + start.x] = 0;
	pq.push(Node{ 0, start });

	bool found = false;

	while (!pq.empty())
	{
		Node cur = pq.top();
		pq.pop();

		int ci = cur.pos.y * w + cur.pos.x;

		if (done[ci])
			continue;
		done[ci] = true;

		result.visited.push_back(cur.pos);

		if (cur.pos.x == goal.x && cur.pos.y == goal.y)
		{
			found = true; 
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			int nx = cur.pos.x + dx[i];
			int ny = cur.pos.y + dy[i];

			if (!grid.isWalkable(nx, ny))
				continue;

			int ni = ny * w + nx;
			if (done[ni])
				continue;

			int newCost = dist[ci] + grid.getCost(nx, ny);

			if (newCost < dist[ni])
			{
				dist[ni] = newCost;
				parent[ni] = cur.pos;
				pq.push(Node{ newCost, Pos{ nx, ny } });
			}
		}
	}
	if (!found)
		return result;
	result.path = buildPath(parent, w, start, goal);;
	result.cost = calcCost(grid, result.path);
	return result;
}