#pragma once
#include "physic_object.h"

class Physic_box : virtual public Physic_object
{
public:
    Physic_box();
    ~Physic_box();
	void Set_body_rect(const vec2& _min, const vec2& _max);
protected: 
	vec2 Calc_center(const vec2 (&vertex)[4]);
	b2PolygonShape* box_shape_;
	b2FixtureDef    fixture_def_;
	vec2 min_vertex_;
	vec2 max_vertex_;
};