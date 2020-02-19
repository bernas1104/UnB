#ifndef UTIL_H
#define UTIL_H

/* terminal color codes (source: https://stackoverflow.com/a/5947802) */
#ifdef _WIN32
	#define COLOR_RED ""
	#define COLOR_GREEN ""
	#define COLOR_BLUE ""
	#define TEXT_BOLD ""
	#define COLOR_NC ""
#else
	#define COLOR_RED "\033[0;31m"
	#define COLOR_GREEN "\033[0;32m"
	#define COLOR_BLUE "\033[0;34m"
	#define TEXT_BOLD "\033[1m"
	#define COLOR_NC "\033[0m"
#endif
#define AS_COLOR(c, of) c of COLOR_NC

#ifdef _WIN32
    #include <windows.h>
    // source: https://stackoverflow.com/a/3379146
    #define os_sleep(x) Sleep(x*1000) // time is in millisecs
#else
    #include <unistd.h>
    #define os_sleep(x) sleep(x)
#endif

#endif