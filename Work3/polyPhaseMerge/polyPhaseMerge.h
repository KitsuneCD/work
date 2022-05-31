#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "FileManager.h"
#include "Fibonacci.h"

void polyPhaseMerge(std::string filename);
void merge(FileManager& manager);
void firstDistrib(std::fstream& file, FileManager& manager);