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
	Flow_Type Flow;
	Dir Connection;
	int Cap;
} Node_Data;

typedef struct {
	SDL_Texture* Icon;
	int Price;
	int Fee;
	int Depth;
	char* Name;
	char* Desc;
	char* Index;
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
} Machine_Data;

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

typedef Machine_Data* Machine_Ptr;
typedef Item_Data* Item_Ptr;

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

typedef struct {
	bool Allocated;
	char Key;
	Point Bounds;
	Point Bearing;
	int Advance;
	SDL_Texture* Data;
} Glyph;