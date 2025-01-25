//
//  Coordinate.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 25/01/2025.
//

#include "Coordinate.hpp"
#include "Sudoku/Grid.hpp"
#include "Sudoku/SudokuDefines.h"

namespace Sudoku {

    Coordinate::Coordinate(int inX /* = -1 */, int inY /* = -1 */)
    : x(inX)
    , y(inY)
    {
    }

    bool Coordinate::IsValid() const {
        bool xValid = (x >= 0 && x < SUDOKU_NUMBER);
        bool yValid = (y >= 0 && y < SUDOKU_NUMBER);
        
        return (xValid && yValid);
    }

    std::string Coordinate::GetStringValue() {
        return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
    }
}
