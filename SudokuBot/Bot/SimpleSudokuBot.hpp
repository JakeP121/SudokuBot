#pragma once

//
//  SimpleSudokuBot.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 25/01/2025.
//

#include <stdio.h>
#include "SudokuBot.hpp"

class SimpleSudokuBot : public SudokuBot
{
public:
    SimpleSudokuBot(Sudoku::Grid& Grid);
    
protected:
    virtual bool MainLoop() override;
};
