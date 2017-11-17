#ifndef _LIVE_GLOBALS_HH
#define _LIVE_GLOBALS_HH

#include <stdarg.h>

#if defined _MSC_VER && defined LIVE_EXPORTS
	#define LIVE_API __declspec(dllexport)
#elif defined _MSC_VER && defined LIVE_DLL
	#define LIVE_API __declspec(dllimport)
#else
	#define LIVE_API
#endif

// Note: FD_SETSIZE defaults to 64 on Windows
//   When we have lots of connections at once, this results in certain sockets simply not being handled by select()!
//   It must be defined BEFORE including winsock2.h
// Note: This MUST be defined here (not in NetCommon.h where it would fit better)
//   because some files use fd_set but do not include NetCommon.h (eg. BasicUsageEnvironment)!
//   This results in our own NetworkMedia::ThreadedTaskScheduler thinking sizeof(BasicUsageEnvironment) uses FD_SETSIZE 64 (the default),
//   when it does not; this causes memory corruption / causes 'this' to be incorrect when calling one of its ThreadBase virtual functions

#ifdef _WIN32
#define FD_SETSIZE 1024
#endif

// Values for messageLevel in log functions
extern const int LIVELOGLVL_CRITICAL;
extern const int LIVELOGLVL_ERROR;
extern const int LIVELOGLVL_WARN;
extern const int LIVELOGLVL_INFO;
extern const int LIVELOGLVL_MOREINFO;
extern const int LIVELOGLVL_DIAG;
extern const int LIVELOGLVL_MOREDIAG;
extern const int LIVELOGLVL_SUPERDIAG;

typedef void (*LiveLogHook)(int messageLevel, const char* format, va_list args);

void LIVE_API LiveSetLogHook(LiveLogHook func);
void LiveLog(int messageLevel, const char* format, ...);  // Not LIVE_API since this is for internal use only

// Logging helpers
#define LIVELOG_CRITICAL(fmt, ...) LiveLog(LIVELOGLVL_CRITICAL, fmt"\n", __VA_ARGS__)
#define LIVELOG_ERROR(fmt, ...) LiveLog(LIVELOGLVL_ERROR, fmt"\n", __VA_ARGS__)
#define LIVELOG_WARN(fmt, ...) LiveLog(LIVELOGLVL_WARN, fmt"\n", __VA_ARGS__)

// Enables verbose logging in Release builds
// Note: Not to be used in public releases!
//#define LIVE_ENABLE_VERBOSE_LOGGING

#if defined(_DEBUG) || defined(LIVE_ENABLE_VERBOSE_LOGGING)
// Only allow detailed logs in builds that are not being released to public
#define LIVELOG_INFO(fmt, ...) LiveLog(LIVELOGLVL_INFO, fmt"\n", __VA_ARGS__)
#define LIVELOG_MOREINFO(fmt, ...) LiveLog(LIVELOGLVL_MOREINFO, fmt"\n", __VA_ARGS__)
#define LIVELOG_DIAG(fmt, ...) LiveLog(LIVELOGLVL_DIAG, fmt"\n", __VA_ARGS__)
#define LIVELOG_MOREDIAG(fmt, ...) LiveLog(LIVELOGLVL_MOREDIAG, fmt"\n", __VA_ARGS__)
#define LIVELOG_SUPERDIAG(fmt, ...) LiveLog(LIVELOGLVL_SUPERDIAG, fmt"\n", __VA_ARGS__)
#else
#define LIVELOG_INFO(fmt, ...)
#define LIVELOG_MOREINFO(fmt, ...)
#define LIVELOG_DIAG(fmt, ...)
#define LIVELOG_MOREDIAG(fmt, ...)
#define LIVELOG_SUPERDIAG(fmt, ...)
#endif


#endif
