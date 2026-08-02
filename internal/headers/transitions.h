#pragma once
#include <core.h>
#include <data.h>

typedef struct {
	int Queried_Tab;
	int Frames;
	int Max_Frames;
	int Phase;
	Point Sub_Pos;
	int Sub_Side;
	int Sub_Phase;
	float Sub_Frames;
	float Sub_Offset;
	float Sub_Vertical;
} Proto_Transition;

void Start_Transition(int Tab);
void Force_Opening();
void Render_Closing(bool Clearing);
void Render_Opening();
void Trigger_Ambiance();
void Render_Submarine();
void Render_Transitions();

extern Proto_Transition Transition;