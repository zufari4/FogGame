#include "editable_box.h"

Editable_box::Editable_box():
	Box_shape(),
	Editing_shape()
{

}

bool Editable_box::Point_in_shape(const vec2& p) const
{
	if (Box_shape::Point_in_shape(p)) return true;
	else if (Editing_shape::Point_in_vertex(p, vertex_[0])) return true;
	else if (Editing_shape::Point_in_vertex(p, vertex_[1])) return true;
	else if (Editing_shape::Point_in_vertex(p, vertex_[2])) return true;
	else if (Editing_shape::Point_in_vertex(p, vertex_[3])) return true;
	else return false;
}