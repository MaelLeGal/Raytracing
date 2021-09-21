#ifndef CREATIONIMAGEPPM_H
#define CREATIONIMAGEPPM_H

#pragma once

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void createPPMImage(vector<int> dimensions, vector<vector<vector<int>>> pixels, const char* filename);

#endif // !CREATIONIMAGEPPM_H