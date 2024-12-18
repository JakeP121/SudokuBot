#pragma once

//
//  Grid.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include "Cell.hpp"
#include <functional>

namespace Sudoku {

    class Grid
    {
    public:
        static const int GRID_LENGTH = 9;
        static const int GRID_HEIGHT = 9;
        static const int NUM_CELLS_IN_SECTION = 9;
        
        Grid() = default;
        Grid(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]);
        
        void Initialise(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]);
        void SetCell(const int row, const int column, const int value);
        
        bool IsFilled() const;
        bool Validate();
        
        void Print(bool drawDividers = true) const;
        
        void ForEachCell(std::function<bool(Cell&, const int /*row*/, const int /*column*/)> predicate);
        void ForEachCell(std::function<bool(const Cell&, const int /*row*/, const int /*column*/)> predicate) const;
        
        void GetAllCellsInRow(const int row, Cell* (&outCells)[GRID_LENGTH]);
        void GetAllCellsInColumn(const int column, Cell* (&outCells)[GRID_HEIGHT]);
        void GetAllCellsInSection(const int row, const int column, Cell* (&outCells)[NUM_CELLS_IN_SECTION]);
        
    private:
        bool IsValidCoordinate(const int row, const int column) const;
        
        bool ValidateCell(const int row, const int column);
        
        Cell mCells[GRID_LENGTH][GRID_HEIGHT];
    };
}
