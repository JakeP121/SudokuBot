#pragma once

//
//  Grid.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include <functional>
#include <string>

#include "Cell.hpp"
#include "SudokuDefines.h"

namespace Sudoku {    
    class Grid
    {
    public:
        static const int GRID_LENGTH = SUDOKU_NUMBER;
        static const int GRID_HEIGHT = SUDOKU_NUMBER;
        static const int NUM_CELLS_IN_SECTION = SUDOKU_NUMBER;
        
        Grid() = default;
        Grid(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]);
        
        void Initialise(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]);
        void SetCell(const int row, const int column, const int value);
        void ClearCell(const int row, const int column);
        
        bool IsFilled() const;
        bool Validate();
        
        void Print(bool drawDividers = true) const;
        
        void ForEachCell(std::function<bool(Cell&, const int /*row*/, const int /*column*/)> predicate);
        void ForEachCell(std::function<bool(const Cell&, const int /*row*/, const int /*column*/)> predicate) const;
        
        Cell* GetCell(const int row, const int column);
        void GetAllCellsInRow(const int row, Cell* (&outCells)[GRID_LENGTH]);
        void GetAllCellsInColumn(const int column, Cell* (&outCells)[GRID_HEIGHT]);
        void GetAllCellsInSection(const int row, const int column, Cell* (&outCells)[NUM_CELLS_IN_SECTION]);
        
    private:
        bool IsValidCoordinate(const int row, const int column) const;
        
        bool ValidateCell(const int row, const int column);
        
        Cell mCells[GRID_LENGTH][GRID_HEIGHT];
    };
}
