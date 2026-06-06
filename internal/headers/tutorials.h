#pragma once
#include <core.h>
#include <prepping.h>
#include <connectables.h>
#include <rendering.h>

enum Tutorial_Types {
    T_Terminator = ktn_invalid,
    T_Key,
    T_Button,
	T_Placement
};

typedef struct {
	int Type;
	int Hotkey;
	int Selection;
	char Label[128];
	int Item;
	Point Placement_Locations[64];
	Machine_Ptr ID_Override;
	char Context[128];
} Tutorial_Step;

void Process_Tutorial(int Input);
void Render_Tutorial();

extern Tutorial_Step Tutorial_Stack[256];