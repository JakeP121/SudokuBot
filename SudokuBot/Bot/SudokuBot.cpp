//
//  Bot.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include "SudokuBot.hpp"
#include "Grid.hpp"
#include "Cell.hpp"
#include "Utilities.hpp"

SudokuBot::SudokuBot(Sudoku::Grid& grid) {
    mGrid = &grid;
}

void SudokuBot::Run(const bool printEachMove) {
    mPrintEachMove = printEachMove;
    
    while (MainLoop())
    {
        if (mGrid)
        {
            Utilities::ClearConsole();
            mGrid->Print();
        }
    }
}

void SudokuBot::GetPossibleValues(const int row, const int column, std::set<int>& outValues) const {
    if (mGrid == nullptr)
    {
        return;
    }
    
    outValues = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    auto removePossibleValues = [&](Sudoku::Cell** cellArr, int arrLength) {
        for (int i = 0; i < arrLength; ++i)
        {
            Sudoku::Cell* cell = cellArr[i];
            if (cell == nullptr)
            {
                continue;
            }
            
            const std::optional<int>& cellValue = cell->GetValue();
            if (!cellValue.has_value())
            {
                continue;
            }
            
            outValues.erase(*cellValue);
        }
    };
    
    
    { // Filter with any cells in current row
        Sudoku::Cell* cellsInRow[Sudoku::Grid::GRID_LENGTH];
        mGrid->GetAllCellsInRow(row, cellsInRow);
        removePossibleValues(cellsInRow, Sudoku::Grid::GRID_LENGTH);
    }
    
    { // Filter with any cells in current column
        Sudoku::Cell* cellsInColumn[Sudoku::Grid::GRID_HEIGHT];
        mGrid->GetAllCellsInColumn(column, cellsInColumn);
        removePossibleValues(cellsInColumn, Sudoku::Grid::GRID_HEIGHT);
    }
    
    { // Filter with any cells in current section
        Sudoku::Cell* cellsInSection[Sudoku::Grid::NUM_CELLS_IN_SECTION];
        mGrid->GetAllCellsInSection(row, column, cellsInSection);
        removePossibleValues(cellsInSection, Sudoku::Grid::NUM_CELLS_IN_SECTION);
    }
}
