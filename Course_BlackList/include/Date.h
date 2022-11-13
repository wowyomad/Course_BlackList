#pragma once

#include "console_manip.h"

bool str_to_tm(const char* str, const char* pattern, tm* datetime);
bool str_to_tm_leaps(const char* str, const char* pattern, tm* datetime);
