#pragma once

#include "physic_object.h"

class Physic_circle : virtual public Physic_object
{
public:
    Physic_circle();
	~Physic_circle();
    void  Set_body_radius(float val);
	float Get_body_radius() const;
protected:
	b2CircleShape* circle_shape_;
	b2FixtureDef   fixture_def_;
};
