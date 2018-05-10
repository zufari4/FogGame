#include "image_button.h"

Image_button::Image_button(unsigned texture, Base_control& parent, float w, float h):
    texture_((ImTextureID)texture),
    Base_control(parent)
{
    SetSize(w, h);
}

void Image_button::Render()
{
    if (ImGui::ImageButton(texture_, size_)) {
        if (callback_click_) {
            callback_click_(*this);
        }
    }
}

void Image_button::Set_texture(unsigned texture)
{
    texture_ = (ImTextureID)texture;
}
