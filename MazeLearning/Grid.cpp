#include "Grid.hpp"

Grid::Grid(int width, int height)
	: width(width), height(height),
	cells(width* height, CellType::Wall)
{
}

int Grid::getWidth() const
{
	return width;
}

int Grid::getHeight() const
{
	return height;
}

CellType Grid::getCell(int x, int y) const
{
	return cells[y * width + x];
}

void Grid::setCell(int x, int y, CellType type)
{
	cells[y * width + x] = type;
}
bool Grid::isWalkable(int x, int y) const
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return false;
	return cells[y * width + x] == CellType::Path;
}