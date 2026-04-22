#pragma once
#include <enums.h>
#define NULLPOINT (Point){ LDE_TERMINATOR, LDE_TERMINATOR }
#define NULLSTRING "NULL"
#define NULLRECIPE (Recipe){ .ID = LDE_TERMINATOR }

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
	SDL_Texture* Icon;
	int Price;
	int Fee;
	int Depth;
	char* Name;
	char* Path;
	bool Quirks[LDE_QUIRKS];
	bool Single_ID;
	Point Size;
	SDL_FRect Rect;
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
} Machine_Data;

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