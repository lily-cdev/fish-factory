#pragma once
#include <core.h>
#include <prepping.h>

struct Subfish {
    float Damage;
    int Growth;
};

struct Fishlink {
    bool Allocated;
    int Fish_Ct;
    int Size;
    float Nutrition;
    struct Subfish* Fish;
    Fish_Ptr Type;
    bool Autofill;
};

struct Docklink {
    bool Allocated;
    char Items[2][64];
};

extern char Growth_Phases[ktn_fish_phases][32];
extern char Plural_Growth_Phases[ktn_fish_phases][32];
extern int Growth_Weights[ktn_fish_phases];
extern int Pool_Ct;
extern int Dock_Ct;
extern struct Fishlink Fishlinks[ktn_fishlinks];
extern struct Docklink Docklinks[ktn_docklinks];

void Update_Item(Point Pos, char Identifier[64], int Temperature);
Item_Ptr Get_Item(const char* Index);
Fish_Ptr Get_Fish(int Identifier);
void Purge_Items();
int Get_Phase(Fish_Ptr Fish, int Progress);
void Get_Phase_Name(char* Buffer, int Length, Fish_Ptr Fish, int Progress, int Count);
Point Get_Transformed(Node_Data Node, Point Pos);
bool Process_O_Recipe(Recipe Chosen, Point Pos, Point* Outputs);
bool Process_IO_Recipe(Recipe Chosen, Point Pos, Point* Inputs, Point* Outputs);
bool Extend_Recipe(Recipe Chosen, Point Pos, Point* Outputs);