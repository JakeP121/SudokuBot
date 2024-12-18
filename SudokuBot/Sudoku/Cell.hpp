#pragma once
//
//  Cell.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include <optional>

namespace Sudoku {

    class Cell {

    public:
        static bool IsValidValue(const int value);
        
        void operator=(const int& value);
        bool operator==(const Cell& other) const;

        void SetValue(const int value);
        void ClearValue() { mValue.reset(); }
        
        void SetValid(const bool isValid) { mIsValid = isValid; }
        
        void Print() const;

        const std::optional<int>& GetValue() const { return mValue; }
        std::string GetValueStr() const;
        
    private:
        std::optional<int> mValue;
        bool mIsValid = true;
    };

}
