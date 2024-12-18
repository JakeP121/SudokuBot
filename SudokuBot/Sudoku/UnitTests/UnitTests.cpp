//
//  UnitTests.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include "UnitTests.hpp"
#include "Grid.hpp"
#include <iostream>

namespace UnitTests {

bool Test_All() {
    bool success = true;

    success &= Test_GetAllCellsInRow();
    success &= Test_GetAllCellsInColumn();
    success &= Test_GetAllCellsInSection();
    
    if (!success)
    {
        throw "Unit tests failed";
    }
    return success;
}

bool Test_GetAllCellsInRow() {
    static const std::string testName = "GetAllCellsInRow";
    static const int startingGrid[9][9] =
    {
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 1, 2, 3,  1, 2, 3,  1, 2, 3, },
        
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
    };
    
    // Initialise
    Sudoku::Grid testGrid(startingGrid);
    Sudoku::Cell* rowCells[Sudoku::Grid::GRID_LENGTH];
    testGrid.GetAllCellsInRow(2, rowCells);
    
    // Test
    for (int i = 0; i < Sudoku::Grid::GRID_LENGTH; ++i)
    {
        if (rowCells[i] == nullptr)
        {
            LogError(testName, "Failed to return a cell");
            return false;
        }
        
        if (!rowCells[i]->GetValue().has_value())
        {
            LogError(testName, "Returned a cell from a different row");
            return false;
        }
    }
    
    Log(testName, "Succeeded!");
    return true;
}

bool Test_GetAllCellsInColumn() {
    static const std::string testName = "GetAllCellsInColumn";
    static int startingGrid[9][9] =
    {
        { 0, 0, 1,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 2,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 3,  0, 0, 0,  0, 0, 0, },
        
        { 0, 0, 4,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 5,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 6,  0, 0, 0,  0, 0, 0, },
        
        { 0, 0, 7,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 8,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 9,  0, 0, 0,  0, 0, 0, },
    };
    
    // Initialise
    Sudoku::Grid testGrid(startingGrid);
    Sudoku::Cell* columnCells[Sudoku::Grid::GRID_HEIGHT];
    testGrid.GetAllCellsInColumn(2, columnCells);
    
    // Test
    for (int i = 0; i < Sudoku::Grid::GRID_HEIGHT; ++i)
    {
        if (columnCells[i] == nullptr)
        {
            LogError(testName, "Failed to return a cell");
            return false;
        }
        
        if (!columnCells[i]->GetValue().has_value())
        {
            LogError(testName, "Returned a cell from a different column");
            return false;
        }
    }
    
    Log(testName, "Succeeded!");
    return true;
}

bool Test_GetAllCellsInSection() {
    static const std::string testName = "GetAllCellsInSection";
    
    static int startingGrid[9][9] =
    {
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        
        { 0, 0, 0,  1, 2, 3,  0, 0, 0, },
        { 0, 0, 0,  4, 5, 6,  0, 0, 0, },
        { 0, 0, 0,  7, 8, 9,  0, 0, 0, },
        
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
        { 0, 0, 0,  0, 0, 0,  0, 0, 0, },
    };
    
    // Initialise
    Sudoku::Grid testGrid(startingGrid);
    Sudoku::Cell* sectionCells[Sudoku::Grid::NUM_CELLS_IN_SECTION];
    testGrid.GetAllCellsInSection(5, 5, sectionCells);
    
    // Test
    for (int i = 0; i < Sudoku::Grid::GRID_HEIGHT; ++i)
    {
        if (sectionCells[i] == nullptr)
        {
            LogError(testName, "Failed to return a cell");
            return false;
        }
        
        if (!sectionCells[i]->GetValue().has_value())
        {
            LogError(testName, "Returned a cell from a different section");
            return false;
        }
    }
    
    Log(testName, "Succeeded!");
    return true;
}

void Log(const std::string& testName, const std::string& message) {
    std::cout << "UNIT TEST [" << testName << "] | INFO | " << message << "\n";
}

void LogWarning(const std::string& testName, const std::string& message) {
    std::cout << "UNIT TEST [" << testName << "] | WARN | " << message << "\n";
}

void LogError(const std::string& testName, const std::string& message) {
    std::cout << "UNIT TEST [" << testName << "] | ERROR | " << message << "\n";
}
}
