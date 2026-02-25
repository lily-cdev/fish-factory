#pragma once
#include <core.h>
#include <prepping.h>
#include <items.h>

typedef struct {
	bool Filled;
	int X1;
	int Y1;
	int X2;
	int Y2;
	int X_Offset;
	int Y_Offset;
	int Orienation;	
} Bridge;

typedef struct {
	Bridge* Data;
	int Full_Size;
	int Length;
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