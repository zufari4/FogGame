#include "editable_line_segment.h"

Editable_line_segment::Editable_line_segment():
	Line_segment_shape(),
	Editing_shape()
{

}

bool Editable_line_segment::Point_in_shape(const vec2& p) const
{
	if (Line_segment_shape::Point_in_shape(p)) return true;
	else if (Editing_shape::Point_in_vertex(p, vertex_[0])) return true;
	else if (Editing_shape::Point_in_vertex(p, vertex_[1])) return true;
	else return false;
}
