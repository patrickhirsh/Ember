#include "Path.h"

namespace _EmberUtility
{
	std::string GetRootDirectory()
	{
		std::string root;
		std::stringstream path(EMBER_PATH); 
		std::string token;
		std::vector<std::string> tokens;
		
		while(std::getline(path, token, '/'))  
			tokens.push_back(token); 
		
		for (int i = 0; i < ((int)tokens.size() - 5); i++)  
			root += tokens[i] + "/";

		return root;
	}
}