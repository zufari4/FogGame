#pragma once
#include "base_control.h"

class Label: public Base_control
{
public:
    Label(Base_control& parent, const char* text = "");
    void Render() override;
    void SetText(const char* fmt, ...);
protected:
    std::string text_;
    char buff_[4096];
};

