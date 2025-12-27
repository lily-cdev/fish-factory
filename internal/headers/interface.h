#pragma once
extern "C" {
	#include <core.h>
	#include <transitions.h>
	#include <data.h>
}
#include <preloader.h>
#include <items.h>
#include <connectables.h>
#include <Data_Handler.h>
#include <ui.h>
#include <Tutorial_Handler.h>

void Close_Prompt();
void Process_Inputs();
void Handle_None(int X, int Y);
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