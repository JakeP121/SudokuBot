//
//  main.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <iostream>
#include "Bot/BruteForceSudokuBot.hpp"
#include "Sudoku/Grid.hpp"
#include "UnitTests.hpp"
#include "Utilities/Utilities.hpp"

#include <chrono>
#include <ctime>

int main(int argc, const char * argv[]) {
    
    UnitTests::Test_All();
    
    int startingGrid[9][9] =
    {
        { 0, 0, 0,  3, 5, 7,  4, 1, 9, },
        { 5, 7, 1,  4, 0, 0,  3, 0, 0, },
        { 3, 0, 0,  0, 0, 2,  0, 8, 0, },
        
        { 0, 5, 0,  0, 2, 0,  9, 0, 0, },
        { 2, 0, 0,  7, 0, 1,  0, 3, 0, },
        { 0, 6, 4,  0, 0, 3,  1, 0, 8, },
        
        { 0, 0, 7,  1, 0, 0,  0, 4, 6, },
        { 0, 3, 6,  9, 7, 0,  0, 0, 0, },
        { 0, 0, 0,  2, 6, 4,  0, 0, 3, },
    };
    
    Sudoku::Grid newGrid(startingGrid);
    
    newGrid.Print();
    Utilities::ClearConsole();
    if (!newGrid.Validate())
    {
        throw "Grid isn't valid";
    }
    
    BruteForceSudokuBot bot(newGrid);
    
    auto startTime = std::chrono::system_clock::now();
    bot.Run(true);
    auto endTime = std::chrono::system_clock::now();
    
    if (newGrid.IsFilled() && newGrid.Validate())
    {
        std::chrono::duration<double> elapsed_seconds = endTime-startTime;
        
        std::cout << "Solved in " << elapsed_seconds.count() << "s!\n";
    }
    
    return 0;
}



/*
 
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
 
 
 NYT Hard
 { 0, 0, 7,  0, 8, 6,  0, 0, 0, },
 { 0, 0, 0,  0, 0, 1,  9, 0, 0, },
 { 0, 0, 0,  3, 9, 0,  8, 0, 4, },
 
 { 0, 0, 0,  0, 0, 5,  0, 0, 0, },
 { 0, 2, 0,  0, 0, 3,  5, 9, 6, },
 { 0, 0, 4,  8, 6, 0,  2, 0, 0, },
 
 { 0, 0, 9,  0, 5, 0,  0, 0, 0, },
 { 0, 6, 0,  0, 0, 0,  0, 0, 0, },
 { 2, 0, 0,  0, 0, 4,  7, 3, 0, },
 
 
 */
