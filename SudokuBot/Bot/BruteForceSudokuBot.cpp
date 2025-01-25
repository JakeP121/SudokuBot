//
//  BruteForceSudokuBot.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include "BruteForceSudokuBot.hpp"

#include <map>
#include <iostream>

#include "Defines.h"

BruteForceMove::BruteForceMove(const Sudoku::Coordinate& coord, const std::set<int>& possibleValues, const int& chosenValue)
    : mCoord(coord)
    , mPossibleValues(possibleValues)
    , mChosenValue(chosenValue)
{
}

BruteForceSudokuBot::BruteForceSudokuBot(Sudoku::Grid& grid)
    : SudokuBot(grid)
{
}

bool BruteForceSudokuBot::MainLoop() {
        
    if (mGrid == nullptr)
    {
        return false;
    }
    
    Sudoku::Coordinate emptyCell = FindEmptyCell();
    if (emptyCell.IsValid())
    {
        std::set<int> possibleValues;
        GetPossibleValues(emptyCell.x, emptyCell.y, possibleValues);
        
        if (possibleValues.size() <= 0)
        {
#if PRINT_MOVES
            printf("We've fucked up. No possible values for %s\n",
                   emptyCell.GetStringValue().c_str());
#endif
            
            const bool bRecoveredFromFuckUp = WeFuckedUp();
            
#if PRINT_MOVES
            if (bRecoveredFromFuckUp)
            {
                printf("Recovered from the fuck up \n");
            }
            else
            {
                printf("Failed to recover from the fuck up \n");
            }
#endif
            return bRecoveredFromFuckUp;
        }
        
        const int value = *(possibleValues.begin());
        mGrid->SetCell(emptyCell.x, emptyCell.y, value);
        mHistory.push(BruteForceMove(emptyCell, possibleValues, value));
        return true;
    }
    
    return false;
}

Sudoku::Coordinate BruteForceSudokuBot::FindEmptyCell() const {
    if (mGrid == nullptr )
    {
        return Sudoku::Coordinate();
    }
    
    Sudoku::Coordinate emptyCellCoords;
    
    mGrid->ForEachCell([&emptyCellCoords](Sudoku::Cell& cell, const int row, const int column) {
        if (cell.HasValue())
        {
            return true; // Continue to next cell
        }
        
        emptyCellCoords = { row, column };
        return false;
    });
    
    return emptyCellCoords;
}

bool BruteForceSudokuBot::WeFuckedUp() {
    if (mGrid == nullptr || mHistory.empty())
    {
        return false;
    }
    
    BruteForceMove& lastMove = mHistory.top();
    if (lastMove.mPossibleValues.size() <= 1)
    {
        // No other possible values for the last decision, pop it off and fall back an earlier one
#if PRINT_MOVES
        printf("Undoing guess for cell %s\n",
               lastMove.mCoord.GetStringValue().c_str());
#endif
        
        mGrid->ClearCell(lastMove.mCoord.x, lastMove.mCoord.y);
        mHistory.pop();
        
        return WeFuckedUp();
    }
    else
    {
        // This potential move has failed us, roll back and pick a different one
        int oldValue = lastMove.mChosenValue;
        
        lastMove.mPossibleValues.erase(oldValue);
        lastMove.mChosenValue = *(lastMove.mPossibleValues.begin());
        
#if PRINT_MOVES
        printf("Trying another value for cell %s (%i -> %i)\n",
               lastMove.mCoord.GetStringValue().c_str(),
               oldValue,
               lastMove.mChosenValue);
#endif
        
        mGrid->SetCell(lastMove.mCoord.x, lastMove.mCoord.y, lastMove.mChosenValue);
        
        return true; // Recovered
    }
}

void BruteForceSudokuBot::CrosscheckRow(Sudoku::Cell& cell, const int row, std::set<int>& possibleValues) {
    if (mGrid == nullptr)
    {
        return;
    }
    
    Sudoku::Cell* rowCells[Sudoku::Grid::GRID_LENGTH];
    mGrid->GetAllCellsInRow(row, rowCells);
    
}

bool BruteForceSudokuBot::TryPossibleValues(const int row, const int column, std::set<int> (&allPossibleValues)[Sudoku::Grid::GRID_LENGTH][Sudoku::Grid::GRID_HEIGHT]) {
    if (mGrid == nullptr)
    {
        return false;
    }
    
    
    // Iterate through a row
    // Make a map<value, [possible columns]>
    // If any value in that map only had one possible column, fill it
    
    for (int row = 0; row < Sudoku::Grid::GRID_HEIGHT; ++row)
    {
        for (int column = 0; column < Sudoku::Grid::GRID_LENGTH; ++column)
        {
            if (allPossibleValues[column][row].empty())
            {
                continue;
            }
        }
    }
    
    return true;
}

bool BruteForceSudokuBot::TryPossibleValues(Sudoku::Cell& cell, const int row, const int column, std::set<int>& possibleValues) {
    
    if (mGrid == nullptr)
    {
        return false;
    }
    
    {
        Sudoku::Cell* cellsInRow[Sudoku::Grid::GRID_LENGTH];
        mGrid->GetAllCellsInRow(row, cellsInRow);
        
        std::set<int> rowPossibilities;
        for (int i = 0; i < Sudoku::Grid::GRID_LENGTH; ++i)
        {
            Sudoku::Cell* otherCell = cellsInRow[i];
            if (otherCell == nullptr || &cell == otherCell)
            {
                continue;
            }
            
            if (otherCell->HasValue())
            {
                continue;
            }
            
            
        }
    }
    
    return false;
}
