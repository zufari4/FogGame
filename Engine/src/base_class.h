#pragma once

class BaseClass {};


typedef void (BaseClass::*MemPointer)();

typedef struct
{
    BaseClass* obj;
    MemPointer func;
} ClassCallback;

