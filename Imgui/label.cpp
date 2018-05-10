#include "label.h"
#include <stdarg.h>

Label::Label(Base_control& parent, const char* text):
    Base_control(parent),
    text_(text)
{

}

void Label::Render()
{
    ImGui::Text(text_.c_str());
}

void Label::SetText(const char* fmt, ...)
{
    va_list arglist;
    va_start(arglist, fmt);
    vsprintf_s(buff_, fmt, arglist);
    va_end(arglist);
    text_ = buff_;
}
