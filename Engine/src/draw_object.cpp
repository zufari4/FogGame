#include "draw_object.h"

Draw_object::Draw_object():
	Base_class(),
	selected_(false),
	visible_(false),
	pos_(b2Vec2_zero),
	angle_(0.0f)
{

}

void Draw_object::Show()
{
	visible_ = true;
}

void Draw_object::Set_pos(const vec2& newpos)
{
	pos_ = newpos;
}

const vec2& Draw_object::Get_pos() const
{
	return pos_;
}

float Draw_object::Get_angle() const
{
	return angle_;
}

void Draw_object::Move(const vec2& delta)
{
	pos_ += delta;
}

void Draw_object::Set_selected(bool value)
{
	selected_ = value;
}

bool Draw_object::Is_visible() const
{
	return visible_;
}

void Draw_object::Rotate(float delta_rad)
{
	angle_ += delta_rad;
}

void Draw_object::Hide()
{
	visible_ = false;
}

bool Draw_object::Has_edit() const
{
	return (selected_ && visible_);
}


