#include "Log.h"

#if DEBUG
std::ofstream LOGSTREAM = std::ofstream("Log.txt", std::ofstream::out);
#endif