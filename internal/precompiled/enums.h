#pragma once

enum Machine {
	Reinforced_Pipe,
	Ram_Pump,
	Incinerator,
	RTG,
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
	E_Heat,
	E_Radiation
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

enum Quirks {
	Q_Non_Rotatable,
	Q_Modular,
	Q_Interactable,
	Q_Omnidirectional
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
	T_None = LDE_INVALID,
	T_Building,
	T_Deleting,
	T_Inspecting,
	T_Wiring,
	T_Plumbing
};

enum Issues {
	I_None,
	I_No_Font,
	I_No_Surface_Texture,
	I_No_Texture,
	I_No_Image,
	I_No_SDL3,
	I_No_TTF3,
	I_No_Miniaudio,
	I_No_Window,
	I_No_Renderer,
	I_No_Sound,
	I_Render_Failed
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

typedef enum {
	Ambience1,
	Filtration1,
	Ram1,
	Click
} Sound;

enum Recipe_Types {
	R_None = LDE_INVALID,
	R_Inputs,
	R_Outputs,
	R_Both
};

enum Settings {
	S_Time = 1
};

enum Particles {
	P_Bubble
};

enum Connections {
	C_None,
	C_Omni,
	C_LeftT,
	C_RightT,
	C_UpT,
	C_DownT,
	C_Vertical,
	C_Horizontal,
	C_RightBottom,
	C_BottomLeft,
	C_LeftTop,
	C_TopRight,
	C_Bottom,
	C_Left,
	C_Top,
	C_Right
};