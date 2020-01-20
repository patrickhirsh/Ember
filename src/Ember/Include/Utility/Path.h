#pragma once
#include <string.h>
#include <sstream>
#include <vector>

#define EMBER_PATH __FILE__

namespace _EmberUtility
{
	/* Returns the root working directory (Ember) */
	std::string GetRootDirectory();
}