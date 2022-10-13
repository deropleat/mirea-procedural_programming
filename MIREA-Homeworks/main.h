#pragma once

#define BUFFER(i) Input->getBuffer(i)
#define SENDERROR(data, err) { std::cout << data << " (err-" << err << ")" << SKIPLINE; continue; }
#define INCORRECT(fName) { std::cout << "Incorrect values" << SKIPLINE; fName(); return; }
#define INCORRECTMSG(fName, msg) { std::cout << msg << SKIPLINE; fName(); return; }
#define SKIPLINE std::endl << std::endl
#define M_PI 3.14159265358979323846

#include <iostream>
#include <vector>
#include <functional>
#include <fstream>
#include <string>
#include <cmath>

#include "input.h"
#include "safedata.h"
#include "Homeworks/Homework.h"
#include "Homeworks/CHomework1.h"
#include "Homeworks/CHomework2.h"
#include "Homeworks/CHomework3.h"
#include "Homeworks/CHomework4.h"
#include "Homeworks/CHomework5.h"

template<typename t>
t clamp(t value, t min, t max)
{
	if (value > max) return max;
	else if (value < min) return min;
	else return value;
}