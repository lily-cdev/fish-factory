#pragma once
#include <Core.h>
#include <Preloader.h>

class Legacy_Item_Stack {
public:
	int Identifier = LDE_INVALID;
	std::string Display_Name = "None";
	double Sale_Value = 0;
	double Toxicity = 0;
	double Temperature = LDE_ROOMTEMP;
	double Chemical_Energy = 0;
};

extern Legacy_Item_Stack Legacy_Item_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE];