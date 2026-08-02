#pragma once
#include <core.h>
#include <prepping.h>
#include <items.h>

typedef struct {
	bool Filled;
	int8_t X1;
	int8_t Y1;
	int8_t X2;
	int8_t Y2;
	int16_t X_Offset;
	int16_t Y_Offset;
	int8_t Orienation;
} Bridge;

typedef struct {
	Bridge* Data;
	int64_t Full_Size;
	int64_t Length;
} Bridges;

extern Bridges Pipes;
extern Bridges Wires;
extern Bridges Links;

void Push_Bridge(Bridges* List, Bridge Input);
void Pull_Bridge(Bridges* List, int Position);
void Clear_Bridges(Bridges* List);
void Clear_Unconnected_Bridges(Bridges* List);
void Render_Wires();
void Render_Wire_Nodes();
void Place_Wire();
void Update_Power();
void Render_Pipes();
void Place_Pipe();
void Update_Pipes();
void Orient_Pipe(Bridge* Input);