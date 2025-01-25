//
//  Bot.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include "SudokuBot.hpp"

#include "Cell.hpp"
#include "Defines.h"
#include "Grid.hpp"
#include "Utilities.hpp"

SudokuBot::SudokuBot(Sudoku::Grid& grid) {
    mGrid = &grid;
}

void SudokuBot::Run() {
    
    while (MainLoop())
    {
#if PRINT_MOVES
        {
            PrintGrid();
        }
#endif
    }
    
    PrintGrid();
}

std::optional<int> SudokuBot::GetExclusivePossibleValue(const int row, const int column) const {
    
    if (mGrid == nullptr)
    {
        return {};
    }
    
    Sudoku::Cell* thisCell = mGrid->GetCell(row, column);
    if (thisCell == nullptr)
    {
        return {};
    }
    
    std::set<int> possibleValues;
    GetPossibleValues(row, column, possibleValues);
    if (possibleValues.empty())
    {
        return {};
    }
    else if (possibleValues.size() == 1)
    {
        return *possibleValues.begin();
    }
    
    auto GetAllPossibleValuesForOtherCells = [this, &thisCell](Sudoku::Cell* (&cells)[9], std::set<int>& possibleValues) {
        for (int i = 0; i < SUDOKU_NUMBER; ++i)
        {
            Sudoku::Cell* cell = cells[i];
            if (cell == nullptr || cell == thisCell || cell->HasValue())
            {
                continue;
            }
            
            std::set<int> cellPossibleValues;
            GetPossibleValues(cell->GetRow(), cell->GetColumn(), cellPossibleValues);
            
            for (int value : cellPossibleValues)
            {
                possibleValues.insert(value);
            }
            
            if (possibleValues.size() == SUDOKU_NUMBER)
            {
                return; // All possible values, no point continuing
            }
        }
    };
    
    { // Check if one of our possible values isn't allowed anywhere else in this row
        Sudoku::Cell* cellsInRow[Sudoku::Grid::GRID_LENGTH];
        mGrid->GetAllCellsInRow(row, cellsInRow);
        
        std::set<int> possibleValuesForOtherCells;
        GetAllPossibleValuesForOtherCells(cellsInRow, possibleValuesForOtherCells);
        
        if (possibleValuesForOtherCells.size() < Sudoku::Grid::GRID_LENGTH)
        {
            for (int possibleValue : possibleValues)
            {
                if (!possibleValuesForOtherCells.contains(possibleValue))
                {
                    return possibleValue;
                }
            }
        }
    }
    
    { // Check if one of our possible values isn't allowed anywhere else in this column
        Sudoku::Cell* cellsInColumn[Sudoku::Grid::GRID_HEIGHT];
        mGrid->GetAllCellsInColumn(column, cellsInColumn);
        
        std::set<int> possibleValuesForOtherCells;
        GetAllPossibleValuesForOtherCells(cellsInColumn, possibleValuesForOtherCells);
    
        if (possibleValuesForOtherCells.size() < Sudoku::Grid::GRID_HEIGHT)
        {
            for (int possibleValue : possibleValues)
            {
                if (!possibleValuesForOtherCells.contains(possibleValue))
                {
                    return possibleValue;
                }
            }
        }
    }
    
    { // Check if one of our possible values isn't allowed anywhere else in this section
        Sudoku::Cell* cellsInSection[Sudoku::Grid::NUM_CELLS_IN_SECTION];
        mGrid->GetAllCellsInSection(row, column, cellsInSection);
        
        std::set<int> possibleValuesForOtherCells;
        GetAllPossibleValuesForOtherCells(cellsInSection, possibleValuesForOtherCells);
    
        if (possibleValuesForOtherCells.size() < Sudoku::Grid::GRID_LENGTH)
        {
            for (int possibleValue : possibleValues)
            {
                if (!possibleValuesForOtherCells.contains(possibleValue))
                {
                    return possibleValue;
                }
            }
        }
    }
    
    
    return {};
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

void SudokuBot::PrintGrid()
{
    if (mGrid)
    {
        Utilities::ClearConsole();
        mGrid->Print();
    }
}
