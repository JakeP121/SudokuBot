#pragma once
//
//  Coordinate.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 25/01/2025.
//

#include <string>

namespace Sudoku {
    struct Coordinate {
        
        int x = -1;
        int y = -1;
        
        Coordinate(int x = -1, int y = -1);
        
        bool IsValid() const;
        std::string GetStringValue();
    };
}
