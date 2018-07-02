#pragma once
#include "base_class.h"
#include <Box2D/Box2D.h>

class Physic_object : public Base_class
{
public:
	Physic_object();
	virtual ~Physic_object() {};
    b2Body*    Get_body() const;
    b2Fixture* Get_fixture() const;
    b2Shape*   Get_shape() const;
    virtual bool TestPoint(const vec2& p) const;
	virtual const vec2& Get_body_pos();
	virtual void  Set_body_pos(const vec2& newpos);
	virtual float Get_body_angle() const;
protected:
    b2Body*    body_;
    b2Shape*   shape_;
    b2Fixture* fixture_;
};