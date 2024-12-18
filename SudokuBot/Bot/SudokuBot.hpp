#pragma once 
//
//  Bot.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include <set>

namespace Sudoku {
    class Grid;
    class Cell;
}

class SudokuBot
{
public:
    SudokuBot(Sudoku::Grid& grid);
    
    void Run(const bool printEachMove);
    
protected:
    virtual bool MainLoop() = 0;
    
    void GetPossibleValues(const int row, const int column, std::set<int>& outValues) const;
    
    Sudoku::Grid* mGrid = nullptr;
    bool mPrintEachMove = false;
};
