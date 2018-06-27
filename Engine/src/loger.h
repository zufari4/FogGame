#pragma once
#include <windows.h>
#define MAX_LOG_SIZE 1024
#define log(x) Loger::Instance().Write_message(x)

class Loger
{
public:
    static Loger& Instance();
    void Write_message(const char* format, ...);
private:
    Loger() {};
    char buffer[MAX_LOG_SIZE];
	SYSTEMTIME cur_time;
};