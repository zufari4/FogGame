#include "loger.h"
#include <stdio.h>
#include <stdarg.h>


Loger& Loger::Instance()
{
    static Loger singlton;
    return singlton;
}

void Loger::Write_message(const char* format, ...)
{
	GetLocalTime(&cur_time);
	va_list arglist;
	va_start(arglist, format);
	vsprintf_s(buffer, format, arglist);
	va_end(arglist);
	printf("%d:%d:%d.%d | %s\n", cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds, buffer);
}
