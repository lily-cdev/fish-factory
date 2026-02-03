#pragma once
#include <core.h>
#include <prepping.h>

typedef struct {
	int Queried_Tab;
	int Frames;
	int Max_Frames;
	int Phase;
	Point Sub_Pos;
	int Sub_Side;
	int Sub_Phase;
	float Sub_Offset;
	float Sub_Vertical;
} TRANSITION;

void Start_Transition(int Tab);
void Force_Opening();
void Render_Closing(bool Clearing);
void Render_Opening();
void Trigger_Ambiance();
void Render_Submarine();
void Render_Transitions();

extern TRANSITION Transition;