#pragma once

#ifndef MESHFILEPARSER_H
#define MESHFILEPARSER_H

#pragma once

#include "pch.h"
#include "Triangle.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

vector<Triangle*> parseOffFile(const char* filename);

#endif // !MESHFILEPARSER_H
