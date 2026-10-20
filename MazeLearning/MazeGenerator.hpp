#pragma once

#include "Grid.hpp"
#include <random>

class MazeGenerator
{
private:
	std::mt19937 rng;

public:
	MazeGenerator();

	void generateDFS(Grid& grid);
	void generatePrim(Grid& grid);
};