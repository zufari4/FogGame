#include "physic_circle_editable.h"

Physic_circle_editable::Physic_circle_editable():
	Game_object(otPhysicShape),
	Physic_circle(),
	Editable_circle()
{
	Editable_circle::Set_radius(Physic_circle::Get_body_radius());
}

bool Physic_circle_editable::Cursor_enter(const vec2& cursor) const
{
	return Point_in_shape(cursor);
}

void Physic_circle_editable::Set_radius(float val)
{
	Editable_circle::Set_radius(val);
	Physic_circle::Set_body_radius(val);
}

void Physic_circle_editable::Set_pos(const vec2& newpos)
{
	Editable_circle::Set_pos(newpos);
	Physic_circle::Set_body_pos(newpos);
}

void Physic_circle_editable::On_mouse_move(float x, float y)
{
	Editable_circle::On_mouse_move(x, y);
}

void Physic_circle_editable::On_mouse_down(float x, float y, int b)
{
	Editable_circle::On_mouse_down(x, y, b);
}

void Physic_circle_editable::On_mouse_up(float x, float y, int b)
{
	Editable_circle::On_mouse_up(x, y, b);
}

void Physic_circle_editable::Draw() const
{
	// Shape
	if (selected_) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	else  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	Editable_circle::Draw();
	
	// Radius
	glBegin(GL_LINES);
	glVertex2f(pos_.x, pos_.y);
	glVertex2f(vertex_[0].x, vertex_[0].y);
	glEnd();

	// Center
	glPointSize(EDIT_POINT_SIZE / 2.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_POINTS);
	glVertex2f(pos_.x, pos_.y);
	glEnd();

	// Support point
	if (selected_) {
		if (focused_vertex_ == 0) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		else glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glPointSize(EDIT_POINT_SIZE);
		glBegin(GL_POINTS);
		glVertex2f(vertex_[0].x, vertex_[0].y);
		glEnd();
	}
}

void Physic_circle_editable::Update(Uint32)
{
	Editable_circle::Set_pos(body_->GetPosition());
	Editable_circle::Rotate(body_->GetAngle() - Editable_circle::angle_);
}

b2Body* Physic_circle_editable::Get_body() const
{
	return Physic_circle::Get_body();
}

void Physic_circle_editable::On_drag_point(const vec2& pos)
{
	float length = (Editable_circle::pos_ - pos).Length();
	Editable_circle::Set_radius(length);
}

void Physic_circle_editable::On_stop_drag_object()
{
	Physic_circle::Set_body_pos(Circle_shape::pos_);
}

void Physic_circle_editable::On_stop_drag_vertex()
{
	Physic_circle::Set_body_radius(Circle_shape::radius_);
}
