#pragma once

//
//  BruteForceSudokuBot.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//

#include <stdio.h>
#include "SudokuBot.hpp"

class BruteForceSudokuBot : public SudokuBot {
public:
    BruteForceSudokuBot(Sudoku::Grid& grid);
    
    virtual bool MainLoop() override;
};
