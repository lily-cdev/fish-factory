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
} Wire;

typedef struct {
	Wire* Data;
	int Full_Size;
	int Length;
} Wires;

typedef struct {
	bool Filled;
	int X1;
	int Y1;
	int X2;
	int Y2;
	int X_Offset;
	int Y_Offset;
	int Orienation;
} Pipe;

typedef struct {
	Pipe* Data;
	int Full_Size;
	int Length;
} Pipes;

extern Pipes Pipes_List;
extern Wires Wires_List;

void Push_Wire(Wire Input);
void Pull_Wire(int Position);
void Clear_Wires();
void Clear_Unconnected_Wires();
void Render_Wires();
void Render_Wire_Nodes();
void Place_Wire();
void Update_Power();
void Push_Pipe(Pipe Input);
void Pull_Pipe(int Position);
void Clear_Pipes();
void Clear_Unconnected_Pipes();
void Render_Pipes();
void Place_Pipe();
void Update_Pipes();
void Orient_Pipe(Pipe* Input);