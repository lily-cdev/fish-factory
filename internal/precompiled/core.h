#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define LDE_BORDERWIDTH 4
#define LDE_BUFFERSIZE 360
#define LDE_CHANNELS 1
#define LDE_DOCKCAPACITY 750.0
#define LDE_GRIDSIZE 48
#define LDE_HXCAPACITY 1200
#define LDE_HXEFFICIENCY 1200
#define LDE_INFINITY 2147483646
#define LDE_INVALID -1
#define LDE_ITEMCOUNT 11
#define LDE_LARGECAP 150
#define LDE_MACHINES 40
#define LDE_REINFORCEDCAP 30
#define LDE_ROOMTEMP 65
#define LDE_SLIDERS 14
#define LDE_STATICRATE 15
#define LDE_SUFFIXES 5
#define LDE_TILESIZE 40
#define LDE_TURBINECOEFFICIENT 0.15
#define LDE_VESSELSPEED 4
#define LDE_WASTETOX 200
#define LDE_WATERBOILPOINT 211.3

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <corecrt_math_defines.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

extern SDL_ScaleMode Scaling_Quality;

enum Machine {
    Reinforced_Pipe,
    Ram_Pump,
    Incinerator,
    Piezo_Generator,
    Decoration,
    Submarine_Dock,
    Filtration_Plant,
    Bio_Generator,
    Spawning_Pool,
    Distillery,
    Algae_Bed,
    Command_Platform,
    Basic_Scrubber,
    Spawning_Controller,
    Spawning_Output,
    Spawning_Input,
    Electrolytic_Cell,
    Fluid_Mixer,
    Signal_Tower,
    Flowerpot,
    Ammunition_Shelf,
    Cable_Node,
    Geo_Well,
    Large_Pipe,
    Heat_Exchanger,
    Petrified_Wood,
    Basalt_Tile,
    Silicone_Carpet,
    Money_Generator,
    Fluid_Generator,
    R_Intersection,
    L_Intersection,
    Hazard_Strip,
    Condenser_Input,
    Condenser_Transferor,
    Condenser_Heatsink,
    Condenser_Output,
    Turbine_Input,
    Turbine_Impulse,
    Turbine_Output
};

enum Subcategories {
    Modular_Spawning_Pool,
    Flooring,
    Reinforced,
    Large,
    Condenser,
    Turbine
};

enum Prompts {
    P_None = LDE_INVALID,
    P_Help,
    P_Shop,
    P_Daily_Report,
    P_Spawning_Pool,
    P_Transmitter,
    P_Dock,
    P_Exchanger,
    P_Money_Generator,
    P_Fluid_Generator,
    P_Catalog,
    P_Turbine
};

enum Effect {
    Heat
};

enum State {
    Recache,
    Deep_Recache
};

enum Direction {
    Any,
    Left,
    Up,
    Right,
    Down
};

enum Data_Grid {
    Stored_Fluids,
    Fluid_Cap,
    Stored_Power,
    Power_Cap
};

enum Hazard {
    Harmless,
    Mild,
    Medium,
    Severe
};

enum Value {
    Worthless,
    Normal,
    Expensive,
    Exotic
};

enum Commands {
    Execute,
    Get_Data
};

enum Log {
    Changelog,
    Credits,
    Legal
};

enum Tool {
    No_Tool = LDE_INVALID,
    Building,
    Deleting,
    Inspecting,
    Wiring,
    Plumbing
};

enum Error {
	No_Docked_Sub,
	Docked_Sub,
	Empty_Target,
	No_File,
	Low_Value,
	No_Fish,
	Fish_Present,
    Missing_Input,
    Missing_Output,
    Too_Many_Inputs,
    Too_Many_Outputs,
    Too_Many_Controllers,
    Missing_Pool
};

enum Flows {
    F_Either,
    F_In,
    F_Out
};

typedef struct {
    char* Content;
    int Length;
} Char_Array;

typedef struct {
    int X;
    int Y;
} Point;

typedef struct {
    float X;
    float Y;
} Point_f;

typedef struct {
    double X;
    double Y;
} Point_d;

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

SDL_Surface* Load_BMP(const char* Path);
SDL_Texture* SDL_GenerateTexture(SDL_Renderer* Renderer, SDL_PixelFormat Format,
    SDL_TextureAccess Access, int Width, int Height);
SDL_Texture* SDL_GenerateTextureFromSurface(SDL_Renderer* Renderer, SDL_Surface* Surface);
SDL_Texture* IMG_GenerateTexture(SDL_Renderer* Renderer, const char* Path);
int sgn(long double Input);
long double sqr_d(long double Input);
int sqr_i(int Input);
bool evn_i(int Input);