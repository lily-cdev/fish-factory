#pragma once
extern "C" {
	#include <core.h>
	#include <prepping.h>
}
#include <clib.hpp>

struct OLD_TEMPORARY {
public:
	std::vector<double> FPS_Query = { };
	std::vector<SDL_FRect> Query = { };
	std::vector<int> ID_Query = { };
	std::vector<SDL_Color> Color_Query = { };
};

struct OLD_INTERFACE {
public:
	std::vector<std::string> Terminal_Logs = { };
	std::vector<int> Default_Positions = { 0 };
	std::string Terminal_Entry;
};

extern OLD_TEMPORARY Temporary_L;
extern OLD_INTERFACE Interface_L;