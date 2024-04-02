#pragma once

#include "Particle.hpp"

#include <vector>

class GridCell
{
private:
    size_t m_PosX;
    size_t m_PosY;
    size_t m_Size;
public:
    std::vector<size_t> particlesIndices;

    GridCell(size_t posX, size_t posY, size_t size);
    ~GridCell();
};

class Grid
{
private:
    size_t m_SizeX;
    size_t m_SizeY;
    size_t m_CellSize;

    size_t m_NumCellsX;
    size_t m_NumCellsY;

    std::vector<std::vector<GridCell>> m_Cells;
    std::vector<Particle*>& m_SceneParticles;

    void PopulateGrid();
    void CheckCollisions(const float dt);
public:
    Grid(size_t sizeX, size_t sizeY, size_t cellSize, std::vector<Particle*>& sceneParticles);
    ~Grid();

    void Update(const float dt);
};
