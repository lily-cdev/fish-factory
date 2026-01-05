#pragma once
extern "C" {
	#include <core.h>
	#include <transitions.h>
	#include <data.h>
	#include <interface.h>
	#include <connectables.h>
	#include <items.h>
}
#include <Legacy_Preloader.hpp>
#include <Legacy_UI.hpp>
#include <Legacy_Tutorials.hpp>

void Close_Prompt();
void Process_Inputs();
void Handle_Help(int X, int Y);
void Handle_Shop(int X, int Y);
void Handle_Daily_Report(int X, int Y);
void Handle_Spawning_Pool(int X, int Y);
void Handle_Transmitter(int X, int Y);
void Handle_Dock(int X, int Y);
void Handle_Exchanger(int X, int Y);
void Handle_Money_Generator(int X, int Y);
void Handle_Fluid_Generator(int X, int Y);
void Handle_Catalog(int X, int Y);
void Handle_Turbine(int X, int Y);