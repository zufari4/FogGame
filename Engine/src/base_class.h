#pragma once

class Base_class {};


typedef void (Base_class::*Mem_pointer)();

typedef struct
{
    Base_class* obj;
    Mem_pointer func;
} Callback;

