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

extern char Growth_Phases[ktn_fish_phases][32];
extern char Plural_Growth_Phases[ktn_fish_phases][32];
extern int Growth_Weights[ktn_fish_phases];
extern int Pool_Ct;
extern struct Fishlink Fishlinks[16];

void Update_Item(Point Pos, int Identifier, int Temperature);
Item_Ptr Get_Item(const char* Index);
Item_Ptr Get_ID_Item(const int ID);
Fish_Ptr Get_Fish(int Identifier);
void Purge_Items();
float Calculate_Pressure(int Temperature, float Boiling_Point, float H_Vaporisation);
int Get_Phase(Fish_Ptr Fish, int Progress);
void Get_Phase_Name(char* Buffer, int Length, Fish_Ptr Fish, int Progress, int Count);
Point Get_Transformed(Machine_Ptr Machine, Node_Data Node, Point Pos);
bool Process_O_Recipe(Recipe Chosen, Point Pos, Point* Outputs);
bool Process_IO_Recipe(Recipe Chosen, Point Pos, Point* Inputs, Point* Outputs);
bool Extend_Recipe(Recipe Chosen, Point Pos, Point* Outputs);