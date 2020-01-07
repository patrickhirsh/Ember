#pragma once
#include <cstring>
#include <fstream>
#include <iostream>

#if DEBUG
std::ofstream LOGSTREAM("Log.txt", std::ofstream::out);
#define _LOG_META "[" << __FILE__ << "][" << __FUNCTION__ << "][line " << __LINE__ << "]"
#define _LOG(s) do { LOGSTREAM << s; std::cout << s; } while(0)
#define LOG_INFO(m) _LOG("          " << _LOG_META << " : " << m << std::endl)	// Ember log info
#define LOG_WARN(m) _LOG("[WARNING] " << _LOG_META << " : " << m << std::endl)	// Ember log warning
#define LOG_ERROR(m) _LOG(" [ERROR]  " << _LOG_META << " : " << m << std::endl) // Ember log error
#else
#define LOG_INFO(m) do { } while(0)
#define LOG_WARN(m) do { } while(0)
#define LOG_ERROR(m) do { } while(0)
#endif
