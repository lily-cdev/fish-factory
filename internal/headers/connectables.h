#pragma once
extern "C" {
	#include <core.h>
}
#include <preloader.h>
#include <items.h>
#include <clib.hpp>

class Wire {
public:
	bool Filled = false;
	int X1 = 0;
	int Y1 = 0;
	int X2 = 0;
	int Y2 = 0;
};

class Pipe {
public:
	bool Filled = false;
	int X1 = 0;
	int Y1 = 0;
	int X2 = 0;
	int Y2 = 0;
	int X_Offset = 0;
	int Y_Offset = 0;
	int Orienation = 0;
	void Determine_Orientation() {
		if (X1 == X2 - 1) {
			Orienation = 0;
			X_Offset = 20;
		} else if (X1 == X2 + 1) {
			Orienation = 2;
			X_Offset = -20;
		} else if (Y1 == Y2 - 1) {
			Orienation = 1;
			Y_Offset = 20;
		} else {
			Orienation = 3;
			Y_Offset = -20;
		}
	}
};

extern std::vector<Wire> Wires_List;
extern std::vector<Pipe> Pipes_List;

void Clear_Wires();
void Clear_Pipes();
void Clear_Unconnected_Wires();
void Clear_Unconnected_Pipes();
void Render_Wires();
void Render_Pipes();
void Render_Wire_Nodes();
void Place_Wire();
void Place_Pipe();
void Update_Power();
void Update_Pipes();