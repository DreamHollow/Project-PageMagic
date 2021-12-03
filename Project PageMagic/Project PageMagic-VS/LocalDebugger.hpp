#ifndef LOCALDEBUGGER_HPP
#define LOCALDEBUGGER_HPP

// This is a hideous name for a debugger class but I didn't want it getting confused with other debuggers

class LocalDebugger
{
public:
	LocalDebugger();
	virtual ~LocalDebugger();

	// Functions
	const bool is_debugging() const { return debug_on; }; // Having this as const has helped reduce incorrect syntax

private:
	// Variables
	bool debug_on;
};

#endif