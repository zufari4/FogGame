#include "editable_circle.h"


Editable_circle::Editable_circle():
	Circle_shape(),
	Editing_shape()
{

}

bool Editable_circle::Point_in_shape(const vec2& p) const
{
	if (Circle_shape::Point_in_shape(p)) return true;
	else if (Editing_shape::Point_in_vertex(p, vertex_[0])) return true;
	else return false;
}

void Editable_circle::Update_focused_vertex(const vec2& point)
{
	if (Point_in_vertex(vertex_[0], point)) focused_vertex_ = 0;
	else focused_vertex_ = -1;
}

