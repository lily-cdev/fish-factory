#pragma once
#include <Core.h>
#include <Preloader.h>
#include <Items.h>

class Wire {
public:
	bool Filled = false;
	int First_X = 0;
	int First_Y = 0;
	int Second_X = 0;
	int Second_Y = 0;
};

class Pipe {
public:
	bool Filled = false;
	int First_X = 0;
	int First_Y = 0;
	int Second_X = 0;
	int Second_Y = 0;
	int X_Offset = 0;
	int Y_Offset = 0;
	int Orienation = 0;
	void Determine_Orientation() {
		if (First_X == Second_X - 1) {
			Orienation = 0;
			X_Offset = 20;
		} else if (First_X == Second_X + 1) {
			Orienation = 2;
			X_Offset = -20;
		} else if (First_Y == Second_Y - 1) {
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