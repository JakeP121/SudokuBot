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

    class Grid {
      
        static const int GRID_LENGTH = 9;
        static const int GRID_HEIGHT = 9;
        static const int NUM_CELLS_IN_SECTION = 9;
        
    public:
        Grid() = default;
        Grid(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]);
        
        void Initialise(const int (&initialGrid)[GRID_LENGTH][GRID_HEIGHT]);
        void SetCell(const int row, const int column, const int value);
        
        void Print(bool drawDividers = true) const;
        bool Validate();
        
    private:
        bool IsValidCoordinate(const int row, const int column) const;
        void ForEachCell(std::function<void(Cell&, const int /*row*/, const int /*column*/)> predicate);
        void ForEachCell(std::function<void(const Cell&, const int /*row*/, const int /*column*/)> predicate) const;
        
        void GetAllCellsInSection(const int row, const int column, Cell* (&outCells)[NUM_CELLS_IN_SECTION]);
        
        Cell mCells[GRID_LENGTH][GRID_HEIGHT];
    };
}
