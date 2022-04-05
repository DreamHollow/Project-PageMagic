#include <cstdint>
#include "Page.hpp"

/* System warns user against using specific bit configurations that won't work with SFML */
#if INTPTR_MAX == INT64_MAX

#pragma message ("Configured for 64-bit system.")
#elif INTPTR_MAX == INT32_MAX
#error "This program is using 64-bit binaries. 32-bit binaries are not compatible.""
#else
#error Unknown pointer size or missing macros!
#endif

int main()
{
	// Empty for now.

	// Window closes without error.
	system("pause"); // So the user can actually read the goodbye screen.
	return 0;
};