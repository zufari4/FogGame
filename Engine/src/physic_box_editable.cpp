#include "physic_box_editable.h"

Physic_box_editable::Physic_box_editable():
	Game_object(otPhysicShape),
	Physic_box(),
	Editable_box(),
	sqared_(true)
{
	Editable_box::Set_rect(Physic_box::min_vertex_, Physic_box::max_vertex_);
}

bool Physic_box_editable::Cursor_enter(const vec2& cursor) const
{
	return Point_in_shape(cursor);
}

void Physic_box_editable::Set_pos(const vec2& newpos)
{
	Editable_box::Set_pos(newpos);
	Physic_box::Set_body_pos(newpos);
}

void Physic_box_editable::On_mouse_move(float x, float y)
{
	Editable_box::On_mouse_move(x, y);
}

void Physic_box_editable::On_mouse_down(float x, float y, int b)
{
	Editable_box::On_mouse_down(x, y, b);
}

void Physic_box_editable::On_mouse_up(float x, float y, int b)
{
	Editable_box::On_mouse_up(x, y, b);
}

void Physic_box_editable::Draw() const
{
	// Shape
	if (selected_) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	else  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	Editable_box::Draw();

	// Center
	glPointSize(EDIT_POINT_SIZE / 2.0f);
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	glBegin(GL_POINTS);
	glVertex2f(pos_.x, pos_.y);
	glEnd();

	// Support point
	if (selected_) {
		glPointSize(EDIT_POINT_SIZE);
		glBegin(GL_POINTS);

		if (focused_vertex_ == 0) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		else glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glVertex2f(vertex_[0].x, vertex_[0].y);

		if (focused_vertex_ == 1) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		else glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glVertex2f(vertex_[1].x, vertex_[1].y);

		if (focused_vertex_ == 2) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		else glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glVertex2f(vertex_[2].x, vertex_[2].y);

		if (focused_vertex_ == 3) glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
		else glColor4f(0.0f, 1.0f, 0.0f, 0.5f);
		glVertex2f(vertex_[3].x, vertex_[3].y);

		glEnd();
	}
}

void Physic_box_editable::Update(Uint32)
{
	pos_ = body_->GetPosition();
    angle_ = body_->GetAngle();
    for (int i = 0; i < 4; i++) {
        vertex_[i] = body_->GetWorldPoint(box_shape_->GetVertex(i));
    }
}

b2Body* Physic_box_editable::Get_body() const
{
	return Physic_box::Get_body();
}

void Physic_box_editable::On_drag_point(const vec2& pos)
{
	switch (focused_vertex_)
	{
	case 0: vertex_[0] = pos; if (sqared_) { vertex_[3].x = vertex_[0].x; vertex_[1].y = vertex_[0].y; } break;
	case 1: vertex_[1] = pos; if (sqared_) { vertex_[2].x = vertex_[1].x; vertex_[0].y = vertex_[1].y; } break;
	case 2: vertex_[2] = pos; if (sqared_) { vertex_[1].x = vertex_[2].x; vertex_[3].y = vertex_[2].y; } break;
	case 3: vertex_[3] = pos; if (sqared_) { vertex_[0].x = vertex_[3].x; vertex_[2].y = vertex_[3].y; } break;
	}
	Editable_box::Centering_pos();
}

void Physic_box_editable::On_stop_drag_object()
{
	Physic_box::Set_body_pos(Editable_box::pos_);
}

void Physic_box_editable::On_stop_drag_vertex()
{
	Physic_box::Set_body_pos(Editable_box::pos_);
	Physic_box::Set_body_rect(vertex_[0], vertex_[2]);
}
