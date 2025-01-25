#pragma once 
//
//  Bot.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include <set>
#include <optional>

namespace Sudoku {
    class Grid;
    class Cell;
}

class SudokuBot
{
public:
    SudokuBot(Sudoku::Grid& grid);
    
    void Run();
    
protected:
    virtual bool MainLoop() = 0;
    
    std::optional<int> GetExclusivePossibleValue(const int row, const int column) const;
    void GetPossibleValues(const int row, const int column, std::set<int>& outValues) const;

    void PrintGrid();
    
    Sudoku::Grid* mGrid = nullptr;
};
