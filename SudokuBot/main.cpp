//
//  main.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <iostream>
#include "Sudoku/Grid.hpp"

int main(int argc, const char * argv[]) {
    
    int startingGrid[9][9] =
    {
        { 1, 2, 3,  0, 0, 0,  0, 0, 0, },
        { 4, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 5, 0, 0,  4, 0, 0,  0, 0, 0, },
        
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
    };
    
    Sudoku::Grid newGrid(startingGrid);
    
    newGrid.Validate();
    newGrid.Print();
    
    return 0;
}
