#include "editing_shape.h"
#include "engine.h"

Editing_shape::Editing_shape():
	Base_shape(),
	drag_object_(false),
	drag_point_(false),
	drag_start_(b2Vec2_zero),
	focused_vertex_(-1)
{
}

void Editing_shape::On_mouse_move(float x, float y)
{
	if (Has_edit()) {
		vec2 cursor(x, y);
		if (drag_object_) {
			On_drag_object(cursor - drag_start_);
			drag_start_ = cursor;
		}
		else if (drag_point_) {
			On_drag_point(cursor);
		}
		else {
			Update_focused_vertex(cursor);
		}
	}
}

void Editing_shape::On_mouse_down(float x, float y, int b)
{
	if (Has_edit()) {
		if (focused_vertex_ != -1) {
			drag_point_ = true;
			drag_object_ = false;
		}
		else {
			drag_point_ = false;
			drag_object_ = true;
			drag_start_ = vec2(x, y);
		}
	}
}

void Editing_shape::On_mouse_up(float x, float y, int b)
{
	if (drag_point_) {
		drag_point_ = false;
		On_stop_drag_vertex();
	}
	else if (drag_object_) {
		drag_object_ = false;
		On_stop_drag_object();
	}
}

void Editing_shape::On_drag_object(const vec2& delta)
{
	Move(delta);
}

void Editing_shape::On_drag_point(const vec2& pos)
{
	vertex_[focused_vertex_] = pos;
}

void Editing_shape::On_stop_drag_object()
{
}

void Editing_shape::On_stop_drag_vertex()
{
}


void Editing_shape::Update_focused_vertex(const vec2& point)
{
	focused_vertex_ = -1;
	for (const auto& v : vertex_) {
		focused_vertex_++;
		if (Point_in_vertex(point, v)) {
			return;
		}
	}
	focused_vertex_ = -1;
}

bool Editing_shape::Point_in_vertex(const vec2& point, const vec2& vertex) const
{
	vec2  d = vertex - point;
	float r = EDIT_POINT_SIZE * Engine::Get_camera_scale() * 0.5f;
	return d.LengthSquared() < r*r;
}