#pragma once

enum Subcategories {
	Modular_Spawning_Pool,
	Flooring,
	Reinforced,
	Large,
	Condenser,
	Turbine
};

enum Prompts {
	P_None = ktn_invalid,
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
	P_Turbine,
	P_Power_Generator
};

enum Effect {
	E_Heat,
	E_Radiation
};

enum State {
	Recache,
	Deep_Recache
};

typedef enum {
	None,
	Left,
	Up,
	Right,
	Down,
	Any
} Dir;

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
	T_None = ktn_invalid,
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
	I_No_SDL3_TTF,
	I_No_Miniaudio,
	I_No_Window,
	I_No_Renderer,
	I_No_Sound,
	I_Render_Failed,
	I_No_Integer,
	I_No_XML_File,
	I_No_Element,
	I_No_Animtype,
	I_No_Powertype,
	I_No_Hazard,
	I_No_Value
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

typedef enum {
	Ambience1,
	Filtration1,
	Ram1,
	Click
} Sound;

enum Recipe_Types {
	R_None = ktn_invalid,
	R_Inputs,
	R_Outputs,
	R_Both
};

enum Settings {
	S_Time = 1,
	S_ParentX = 1,
	S_ParentY = 2
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

typedef enum {
	F_Logo,
	F_Large,
	F_Text,
	F_Halftext,
	F_Subtext,
	F_Microtext,
	F_Terminal
} Font_Index;

typedef enum {
	A_None,
	A_Static,
	A_Rot,
	A_Modular,
	A_Spinner
} Anim_Type;

typedef enum {
	I_None_Vis,
	I_Single,
	I_Rot
} ID_Type;

typedef enum {
	F_None,
	F_In,
	F_Out,
	F_Either
} Flow_Type;