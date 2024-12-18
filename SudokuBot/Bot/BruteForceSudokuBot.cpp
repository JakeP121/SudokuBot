//
//  BruteForceSudokuBot.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include "BruteForceSudokuBot.hpp"
#include "Grid.hpp"

BruteForceSudokuBot::BruteForceSudokuBot(Sudoku::Grid& grid)
    : SudokuBot(grid)
{
    
}

bool BruteForceSudokuBot::MainLoop() {
    if (mGrid == nullptr)
    {
        return false;
    }
    
    bool anyMovesMade = false;
    
    mGrid->ForEachCell([this, &anyMovesMade](Sudoku::Cell& cell, const int row, const int column) {
        
        if (cell.GetValue().has_value())
        {
            return true;
        }
        
        std::set<int> possibleValues;
        GetPossibleValues(row, column, possibleValues);
        
        if (possibleValues.size() == 0)
        {
            throw "We fucked up";
        }
        
        if (possibleValues.size() == 1)
        {
            cell.SetValue(*possibleValues.begin());
            anyMovesMade = true;
        }
        
        return true;
    });
    
    return anyMovesMade; // Don't bother continuing if we've done a full loop wihtout making a move
}
