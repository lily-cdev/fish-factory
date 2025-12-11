#pragma once
#include <Core.h>

#include <Preloader.h>

struct Transition {
public:
	int Queried_Tab = 0;
	int Transition_Frames = 0;
	int Maximum_Transition_Frames = 0;
	int Transition_Phase = LDE_INVALID;
};

void Start_Transition(int Tab);

void Force_Opening();

void Render_Closing(bool Clearing = false);

void Render_Opening();

void Trigger_Ambiance();

void Render_Submarine();

extern Transition Transition_Access;