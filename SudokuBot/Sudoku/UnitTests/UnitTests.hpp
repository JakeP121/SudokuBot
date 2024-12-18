#pragma once
//
//  UnitTests.hpp
//  SudokuBot
//
//  Created by Jake Passmore on 18/12/2024.
//


#include <stdio.h>
#include <string>

namespace UnitTests {

bool Test_All();
bool Test_GetAllCellsInRow();
bool Test_GetAllCellsInColumn();
bool Test_GetAllCellsInSection();

void Log(const std::string& testName, const std::string& message);
void LogWarning(const std::string& testName, const std::string& message);
void LogError(const std::string& testName, const std::string& message);

}
