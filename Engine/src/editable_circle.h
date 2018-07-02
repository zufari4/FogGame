#pragma once
#include "circle_shape.h"
#include "editing_shape.h"

class Editable_circle : virtual public Circle_shape, virtual public Editing_shape
{
public:
	Editable_circle();
	virtual ~Editable_circle() {};
	virtual bool Point_in_shape(const vec2& p) const override;
protected:
	void Update_focused_vertex(const vec2& point) override;
};

