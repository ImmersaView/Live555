#include "LiveGlobals.hh"

#include <stdio.h>

const int LIVELOGLVL_CRITICAL = 1;
const int LIVELOGLVL_ERROR = 2;
const int LIVELOGLVL_WARN = 3;
const int LIVELOGLVL_INFO = 5;
const int LIVELOGLVL_MOREINFO = 6;
const int LIVELOGLVL_DIAG = 7;
const int LIVELOGLVL_MOREDIAG = 8;
const int LIVELOGLVL_SUPERDIAG = 9;

static void DefaultLiveLog(int messageLevel, const char* format, va_list args) { /* nop */ }

static LiveLogHook s_liveLogHook = DefaultLiveLog;

void LiveSetLogHook(LiveLogHook func)
{
	s_liveLogHook = func ? func : DefaultLiveLog;
}

void LiveLog(int messageLevel, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	s_liveLogHook(messageLevel, format, args);
	va_end(args);
}
