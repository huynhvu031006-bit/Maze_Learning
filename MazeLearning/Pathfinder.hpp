#pragma once

#include "Grid.hpp"
#include <vector>

struct PathResult
{
	std::vector<Pos> path;
	std::vector<Pos> visited;
};

class Pathfinder
{
public:
	PathResult bfs(const Grid& grid, Pos start, Pos goal);
};