#include "physic_revolute_joint_editable.h"
#include "engine.h"

Physic_revolute_joint_editable::Physic_revolute_joint_editable():
	Game_object(otPhysicRevoluteJoin),
	Physic_revolute_joint(),
	Editable_circle()
{
	Editable_circle::Set_radius(15.0f * Engine::Get_camera_scale());
}

bool Physic_revolute_joint_editable::Cursor_enter(const vec2& cursor) const
{
	return Editable_circle::Point_in_shape(cursor);
}

void Physic_revolute_joint_editable::On_mouse_move(float x, float y)
{
	Editable_circle::On_mouse_move(x, y);
}

void Physic_revolute_joint_editable::On_mouse_down(float x, float y, int b)
{
	Editable_circle::On_mouse_down(x, y, b);
}

void Physic_revolute_joint_editable::On_mouse_up(float x, float y, int b)
{
	Editable_circle::On_mouse_up(x, y, b);
}

void Physic_revolute_joint_editable::Draw() const
{
	// Shape
	if (selected_) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	else  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	Editable_circle::Draw();
	// Center
	glPointSize(3.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_POINTS);
	glVertex2f(pos_.x, pos_.y);
	glEnd();
}

void Physic_revolute_joint_editable::Update(Uint32)
{
	if (joint_) {
		Editable_circle::Set_pos(joint_->GetAnchorA());
	}
}

void Physic_revolute_joint_editable::Connect_at_point(const vec2& a)
{
	Editable_circle::Set_pos(a);
	Physic_revolute_joint::Connect_at_point(a);
}

void Physic_revolute_joint_editable::Show()
{
	Editable_circle::Show();
}

void Physic_revolute_joint_editable::On_stop_drag_object()
{
	Connect_at_point(Editable_circle::pos_);
}
