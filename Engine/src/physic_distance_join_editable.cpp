#include "physic_distance_join_editable.h"
#include "engine.h"

Physic_distance_join_editable::Physic_distance_join_editable():
	Game_object(otPhysicDistanceJoin),
	Physic_distance_join(),
	Editable_line_segment()
{
	Connect_at_points(vec2_zero, Engine::Scale_vec2(200.0f, 0.0f));
}

bool Physic_distance_join_editable::Cursor_enter(const vec2& cursor) const
{
	return Editable_line_segment::Point_in_shape(cursor);
}

void Physic_distance_join_editable::On_mouse_move(float x, float y)
{
	Editable_line_segment::On_mouse_move(x, y);
}

void Physic_distance_join_editable::On_mouse_down(float x, float y, int b)
{
	Editable_line_segment::On_mouse_down(x, y, b);
}

void Physic_distance_join_editable::On_mouse_up(float x, float y, int b)
{
	Editable_line_segment::On_mouse_up(x, y, b);
}

void Physic_distance_join_editable::Draw() const
{
	// Shape
	if (selected_) glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	else  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	Editable_line_segment::Draw();

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

		glEnd();
	}
}

void Physic_distance_join_editable::Update(Uint32)
{
	if (joint_) {
		Editable_line_segment::Set_line(joint_->GetAnchorA(), joint_->GetAnchorB());
	}
}

void Physic_distance_join_editable::Connect_at_points(const vec2& a, const vec2& b)
{
	Editable_line_segment::Set_line(a, b);
	Physic_distance_join::Connect_at_points(a, b);
}

void Physic_distance_join_editable::Show()
{
	Editable_line_segment::Show();
}

void Physic_distance_join_editable::On_stop_drag_object()
{
	Connect_at_points(vertex_[0], vertex_[1]);
}

void Physic_distance_join_editable::On_stop_drag_vertex()
{
	Connect_at_points(vertex_[0], vertex_[1]);
}

