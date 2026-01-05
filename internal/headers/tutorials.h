#pragma once
#include <core.h>
#include <prepping.h>

enum Tutorial_Types {
    T_Terminator = LDE_INVALID,
    T_Key,
    T_Button,
};

typedef struct {
	int Type;
	int Hotkey;
	int Selection;
	char Label[128];
	int Item;
	Point Placement_Locations[64];
	bool ID_Override;
	char Context[128];
} Tutorial_Step;

extern Tutorial_Step Tutorial_Stack[256];