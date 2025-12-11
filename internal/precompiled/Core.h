#pragma once
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
#define LDE_REINFORCEDCAP 30
#define LDE_ROOMTEMP 65
#define LDE_STATICRATE 24.0
#define LDE_VESSELSPEED 4
#define LDE_WASTETOX 200
#define LDE_WATERBOILPOINT 211.3

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <corecrt_math_defines.h>

#include <json.hpp>
#include <Wrapper.hpp>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

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

enum Effect {
    Heat
};

enum State {
    Recache,
    Deep_Recache
};

enum Direction {
    Left = 1,
    Up = 2,
    Right = 3,
    Down = 4
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

typedef std::chrono::steady_clock Clock;

typedef struct {
    int X;
    int Y;
} Point;

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

inline int sgn(long double Input) {
    if (Input > 0) {
        return 1;
    } else if (Input < 0) {
        return -1;
    }
    return 0;
}

inline long double sqr_d(long double Input) {
    return Input * Input;
}

inline int sqr_i(int Input) {
    return Input * Input;
}

inline bool evn_i(int Input) {
    return static_cast<int>(Input & 1) == 0;
}