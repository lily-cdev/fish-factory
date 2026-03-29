#pragma once
#include <core.h>
#include <prepping.h>
#include <transitions.h>
#include <data.h>
#include <ui.h>
#include <tutorials.h>
#include <connectables.h>
#include <items.h>

void Close_Prompt();
void Process_Inputs();
void Handle_None(Point Pos);
void Handle_Help(Point Pos);
void Handle_Spawning_Pool(Point Pos);
void Handle_Transmitter(Point Pos);
void Handle_Dock(Point Pos);
void Handle_Exchanger(Point Pos);
void Handle_Money_Generator(Point Pos);
void Handle_Fluid_Generator(Point Pos);
void Handle_Catalog(Point Pos);
void Handle_Turbine(Point Pos);
void Handle_Power_Generator(Point Pos);