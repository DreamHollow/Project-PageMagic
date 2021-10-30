#ifndef LOCALDEBUGGER_HPP
#define LOCALDEBUGGER_HPP

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