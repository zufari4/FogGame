#pragma once
#include "base_control.h"

class Same_line: public Base_control
{
public:
    Same_line(Base_control& parent);
    void Render() override;
};
