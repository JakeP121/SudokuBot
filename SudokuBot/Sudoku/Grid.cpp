//
//  Grid.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include "Grid.hpp"
#include <iostream>

namespace Sudoku {
    Grid::Grid(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]) {
        Initialise(initialGrid);
    }

    void Grid::Initialise(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]) {
        for (int row = 0; row < GRID_HEIGHT; ++row)
        {
            for (int column = 0; column < GRID_LENGTH; ++column)
            {
                int value = initialGrid[column][row]; // Flipping this since it's nicer to handle it as [x][y] internally, but typing it would be [row (y)][column (x)]
                if (Cell::IsValidValue(value))
                {
                    mCells[row][column].SetValue(value);
                }
                else
                {
                    mCells[row][column].ClearValue();
                }
            }
        }
    }

    void Grid::SetCell(const int row, const int column, const int value) {
        if (!IsValidCoordinate(row, column))
        {
            throw "Invalid coordinate";
        }
        
        mCells[column][row].SetValue(value);
    }

    void Grid::Print(bool drawDividers /*= true*/) const {
        
        ForEachCell([&](const Cell& cell, const int row, const int column){
            
            cell.Print();
            
            const bool isLastCellInRow = (column == (GRID_LENGTH - 1));
            if (isLastCellInRow)
            {
                std::cout << "\n";
            }
            
            if (drawDividers)
            {
                if ((column > 0) && (column < GRID_LENGTH - 1) && (column+1) % 3 == 0)
                {
                    std::cout << " | ";
                }
                
                if (isLastCellInRow && (row < GRID_HEIGHT - 1) && (row+1) % 3 == 0)
                {
                    std::cout << "---------------------------------\n";
                }
            }
        });
    }

    bool Grid::Validate() {

        bool anyErrors = false;
        
        ForEachCell([&](Cell& cell, const int row, const int column){
            cell.SetValid(true);
        });
        
        ForEachCell([&](Cell& cell, const int row, const int column){
            
            if (!cell.GetValue().has_value())
            {
                return; // No value set yet
            }
            
            // Check for matching cells in row
            for (int i = (column + 1); i < GRID_LENGTH; ++i)
            {
                Cell& otherCell = mCells[i][row];
                if (cell == otherCell)
                {
                    cell.SetValid(false);
                    otherCell.SetValid(false);
                    anyErrors = true;
                }
            }
            
            // Check for matching cells in column
            for (int i = (row + 1); i < GRID_HEIGHT; ++i)
            {
                Cell& otherCell = mCells[column][i];
                if (cell == otherCell)
                {
                    cell.SetValid(false);
                    otherCell.SetValid(false);
                    anyErrors = true;
                }
            }
            
            // Check for matching cells in box
            Cell* sectionCells[NUM_CELLS_IN_SECTION];
            GetAllCellsInSection(row, column, sectionCells);
            for (int i = 0; i < NUM_CELLS_IN_SECTION; ++i)
            {
                if (sectionCells[i] == nullptr || &cell == sectionCells[i])
                {
                    continue;
                }
                 
                Cell& otherCell = *sectionCells[i];
                if (cell == otherCell)
                {
                    cell.SetValid(false);
                    otherCell.SetValid(false);
                    anyErrors = true;
                }
            }
        });
        
        return anyErrors;
    }

    bool Grid::IsValidCoordinate(const int row, const int column) const {
        if (row >= GRID_LENGTH)
        {
            return false;
        }
        if (column >= GRID_HEIGHT)
        {
            return false;
        }
        
        return true;
    }

    void Grid::ForEachCell(std::function<void(Cell&, const int /*row*/, const int /*column*/)> predicate) {
        for (int row = 0; row < GRID_HEIGHT; ++row)
        {
            for (int column = 0; column < GRID_LENGTH; ++column)
            {
                predicate(mCells[column][row], row, column);
            }
        }
    }

    void Grid::ForEachCell(std::function<void(const Cell&, const int /*row*/, const int /*column*/)> predicate) const {
        for (int row = 0; row < GRID_HEIGHT; ++row)
        {
            for (int column = 0; column < GRID_LENGTH; ++column)
            {
                predicate(mCells[column][row], row, column);
            }
        }
    }

    void Grid::GetAllCellsInSection(const int row, const int column, Cell* (&outCells)[NUM_CELLS_IN_SECTION]) {
        const int rowOffset = (row % 3);
        const int columnOffset = (column % 3);
        
        for (int rowIter = 0; rowIter < 3; ++rowIter)
        {
            for (int columnIter = 0; columnIter < 3; ++columnIter)
            {
                int outCellRow = (row - rowOffset) + rowIter;
                int outCellColumn = (column - columnOffset) + columnIter;
                
                if (!IsValidCoordinate(outCellRow, outCellColumn))
                {
                    throw "Invalid coordinate";
                }
                
                int outCellIndex = (rowIter * 3) + columnIter;
                outCells[outCellIndex] = &mCells[outCellColumn][outCellRow];
            }
        }
    }
}
