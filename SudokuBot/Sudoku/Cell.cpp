//
//  Cell.cpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include "Cell.hpp"
#include <iostream>
#include <string>

namespace Sudoku {

    Cell::Cell(const int row, const int column, const int value /* = 0 */)
        : mRow(row)
        , mColumn(column)
    {
        if (IsValidValue(value))
        {
            mValue = value;
            mIsDefault = true;
        }
    }
    
    bool Cell::IsValidValue(const int value) {
        return (value > 0 && value <= 9);
    }

    void Cell::operator=(const int& value) {
        SetValue(value);
        SetValid(true);
    }

    bool Cell::operator==(const Cell& other) const {
        return (mValue == other.mValue);
    }

    void Cell::SetValue(const int value) {
        if (!IsValidValue(value))
        {
            throw "Invalid value";
        }
        
        mValue = value;
    }

    void Cell::ClearValue()
    {
        if (!mIsDefault)
        {
            mValue.reset();
        }
    }

    void Cell::Print() const {
        if (mIsValid)
        {
            std::cout << "[" << GetValueStr() << "]";
        }
        else
        {
            std::cout << "{" << GetValueStr() << "}";
        }
    }

    std::string Cell::GetValueStr() const {
        return (mValue.has_value()) ? std::to_string(*mValue) : " ";
    }
}
