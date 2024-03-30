#include "Grid.hpp"
#include "PhysicsUtility.hpp"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <algorithm>

GridCell::GridCell(size_t posX, size_t posY, size_t size)
    : m_PosX(posX), m_PosY(posY), m_Size(size)
{
    
}

GridCell::~GridCell()
{
    
}

Grid::Grid(size_t sizeX, size_t sizeY, size_t cellSize)
    : m_SizeX(sizeX), m_SizeY(sizeY), m_CellSize(cellSize)
{
    m_NumCellsX = static_cast<size_t>(sizeX / cellSize);
    m_NumCellsY = static_cast<size_t>(sizeY / cellSize);

    // Creating a grid of cells by instantiating cells corresponding to the given dimensions
    for (size_t x = 0; x < m_NumCellsX; x++)
    {
        m_Cells.push_back(std::vector<GridCell>());

        for (size_t y = 0; y < m_NumCellsY; y++)
        {
            m_Cells[x].push_back(GridCell(x * m_CellSize, y * m_CellSize, 80));
        }
    }
}

Grid::~Grid()
{
    
}

void Grid::Update(std::vector<Particle*>& sceneParticles, const float dt)
{   
    #pragma region PopulateGrid

    // Removing all particles from grid cells
    for (size_t x = 0; x < m_NumCellsX; x++)
    {
        for (size_t y = 0; y < m_NumCellsY; y++)
        {
            m_Cells[x][y].particlesIndices.clear();
        }
    }

    // Populating the cells of the grid with particles according to their positions
    for (size_t i = 0; i < sceneParticles.size(); i++)
    {
        Particle* particle = sceneParticles[i];
        glm::vec2 pos = particle->GetPosition();
        float r = particle->GetRadius();

        size_t indexX = static_cast<size_t>(pos.x / m_CellSize);
        size_t indexY = static_cast<size_t>(pos.y / m_CellSize);

        // Constraining indices to the bounds of cells grid
        indexX = std::min(std::max(indexX, static_cast<size_t>(0)), m_NumCellsX - 1);
        indexY = std::min(std::max(indexY, static_cast<size_t>(0)), m_NumCellsY - 1);

        m_Cells[indexX][indexY].particlesIndices.push_back(i);

        // Use the remainder to determine if some particles overlap multiple cells
        size_t remX = static_cast<size_t>(pos.x) % m_CellSize;
        size_t remY = static_cast<size_t>(pos.y) % m_CellSize;
        
        if (remX < r)
        {
            size_t index = indexX - 1;
            index = std::min(std::max(index, static_cast<size_t>(0)), m_NumCellsX - 1);
            m_Cells[index][indexY].particlesIndices.push_back(i);
        }
        if (remY < r)
        {
            size_t index = indexY - 1;
            index = std::min(std::max(index, static_cast<size_t>(0)), m_NumCellsY - 1);
            m_Cells[indexX][index].particlesIndices.push_back(i);
        }
        if (remX < r && remY < r)
        {
            size_t index_x = indexX - 1;
            size_t index_y = indexY - 1;

            index_x = std::min(std::max(index_x, static_cast<size_t>(0)), m_NumCellsX - 1);
            index_y = std::min(std::max(index_y, static_cast<size_t>(0)), m_NumCellsY - 1);
            m_Cells[index_x][index_y].particlesIndices.push_back(i);
        }
    }

    #pragma endregion

    
    #pragma region CheckCollisions

    // Iterate over all cells in the grid
    for (size_t x = 0; x < m_NumCellsX; x++)
    {
        for (size_t y = 0; y < m_NumCellsY; y++)
        {
            GridCell& cell = m_Cells[x][y];

            // Skip the cell if it contains 1 or no particles
            if (cell.particlesIndices.size() < 2)
                continue;

            // Check collisions between all pairs of particles in the cell
            for (size_t i = 0; i < cell.particlesIndices.size() - 1; i++)
            {
                for (size_t j = i + 1; j < cell.particlesIndices.size(); j++)
                {
                    Particle* p1 = sceneParticles[cell.particlesIndices[i]];
                    Particle* p2 = sceneParticles[cell.particlesIndices[j]];

                    if (SolveCollision(p1, p2))
                        ConductHeat(p1, p2, dt);
                }
            }
        }
    }
    #pragma endregion
}
