#include "LocalDebugger.hpp"

/* This bot is not designed to actually fix any bugs, just bring them to the user or developer's attention.
Further down the line, it will have features that will affect program execution to catch more hostile program failures. */

LocalDebugger::LocalDebugger()
{
	debug_on = true; // Turn on during construction
};

LocalDebugger::~LocalDebugger()
{
	debug_on = false; // Turn off during destruction
};