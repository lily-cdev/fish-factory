#pragma once
#include <core.h>
#include <prepping.h>

typedef struct {
    uint64_t Funds;
    uint16_t Time;
    uint8_t Day;
    uint8_t CMD_Placed;
} Package0;

void Get_Filesizes();
void Preclear_Temporaries();
void Render_Loadscreen();
bool Save_Data(int Slot);
bool Load_Data(int Slot);