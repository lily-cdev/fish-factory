#pragma once
#include <core.h>
#include <prepping.h>

typedef struct {
	int Queried_Tab;
	int Transition_Frames;
	int Maximum_Transition_Frames;
	int Transition_Phase;
	Point Submarine_Position;
	int Submarine_Side;
	int Submarine_Phase;
	float Submarine_Offset;
	float Submarine_Vertical;
} TRANSITION;

void Start_Transition(int Tab);
void Force_Opening();
void Render_Closing(bool Clearing);
void Render_Opening();
void Trigger_Ambiance();
void Render_Submarine();

extern TRANSITION Transition;