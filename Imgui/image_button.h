#pragma once
#include <functional>
#include "base_control.h"

class Image_button: public Base_control
{
public:
    Image_button(unsigned texture, Base_control& parent, float w, float h);
    void Render() override;
    template<class T> void Set_click(T* const object, void(T::* const func)(Base_control&))
    {
        callback_click_ = std::bind(func, object, std::placeholders::_1);
    }
    void Set_texture(unsigned texture);
protected:
    ImTextureID texture_;
    std::function<void(Base_control&)> callback_click_;
};