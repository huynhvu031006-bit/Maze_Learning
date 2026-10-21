#pragma once

#include "Grid.hpp"
#include <vector>

class Pathfinder
{
public:
	std::vector<Pos> bfs(const Grid& grid, Pos start, Pos goal);
};