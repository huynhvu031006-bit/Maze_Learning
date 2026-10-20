#pragma once

#include <vector>

enum class CellType
{
	Wall,
	Path
};

class Grid
{
private:
	int width;
	int height;

	std::vector<CellType> cells;

public:
	Grid(int width, int height);

	int getWidth() const;
	int getHeight() const;

	CellType getCell(int x, int y) const;
	void setCell(int x, int y, CellType type);

	bool isWalkable(int x, int y) const;
};