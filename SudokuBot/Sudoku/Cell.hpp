#pragma once
//
//  Cell.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include <optional>

#include "Coordinate.hpp"

namespace Sudoku {

    class Cell
    {
    public:
        static bool IsValidValue(const int value);
        Cell() = default;
        Cell(const int row, const int column, const int value = 0);
        
        void operator=(const int& value);
        bool operator==(const Cell& other) const;
        
        int GetRow() const { return mRow; }
        int GetColumn() const { return mColumn; }
        Coordinate GetCoordinate() const { return Coordinate(mRow, mColumn); }

        void SetValue(const int value);
        void ClearValue();
        bool HasValue() const { return mValue.has_value(); }
        
        void SetValid(const bool isValid) { mIsValid = isValid; }
        
        void Print() const;

        const std::optional<int>& GetValue() const { return mValue; }
        std::string GetValueStr() const;
        
    private:
        int mRow = 0;
        int mColumn = 0;
        
        std::optional<int> mValue;
        bool mIsValid = true;
        bool mIsDefault = false;
    };

}
