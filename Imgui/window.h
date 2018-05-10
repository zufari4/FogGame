#pragma once
#include <string>
#include "base_control.h"

class Window: public Base_control
{
public:
    Window(const std::string& name, float x, float y, float w, float h, int flags);
    void Render() override;
protected:
    std::string name_;
    int flags_;
};
