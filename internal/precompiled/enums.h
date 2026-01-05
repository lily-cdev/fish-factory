#pragma once

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
    E_Heat
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