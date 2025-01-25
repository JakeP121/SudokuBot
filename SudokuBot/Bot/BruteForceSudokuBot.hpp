#pragma once

//
//  BruteForceSudokuBot.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include <stack>

#include "SudokuBot.hpp"
#include "Grid.hpp"
#include "Sudoku/Coordinate.hpp"

struct BruteForceMove {
    
    BruteForceMove() = default;
    BruteForceMove(const Sudoku::Coordinate& coord, const std::set<int>& possibleValues, const int& chosenValue);
    
    Sudoku::Coordinate mCoord;
    
    std::set<int> mPossibleValues;
    int mChosenValue = 0;
};

class BruteForceSudokuBot : public SudokuBot {
public:
    BruteForceSudokuBot(Sudoku::Grid& grid);
    
    virtual bool MainLoop() override;
    
protected:
    Sudoku::Coordinate FindEmptyCell() const;
    
    bool WeFuckedUp();
    
    
    void CrosscheckRow(Sudoku::Cell& cell, const int row, std::set<int>& possibleValues);
    void CrosscheckColumn(Sudoku::Cell& cell, const int column, std::set<int>& possibleValues);
    void CrosscheckSection(Sudoku::Cell& cell, const int row, const int column, std::set<int>& possibleValues);
    
    bool TryPossibleValues(const int row, const int column, std::set<int> (&allPossibleValues)[Sudoku::Grid::GRID_LENGTH][Sudoku::Grid::GRID_HEIGHT]);
    bool TryPossibleValues(Sudoku::Cell& cell, const int row, const int column, std::set<int>& possibleValues);
    
private:
    std::stack<BruteForceMove> mHistory;
};
