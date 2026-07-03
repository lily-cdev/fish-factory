#pragma once
#include <enums.h>
#define ktn_null_point (Point){ ktn_terminator, ktn_terminator }
#define ktn_null_string "_null"
#define ktn_null_recipe (Recipe){ .ID = ktn_terminator }

typedef struct {
	int Length;
	char** Data;
} String2;

typedef struct {
	int X;
	int Y;
} Point;

typedef struct {
	int Length;
	Point* Data;
} Node;

typedef struct {
	int Full_Size;
	int Length;
	Point* Data;
} Node_d;

typedef struct {
	char Stored[512];
	SDL_Texture* Data;
	SDL_FRect Bounds;
	SDL_Color Color;
} Texture_Supply;

typedef struct {
	float X;
	float Y;
} Point_f;

typedef struct {
	int Length;
	SDL_Texture** Data;
} Texture_Array;

typedef struct {
	int Length;
	Texture_Array* Data;
} Texture2_Array;

typedef struct {
	int Length;
	Texture2_Array* Data;
} Texture3_Array;

typedef struct {
	int Length;
	SDL_FRect* Data;
} Rect_Array;

typedef struct {
	int Length;
	Rect_Array* Data;
} Rect2_Array;

typedef struct {
	int Length;
	Rect2_Array* Data;
} Rect3_Array;

typedef struct {
	int Parts;
} Modular_Data;

typedef struct {
	int Speed;
} Spinner_Data;

typedef struct {
	Point Pos;
	Point Size;
} Gauged_Data;

typedef struct {
	Point Pos;
	Flow_Type Flow;
	Dir Connection;
	int Cap;
} Node_Data;

typedef struct Category_Data {
	char* Name;
	char* Index;
	struct Category_Data* Parent;
} Category_Data;

typedef Category_Data* Category_Ptr;
typedef Category_Data* Subcategory_Ptr;

typedef struct {
	union {
		Category_Ptr Parent;
		Subcategory_Ptr Subparent;
	};
	bool Subcategory;
} Category_Bundle;

typedef struct {
	SDL_Texture* Icon;
	int Price;
	int Fee;
	int Depth;
	char* Name;
	char* Desc;
	char* Index;
	Category_Ptr Parent;
	char* Path;
	bool Quirks[ktn_quirks];
	Point Size;
	SDL_FRect Rect;
	ID_Type Visual_Type;
	Anim_Type Animation_Type;
	Flow_Type Power_Type;
	int Power_Capacity;
	Point Anchor;
	union {
		SDL_Texture* Texture1;
		Texture_Array Texture2;
		Texture2_Array Texture3;
	};
	union {
		Modular_Data Mod_Data;
		Spinner_Data Spin_Data;
		Gauged_Data Gauge_Data;
	};
	union {
		int Visual_ID1;
		int Visual_ID4[4];
	};
	int Input_Ct;
	Node_Data* Inputs;
	int Output_Ct;
	Node_Data* Outputs;
	int Neutral_Ct;
	Node_Data* Neutrals;
	bool Heating;
	bool Irradiating;
	bool Command;
	bool Has_Audio;
	ma_sound Run;
} Machine_Data;

typedef Machine_Data* Machine_Ptr;

typedef struct {
	char* Name;
	char* Index;
	char* Path;
	bool Coolant;
	SDL_Texture* Icon;
	int ID;
	enum Hazard Danger;
	enum Value Worth;
	int Price;
	int Chem_Energy;
	int Boil_Pt;
	int V_Enthalpy;
	float Nutrition;
} Item_Data;

typedef Item_Data* Item_Ptr;

typedef struct {
	char* Name;
	int Identifier;
	Item_Ptr Item;
	int Max_Growth;
	float Size;
	float Food_Consumption;
	float Fragility;
} Fish_Data;

typedef Fish_Data* Fish_Ptr;

typedef struct {
	char* Name;
	char* Path;
	SDL_Texture* Icon;
	int ID;
	float Rate;
	float Consumption;
	float Space;
} Gene_Data;

typedef Gene_Data* Gene_Ptr;

typedef struct {
	int Type;
	bool Shuffling_Barred;
	bool Voiding_Excess;
	int Time;
	int Power;
	Machine_Ptr Machine;
	Item_Ptr Input_Items[16];
	float Input_Counts[16];
	Item_Ptr Output_Items[16];
	float Output_Counts[16];
} Recipe;

typedef union {
	void* Pointer;
	int Integer;
	Point Pos;
} Parameter;

typedef struct {
	void (*Carrier)(Parameter Param, Parameter Param2);
	Parameter Param;
	Parameter Param2;
} UI_Link;