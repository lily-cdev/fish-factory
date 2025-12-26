#pragma once
extern "C" {
	#include <core.h>
}
#include <preloader.h>
#include <ui.h>

class Tutorial_Step {
public:
	int Type = 0;
	int Hotkey = 0;
	int Selection = 0;
	std::string Label = "";
	int Item = 0;
	std::vector<std::vector<int>> Placement_Locations = { };
	bool ID_Override = false;
	std::string Context = "";
};

void Process_Tutorial(int Input);

void Render_Tutorial();

extern std::vector<Tutorial_Step> Tutorial_Stack;