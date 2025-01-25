//
//  SimpleSudokuBot.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 25/01/2025.
//

#include "SimpleSudokuBot.hpp"
#include "Grid.hpp"
#include "Defines.h"

SimpleSudokuBot::SimpleSudokuBot(Sudoku::Grid& grid)
    : SudokuBot(grid)
{
}

bool SimpleSudokuBot::MainLoop() {
    bool anyMovesMade = false;
    
    mGrid->ForEachCell([&, this](Sudoku::Cell& cell, const int row, const int column) {
        
        if (cell.HasValue())
        {
            return true;
        }
        
        std::set<int> possibleValues;
        GetPossibleValues(row, column, possibleValues);
        if (possibleValues.size() == 1)
        {
            int value = *possibleValues.begin();
            cell.SetValue(value);
            anyMovesMade = true;
            
#if PRINT_MOVES
            printf("Cell %s only has one possible value (%i). Filling that in\n",
                   cell.GetCoordinate().GetStringValue().c_str(),
                   value);
#endif
        }
        
        std::optional<int> exclusivePossibleValue = GetExclusivePossibleValue(row, column);
        if (exclusivePossibleValue.has_value())
        {
            cell.SetValue(*exclusivePossibleValue);
            anyMovesMade = true;
            
#if PRINT_MOVES
            printf("Cell %s has the exclusive possibility of %i in its row/column/section. Filling that in\n",
                   cell.GetCoordinate().GetStringValue().c_str(),
                   *exclusivePossibleValue);
#endif
        }
        
        if (possibleValues.size() == 0)
        {
            mGrid->Print();
            throw "We fucked up";
        }
        
        return true;
    });
    
    return anyMovesMade;
}
