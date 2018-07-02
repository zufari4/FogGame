#pragma once
#include "line_segment_shape.h"
#include "editing_shape.h"

class Editable_line_segment : virtual public Line_segment_shape, virtual public Editing_shape
{
public:
	Editable_line_segment();
	virtual ~Editable_line_segment() {};
	virtual bool Point_in_shape(const vec2& p) const override;
};